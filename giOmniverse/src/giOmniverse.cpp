/**
 * @file    giOmniverse.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    19/01/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */

#include "giOmniverse.h"
#include "giStaticMesh.h"
#include <giSceneGraph.h>

namespace giEngineSDK {

// Omniverse Log callback
  static void 
  logCallback(const char* threadName,
                          const char* component, 
                          OmniClientLogLevel level, 
                          const char* message) noexcept{
    std::unique_lock<std::mutex> lk(gLogMutex);
    if (gOmniverseLoggingEnabled) {
      puts(message);
    }
  }

  static void 
  OmniClientConnectionStatusCallbackImpl(void* userData, 
                                         const char* url, 
                                         OmniClientConnectionStatus status) noexcept{
    // Let's just print this regardless
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
    }
    if (status == eOmniClientConnectionStatus_ConnectError) {
      // We shouldn't just exit here - we should clean up a bit, but we're going to do it anyway
      g_logger().SetError(ERROR_TYPE::kOmniConection, "Failed connection");
      exit(-1);
    }
  }

  // Startup Omniverse 
  static bool 
  startOmniverse(bool doLiveEdit) noexcept{
  	// Register a function to be called whenever the library wants to print something to a log
  	omniClientSetLogCallback(logCallback);
  
  	// The default log level is "Info", set it to "Debug" to see all messages
  	omniClientSetLogLevel(eOmniClientLogLevel_Debug);
  
  	// Initialize the library and pass it the version constant defined in OmniClient.h
  	// This allows the library to verify it was built with a compatible version. It will
  	// return false if there is a version mismatch.
  	if (!omniClientInitialize(kOmniClientVersion)) {
  		return false;
  	}
  
  	omniClientRegisterConnectionStatusCallback(nullptr, OmniClientConnectionStatusCallbackImpl);
  
  	// Enable live updates
  	omniUsdLiveSetDefaultEnabled(doLiveEdit);
  	
  	return true;
  }

  // Stage URL really only needs to contain the server in the URL.  eg. omniverse://ov-prod
  static void 
  printConnectedUsername(const String& stageUrl) {
    // Get the username for the connection
    String userName("_none_");
    omniClientWait(omniClientGetServerInfo(stageUrl.c_str(), 
                                           &userName, 
                                           [](void* userData, 
                                              OmniClientResult result, 
                                              struct OmniClientServerInfo const* info) noexcept {
        String* userName = static_cast<String*>(userData);
        if (userData && userName && info && info->username)
        {
          userName->assign(info->username);
        }
      }));
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
    }
  }

  // Create a new connection for this model in Omniverse, returns the created stage URL
  static String 
  createOmniverseModel(const String& destinationPath) {
    String stageUrl = destinationPath + "/helloworld.usd";

    // Delete the old version of this file on Omniverse and wait for the operation to complete
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
    }
    omniClientWait(omniClientDelete(stageUrl.c_str(), nullptr, nullptr));
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
    }

    // Create this file in Omniverse cleanly
    gStage = UsdStage::CreateNew(stageUrl);
    if (!gStage) {
      g_logger().SetError(ERROR_TYPE::kOmniConection, "Failure to create model in Omniverse");
      return std::string();
    }

    {
      std::unique_lock<std::mutex> lk(gLogMutex);
    }

    // Always a good idea to declare your up-ness
    UsdGeomSetStageUpAxis(gStage, UsdGeomTokens->y);

    return stageUrl;
  }

  static void 
  createEmptyFolder(const String& emptyFolderPath) {
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
    }

    OmniClientResult localResult;
    localResult = Count_eOmniClientResult;

    omniClientWait(omniClientCreateFolder(emptyFolderPath.c_str(), 
                                          &localResult, 
                                          [](void* userData, 
                                          OmniClientResult result) noexcept {
        auto returnResult = static_cast<OmniClientResult*>(userData);
        *returnResult = result;
      }));

    {
      std::unique_lock<std::mutex> lk(gLogMutex);
    }
  }

  static void 
  checkpointFile(const String stageUrl, const char* comment) {
    bool bCheckpointsSupported = false;
    omniClientWait(omniClientGetServerInfo(stageUrl.c_str(), &bCheckpointsSupported,
      [](void* UserData, OmniClientResult Result, OmniClientServerInfo const* Info) noexcept
      {
        if (Result == eOmniClientResult_Ok && Info && UserData)
        {
          bool* bCheckpointsSupported = static_cast<bool*>(UserData);
          *bCheckpointsSupported = Info->checkpointsEnabled;
        }
      }));

    if (bCheckpointsSupported)
    {
      const bool bForceCheckpoint = true;
      omniClientWait(omniClientCreateCheckpoint(stageUrl.c_str(), comment, bForceCheckpoint, nullptr,
        [](void* userData, OmniClientResult result, char const* checkpointQuery) noexcept
        {}));
    }
  }

  static void 
  shutdownOmniverse() {
    // Calling this prior to shutdown ensures that all pending live updates complete.
    omniUsdLiveWaitForPendingUpdates();

    // The stage is a sophisticated object that needs to be destroyed properly.  
    // Since gStage is a smart pointer we can just reset it
    gStage.Reset();

    //omniClientTick(1000);
    omniClientShutdown();
  }

  static void 
  failNotify(const char* msg, const char* detail = nullptr, ...)
  {
    std::unique_lock<std::mutex> lk(gLogMutex);

    fprintf(stderr, "%s\n", msg);
    if (detail != nullptr)
    {
      fprintf(stderr, "%s\n", detail);
    }
  }

  // Opens an existing stage and finds the first UsdGeomMesh
  static UsdGeomMesh 
  findGeomMesh(const String& existingStage) {
    // Open this file from Omniverse
    gStage = UsdStage::Open(existingStage);
    if (!gStage)
    {
      failNotify("Failure to open stage in Omniverse:", existingStage.c_str());
      return UsdGeomMesh();
    }

    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      //std::cout << "Existing stage opened: " << existingStage << std::endl;
    }

    if (UsdGeomTokens->y != UsdGeomGetStageUpAxis(gStage))
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      //std::cout << "Stage is not Y-up so live xform edits will be incorrect.  Stage is " << UsdGeomGetStageUpAxis(gStage) << "-up" << std::endl;
    }

    // Traverse the stage and return the first UsdGeomMesh we find
    auto range = gStage->Traverse();
    for (const auto& node : range)
    {
      if (node.IsA<UsdGeomMesh>())
      {
        {
          std::unique_lock<std::mutex> lk(gLogMutex);
          //std::cout << "Found UsdGeomMesh: " << node.GetName() << std::endl;
        }
        return UsdGeomMesh(node);
      }
    }

    // No UsdGeomMesh found in stage (what kind of stage is this anyway!?)
    //std::cout << "ERROR: No UsdGeomMesh found in stage: " << existingStage << std::endl;
    return UsdGeomMesh();
  }


  void 
  Omni::createUSD() {
    bool doLiveEdit = true;
    String existingStage;
    String destinationPath = "omniverse://localhost/Users/giTest";

    UsdGeomMesh tmpMesh;

    if (!startOmniverse(doLiveEdit)) {
      exit(1);
    }

    if (existingStage.empty()) {
      // Create the USD model in Omniverse
      const String stageUrl = createOmniverseModel(destinationPath);

      // Print the username for the server
      printConnectedUsername(stageUrl);

      // Create box geometry in the model
      tmpMesh = getData();

      checkpointFile(stageUrl, "Add a Model and nothing else");

      // Create lights in the scene
      //createDistantLight();
      //createDomeLight("./Materials/kloofendal_48d_partly_cloudy.hdr");

      // Add a Nucleus Checkpoint to the stage
      //checkpointFile(stageUrl, "Add lights to stage");

      // Upload a material and textures to the Omniverse server
      //uploadMaterial(destinationPath);

      // Add a material to the box
      //createMaterial(boxMesh);

      // Add a Nucleus Checkpoint to the stage
      //checkpointFile(stageUrl, "Add material to the box");

      // Create an empty folder, just as an example
      createEmptyFolder(destinationPath + "/EmptyFolder");
    }
    else
    {
      // Find a UsdGeomMesh in the existing stage
      tmpMesh = findGeomMesh(existingStage);
    }

    // Do a live edit session moving the box around, changing a material
    //if (doLiveEdit && boxMesh) {
    //  liveEdit(boxMesh);
    //}
    // All done, shut down our connection to Omniverse
    shutdownOmniverse();

  }

  UsdGeomMesh
  Omni::getData() {
    
    auto& sgraph = SceneGraph::instance();

    // Keep the model contained inside of "Root", only need to do this once per model
    SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
    UsdGeomXform::Define(gStage, rootPrimPath);


    // Create the geometry inside of "Root"
    String boxName("model_");
    boxName.append(std::to_string(0));
    SdfPath boxPrimPath = rootPrimPath.AppendChild(TfToken(boxName));//_tokens->box);
    UsdGeomMesh mesh = UsdGeomMesh::Define(gStage, boxPrimPath);

    if (!mesh) {
      return mesh;
    }

    // Set orientation
    mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->rightHanded));

    // Get the model data
    // TODO: 
    // Get the meshes and get the data of every one and set it in a single list
    // USDgeo = meshes
    //Get the actor from the Scene Graph
    auto tmpActor = sgraph.getActorByName("Vela");
    //Get the Static Mesh component
    SharedPtr<StaticMesh> tmpMesh = static_pointer_cast<StaticMesh>(tmpActor->getComponent(COMPONENT_TYPE::kStaticMesh));
    //Get the Model
    auto tmpModel = tmpMesh->getModel();

    //Get the num of vertex
    int num_vertices = tmpModel->m_meshes.at(0).m_vertexVector.size();
    //Get the vertex
    Vector<Vector3> vertex;
    vertex.reserve(num_vertices);
    for(int i = 0; i < num_vertices; i++) { 
      vertex.push_back(tmpModel->m_meshes.at(0).m_vertexVector.at(i).Pos);
    }


    //Get the index
    auto tmpIndex = tmpModel->m_meshes.at(0).m_facesList;

    //Get Normals
    Vector<Vector3> Normals;
    Normals.reserve(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
      Normals.push_back(tmpModel->m_meshes.at(0).m_vertexVector.at(i).Nor);
    }

    //Get UVs
    Vector<Vector2> uvs;
    uvs.reserve(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
      uvs.push_back(tmpModel->m_meshes.at(0).m_vertexVector.at(i).Tex);
    }
    

    // Add all of the vertices
    VtArray<GfVec3f> points;
    points.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
      points[i] = GfVec3f(vertex.at(i).x, vertex.at(i).y, vertex.at(i).z);
    }
    mesh.CreatePointsAttr(VtValue(points));


    // Calculate indices for each triangle
    int num_indices = HW_ARRAY_COUNT(tmpIndex); // 2 Triangles per face * 3 Vertices per Triangle * 6 Faces
    VtArray<int> vecIndices;
    vecIndices.resize(num_indices);
    for (int i = 0; i < num_indices; i++) {
      vecIndices[i] = tmpIndex[i];
    }
    mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));


    // Add vertex normals
    int num_normals = HW_ARRAY_COUNT(Normals);
    VtArray<GfVec3f> meshNormals;
    meshNormals.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
      meshNormals[i] = GfVec3f((float)Normals[i].x, (float)Normals[i].y, (float)Normals[i].z);
    }
    mesh.CreateNormalsAttr(VtValue(meshNormals));


    // Add face vertex count
    VtArray<int> faceVertexCounts;
    faceVertexCounts.resize(12); // 2 Triangles per face * 6 faces
    std::fill(faceVertexCounts.begin(), faceVertexCounts.end(), 3);
    mesh.CreateFaceVertexCountsAttr(VtValue(faceVertexCounts));


    // Set the color on the mesh
    UsdPrim meshPrim = mesh.GetPrim();
    UsdAttribute displayColorAttr = mesh.CreateDisplayColorAttr();
    {
      VtVec3fArray valueArray;
      GfVec3f rgbFace(0.463f, 0.725f, 0.0f);
      valueArray.push_back(rgbFace);
      displayColorAttr.Set(valueArray);
    }


    // Set the UV (st) values for this mesh
    UsdGeomPrimvar attr2 = mesh.CreatePrimvar(_tokens->st, SdfValueTypeNames->TexCoord2fArray);
    {
      int uv_count = HW_ARRAY_COUNT(uvs);
      VtVec2fArray valueArray;
      valueArray.resize(uv_count);
      for (int i = 0; i < uv_count; ++i){
        valueArray[i].Set(uvs[i].x, uvs[i].y);
      }

      bool status = attr2.Set(valueArray);
    }
    attr2.SetInterpolation(UsdGeomTokens->vertex);


    // Commit the changes to the USD
    gStage->Save();
    omniUsdLiveProcess();

    return mesh;
  }


  

}