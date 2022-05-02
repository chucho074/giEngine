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
#include <giMath.h>

//#include "giMesh.h"

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
      ConsoleOut << "Connection Status: " << omniClientGetConnectionStatusString(status) << " [" << url << "]" << std::endl;
    }
    if (status == eOmniClientConnectionStatus_ConnectError) {
      // We shouldn't just exit here - we should clean up a bit, but we're going to do it anyway
      ConsoleOut << "[ERROR] Failed connection, exiting." << std::endl;
      g_logger().SetError(ERROR_TYPE::kOmniConnection, "Failed connection");
      exit(-1);
    }
  }

  // Startup Omniverse 
  static bool 
  startOmniverse(bool doLiveEdit) noexcept {
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

  // Stage URL really only needs to contain the server in the URL.
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
        if (userData && userName && info && info->username) {
          userName->assign(info->username);
        }
      }));
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Connected username: " << userName << std::endl;
    }
  }

  // Create a new connection for this model in Omniverse, returns the created stage URL
  static String 
  createOmniverseModel(const String& destinationPath) {
    String stageUrl = destinationPath + "/scene.usd";
    // Delete the old version of this file on Omniverse and wait for the operation to complete
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Waiting for " << stageUrl << " to delete... " << std::endl;
    }
    omniClientWait(omniClientDelete(stageUrl.c_str(), nullptr, nullptr));
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "finished" << std::endl;
    }

    // Create this file in Omniverse cleanly
    gStage = UsdStage::CreateNew(stageUrl);
    if (!gStage) {
      g_logger().SetError(ERROR_TYPE::kOmniConnection, 
                          "Failure to create model in Omniverse");
      return String();
    }

    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "New stage created: " << stageUrl << std::endl;
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
  failNotify(const char* msg, const char* detail = nullptr, ...) {
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
    if (!gStage) {
      failNotify("Failure to open stage in Omniverse:", existingStage.c_str());

      g_logger().SetError(ERROR_TYPE::kOmniConnection,
                          "Failure to open stage in Omniverse:" + existingStage);
      return UsdGeomMesh();
    }

    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Existing stage opened: " << existingStage << std::endl;
    }

    if (UsdGeomTokens->y != UsdGeomGetStageUpAxis(gStage)) {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Stage is not Y-up so live xform edits will be incorrect.  Stage is " 
                 << UsdGeomGetStageUpAxis(gStage) << "-up" << std::endl;
    }

    // Traverse the stage and return the first UsdGeomMesh we find
    auto range = gStage->Traverse();
    for (const auto& node : range) {
      if (node.IsA<UsdGeomMesh>()) {
        {
          std::unique_lock<std::mutex> lk(gLogMutex);
          ConsoleOut << "Found UsdGeomMesh: " << node.GetName() << std::endl;
        }
        return UsdGeomMesh(node);
      }
    }

    // No UsdGeomMesh found in stage.
    // (what kind of stage is this anyway!?) - idk man, just in case.
    ConsoleOut << "ERROR: No UsdGeomMesh found in stage: " << existingStage << std::endl;
    g_logger().SetError(ERROR_TYPE::kOmniConnection,
                        "ERROR: No UsdGeomMesh found in stage: " + existingStage);
    return UsdGeomMesh();
  }

  // Returns true if the provided maybeURL contains a host and path
  static bool 
  isValidOmniURL(const std::string& maybeURL) {
    bool isValidURL = false;
    OmniClientUrl* url = omniClientBreakUrl(maybeURL.c_str());
    if (url->host && url->path &&
      (std::string(url->scheme) == std::string("omniverse") ||
        std::string(url->scheme) == std::string("omni")))
    {
      isValidURL = true;
    }
    omniClientFreeUrl(url);
    return isValidURL;
  }


  void 
  Omni::startConection() {
    //Get the instance of the SceneGraph
    auto& sgraph = SceneGraph::instance();

    if (m_existingStage.empty()) {
  //> Case of need to create a new USD from Scene Graph.
      //Verify if the sceneGraph haves information.
      if(sgraph.m_numActors > 0 ) {
        //In case than the sgraph have information, create the USD from it.
        createEmptyUSD("giTestProject");
        //Sets the information from the Scene Graph.
        createUSDFromSG();
      }
  //> Case of there is no info (new project) - Actives the live Sync by default.
      else if (sgraph.m_numActors == 0) {
        //In case than the sgraph have information, create the USD from it.
        createEmptyUSD("giTestProject");
        // Create the USD model in Omniverse
        createOmniverseModel(m_destinationPath);
        //Actives the live Edit
        m_liveEditActivation = true;
      }
    }

  //> Case of gets the Scene info from Omniverse USD.
    else {
      // Find a UsdGeomMesh in the existing stage
      createSGFromUSD(findGeomMesh(m_existingStage));
    }
  
  }

  void
  Omni::update() {
    UsdGeomMesh tmpMesh;
    
    if (!startOmniverse(m_liveEditActivation)) {
      Logger::instance().SetError(ERROR_TYPE::kOmniConnection, 
                                  "Error creating the conection with NVIDIA Omniverse");
      exit(1);
    }

    if (m_existingStage.empty()) {
      // Create the USD model in Omniverse
      const String stageUrl = createOmniverseModel(m_destinationPath);

      m_existingStage = m_existingStage +"/scene.usd";
      // Print the username for the server
      printConnectedUsername(stageUrl);
       
      // Get the geometry from the Scene Graph
      tmpMesh = getData();

      checkpointFile(stageUrl, "Add a Model and nothing else");
    }

    else {
      // Find a UsdGeomMesh in the existing stage
      m_existingStage = m_existingStage +"/scene.usd";
      
      tmpMesh = findGeomMesh(m_existingStage);
    }
     // Do a live edit session moving the box around, changing a material.
    if (m_liveEditActivation) {
      liveEdit(tmpMesh);
    }
  }

  void 
  Omni::destroy() {
    shutdownOmniverse();
  }

  void
  Omni::createUSDFromSG() {
    
    UsdGeomMesh tmpMesh;

    if (!startOmniverse(m_liveEditActivation)) {
      Logger::instance().SetError(ERROR_TYPE::kOmniConnection, 
                                  "Error creating the conection with NVIDIA Omniverse");
      exit(1);
    }
    
    // Create the USD model in Omniverse
    const String stageUrl = createOmniverseModel(m_destinationPath);

    // Print the username for the server
    printConnectedUsername(stageUrl);

    // Get the geometry from the Scene Graph
    tmpMesh = getData();

    // Adding a checkpoint for the added models
    checkpointFile(stageUrl, "Added a Model(s) from the Scene Graph existans info.");

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

    // All done, shut down our connection to Omniverse
    shutdownOmniverse();

  }

  void
  Omni::liveEdit(UsdGeomMesh inMesh) {

    // Process any updates that may have happened to the stage from another client
    omniUsdLiveWaitForPendingUpdates();
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Begin Live Edit\n";
    }

    // Process any updates that may have happened to the stage from another client
    omniUsdLiveWaitForPendingUpdates();

    if (m_liveEditActivation) {
      double angle = 0;
      if (angle >= 360) {
        angle = 0;
      }
      double radians = angle * Math::PI / 180.0;
      double x = sin(radians) * 100;
      double y = cos(radians) * 100;

      // Get the transform on the mesh
      UsdGeomXformable xForm = inMesh;

      // Define storage for the different xform ops that Omniverse Kit likes to use
      UsdGeomXformOp translateOp;
      UsdGeomXformOp rotateOp;
      UsdGeomXformOp scaleOp;
      GfVec3d position(0);
      GfVec3f rotZYX(0);
      GfVec3f scale(1);

      // Get the xform ops stack
      bool resetXformStack = false;
      Vector<UsdGeomXformOp> xFormOps = xForm.GetOrderedXformOps(&resetXformStack);

      // Get the current xform op values
      for (size_T i = 0; i < xFormOps.size(); i++) {
        switch (xFormOps[i].GetOpType()) {
        case UsdGeomXformOp::TypeTranslate: {
          translateOp = xFormOps[i];
          translateOp.Get(&position);
          break;
        }
        case UsdGeomXformOp::TypeRotateZYX: {
          rotateOp = xFormOps[i];
          rotateOp.Get(&rotZYX);
          break;
        }
        case UsdGeomXformOp::TypeScale: {
          scaleOp = xFormOps[i];
          scaleOp.Get(&scale);
          break;
        }
        }
      }

      // Move/Rotate the existing position/rotation - this works for Y-up stages
      //position += GfVec3d(x, 0, y);
      //rotZYX = GfVec3f(rotZYX[0], angle, rotZYX[2]);

      SetOp(xForm, translateOp, UsdGeomXformOp::TypeTranslate, position, UsdGeomXformOp::Precision::PrecisionDouble);
      SetOp(xForm, rotateOp, UsdGeomXformOp::TypeRotateZYX, rotZYX, UsdGeomXformOp::Precision::PrecisionFloat);
      SetOp(xForm, scaleOp, UsdGeomXformOp::TypeScale, scale, UsdGeomXformOp::Precision::PrecisionFloat);

      // Make sure the xform op order is correct (translate, rotate, scale)
      Vector<UsdGeomXformOp> xFormOpsReordered;
      xFormOpsReordered.push_back(translateOp);
      xFormOpsReordered.push_back(rotateOp);
      xFormOpsReordered.push_back(scaleOp);
      xForm.SetXformOpOrder(xFormOpsReordered);

      // Commit the change to USD
      gStage->Save();

    }

    
  }

  void 
  Omni::createEmptyUSD(String inProjectName) {
    
    // Create an empty folder, just as an example
    createEmptyFolder(m_destinationPath + inProjectName);
    // Saving the new existing stage
    m_existingStage = m_destinationPath + inProjectName;
    // Saving the destination path with the projectName
    m_destinationPath = m_existingStage;
  }

  void 
  Omni::createSGFromUSD(UsdGeomMesh inMesh) {
    auto& sgraph = SceneGraph::instance();


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
    SdfPath modelPath = rootPrimPath.AppendChild(TfToken(boxName));//_tokens->box);
    UsdGeomMesh model = UsdGeomMesh::Define(gStage, modelPath);

    if (!model) {
      return model;
    }

    // Get the model data
    // TODO: 
    // Get the meshes and get the data of every one and set it in a single list
    // USDgeo = meshes

    //Get the actor from the Scene Graph
    auto tmpActor = sgraph.getActorByName("Vela");
    //Get the Static Mesh component
    SharedPtr<StaticMesh> tmpModelBase = static_pointer_cast<StaticMesh>(tmpActor->getComponent(COMPONENT_TYPE::kStaticMesh));
    //Get the Model
    auto tmpModel = tmpModelBase->getModel();
    int noMesh = 0;

    for(auto actualMesh : tmpModel->m_meshes) {
      // Create the geometry inside of "model_"
      String boxName("mesh_");
      boxName.append(std::to_string(noMesh));
      SdfPath meshPath = modelPath.AppendChild(TfToken(boxName));//_tokens->box);
      UsdGeomMesh mesh = UsdGeomMesh::Define(gStage, meshPath);

      if (!mesh) {
        return mesh;
      }


      // Set orientation
      mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->leftHanded));

      //Get the num of vertex
      int num_vertices = actualMesh.m_vertexVector.size();
      //Get the vertex
      Vector<Vector3> vertex;
      vertex.reserve(num_vertices);
      for(int i = 0; i < num_vertices; i++) { 
        vertex.push_back(actualMesh.m_vertexVector.at(i).Pos);
      }
      
      
      //Get the index
      auto tmpIndex = actualMesh.m_facesList;
      
      //Get Normals
      Vector<Vector3> Normals;
      Normals.reserve(num_vertices);
      for (int i = 0; i < num_vertices; i++) {
        Normals.push_back(actualMesh.m_vertexVector.at(i).Nor);
      }
      
      //Get UVs
      Vector<Vector2> uvs;
      uvs.reserve(num_vertices);
      for (int i = 0; i < num_vertices; i++) {
        uvs.push_back(actualMesh.m_vertexVector.at(i).Tex);
      }
      
      
      // Add all of the vertices
      VtArray<GfVec3f> points;
      points.resize(num_vertices);
      for (int i = 0; i < num_vertices; i++) {
        points[i] = GfVec3f(vertex.at(i).x, vertex.at(i).y, vertex.at(i).z);
      }
      mesh.CreatePointsAttr(VtValue(points));
      
      
      // Calculate indices for each triangle
      int num_indices = tmpIndex.size(); // 2 Triangles per face * 3 Vertices per Triangle * 6 Faces
      //int num_indices = HW_ARRAY_COUNT(tmpIndex); // 2 Triangles per face * 3 Vertices per Triangle * 6 Faces
      VtArray<int> vecIndices;
      vecIndices.resize(num_indices);
      for (int i = 0; i < num_indices; i++) {
        vecIndices[i] = tmpIndex[i];
      }
      mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));
      
      
      // Add vertex normals
      int num_normals = Normals.size();
      //int num_normals = HW_ARRAY_COUNT(Normals);
      VtArray<GfVec3f> meshNormals;
      meshNormals.resize(num_vertices);
      for (int i = 0; i < num_vertices; i++) {
        meshNormals[i] = GfVec3f(Normals[i].x, Normals[i].y, Normals[i].z);
      }
      mesh.CreateNormalsAttr(VtValue(meshNormals));
      
      
      // Add face vertex count
      VtArray<int> faceVertexCounts;
      faceVertexCounts.resize(num_indices * 2); // 2 Triangles per face * 6 faces
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
        int uv_count = uvs.size();
        //int uv_count = HW_ARRAY_COUNT(uvs);
        VtVec2fArray valueArray;
        valueArray.resize(uv_count);
        for (int i = 0; i < uv_count; ++i){
          valueArray[i].Set(uvs[i].x, uvs[i].y);
        }
      
        bool status = attr2.Set(valueArray);
      }
      attr2.SetInterpolation(UsdGeomTokens->vertex);
      rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(TfToken(boxName));
      noMesh++;
    }
    // Commit the changes to the USD
    gStage->Save();
    omniUsdLiveProcess();

    return model;
  }

  SharedPtr<Model> 
  Omni::modelFromUSD() {
    
    auto& sgraph = SceneGraph::instance();

    SharedPtr<Model> tmpModel;
    String destinationPath = "Resources/usds/battledroid.usd";
    
    Vector<Vector3> tmpVertexModel;
    Vector<Vector3> tmpNormalsModel;
    Vector<uint32>  tmpFacesModel;

    //Get the USD information
    UsdGeomMesh tmpUSDMesh;
    
    //Get the data of the mesh
    tmpUSDMesh = findGeomMesh(destinationPath);

    //Get the information
    UsdAttribute tmpVertex = tmpUSDMesh.GetPointsAttr();
    UsdAttribute tmpNormals = tmpUSDMesh.GetNormalsAttr();
    UsdAttribute tmpFaces = tmpUSDMesh.GetFaceVertexCountsAttr();

    //Points
    VtArray<GfVec3f> tmpPointArray;
    tmpVertex.Get(&tmpPointArray);

    Vector<GfVec3f> pointArray;

    uint32 size = tmpPointArray.size();
    auto tmpStart = reinterpret_cast<GfVec3f*>(tmpPointArray.data());
    auto tmpEnd = tmpStart + size;
    pointArray.reserve(size);
    pointArray.insert(pointArray.end(), tmpStart, tmpEnd);

    for(int i = 0; i < size; ++i) {
      tmpVertexModel.push_back(Vector3(pointArray[i].GetArray()[0], 
                                       pointArray[i].GetArray()[1],
                                       pointArray[i].GetArray()[2]));
    }
    
    //Normals
    VtArray<GfVec3f> tmpNormalArray;
    tmpNormals.Get(&tmpNormalArray);

    Vector<GfVec3f> norArray;

    uint32 sizeNor = tmpNormalArray.size();
    auto tmpStartNor = reinterpret_cast<GfVec3f*>(tmpNormalArray.data());
    auto tmpEndNor = tmpStartNor + sizeNor;
    norArray.reserve(sizeNor);
    norArray.insert(norArray.end(), tmpStartNor, tmpEndNor);

    for (int i = 0; i < size; ++i) {
      tmpNormalsModel.push_back(Vector3(norArray[i].GetArray()[0],
                                        norArray[i].GetArray()[1],
                                        norArray[i].GetArray()[2]));
    }

    //Faces
    VtArray<GfVec3f> tmpFacesArray;
    tmpFaces.Get(&tmpFacesArray);

    Vector<GfVec3f> faceArray;

    uint32 sizeFace = tmpFacesArray.size();
    auto tmpStartFaces = reinterpret_cast<GfVec3f*>(tmpFacesArray.data());
    auto tmpEndFaces = tmpStartFaces + sizeFace;
    faceArray.reserve(sizeFace);
    faceArray.insert(faceArray.end(), tmpStartFaces, tmpEndFaces);

    for (int i = 0; i < size; ++i) {
      tmpFacesModel.push_back(faceArray[i].GetArray()[0]);
    }

    //Create the mesh
    Mesh tmpMesh;
    //Set the vertex data to the Vector
    for(int i = 0; i < size; ++i) {
      //Create the vertex
      SimpleVertex tmpVertex;
      //Set positions
      tmpVertex.Pos = tmpVertexModel[i];
      //Set UVs
      
      //Set Normals
      tmpVertex.Nor = tmpNormalsModel[i];

      //Set to the list
      tmpMesh.m_vertexVector.push_back(tmpVertex);
    }
    //Set the index
    tmpMesh.m_facesList = tmpFacesModel;

    //Set in the meshes
    tmpModel->m_meshes.push_back(tmpMesh);
    
    return tmpModel;
  }

  
}