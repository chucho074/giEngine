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

#include <mutex>
#include <memory>
#include <map>
#include <condition_variable>

#include <OmniClient.h>
#include <OmniUsdLive.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/metrics.h>
#include <pxr/base/gf/matrix4f.h>
#include <pxr/base/gf/vec2f.h>
#include <pxr/usd/usdUtils/pipeline.h>
#include <pxr/usd/usdUtils/sparseValueWriter.h>
#include <pxr/usd/usdShade/material.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usdGeom/primvar.h>
#include <pxr/usd/usdShade/input.h>
#include <pxr/usd/usdShade/output.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdShade/materialBindingAPI.h>
#include <pxr/usd/usdLux/distantLight.h>
#include <pxr/usd/usdLux/domeLight.h>
#include <pxr/usd/usdShade/shader.h>
#include <pxr/usd/usd/modelAPI.h>

PXR_NAMESPACE_USING_DIRECTIVE

// Private tokens for building up SdfPaths. We recommend
// constructing SdfPaths via tokens, as there is a performance
// cost to constructing them directly via strings (effectively,
// a table lookup per path element). Similarly, any API which
// takes a token as input should use a predefined token
// rather than one created on the fly from a string.
TF_DEFINE_PRIVATE_TOKENS(
  _tokens,
  (box)
  (Light)
  (Looks)
  (Root)
  (Shader)
  (st)

// Globals for Omniverse Connection and base Stage
static UsdStageRefPtr gStage;

// Omniverse logging is noisy, only enable it if verbose mode (-v)
static bool gOmniverseLoggingEnabled = false;

// Global for making the logging reasonable
static std::mutex gLogMutex;


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
      tmpMesh = ();

      //checkpointFile(stageUrl, "Add box and nothing else");

      // Create lights in the scene
      //createDistantLight();
      //createDomeLight("./Materials/kloofendal_48d_partly_cloudy.hdr");

      // Add a Nucleus Checkpoint to the stage
      checkpointFile(stageUrl, "Add lights to stage");

      // Upload a material and textures to the Omniverse server
      //uploadMaterial(destinationPath);

      // Add a material to the box
      //createMaterial(boxMesh);

      // Add a Nucleus Checkpoint to the stage
      checkpointFile(stageUrl, "Add material to the box");

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
    // Keep the model contained inside of "Root", only need to do this once per model
    SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
    UsdGeomXform::Define(gStage, rootPrimPath);

    // Create the geometry inside of "Root"
    String boxName("box_");
    boxName.append(std::to_string(boxNumber));
    SdfPath boxPrimPath = rootPrimPath.AppendChild(TfToken(boxName));//_tokens->box);
    UsdGeomMesh mesh = UsdGeomMesh::Define(gStage, boxPrimPath);

    if (!mesh)
      return mesh;

    // Set orientation
    mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->rightHanded));

    // Add all of the vertices
    int num_vertices = HW_ARRAY_COUNT(gBoxPoints);
    VtArray<GfVec3f> points;
    points.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
      points[i] = GfVec3f(gBoxPoints[i][0], gBoxPoints[i][1], gBoxPoints[i][2]);
    }
    mesh.CreatePointsAttr(VtValue(points));

    // Calculate indices for each triangle
    int num_indices = HW_ARRAY_COUNT(gBoxVertexIndices); // 2 Triangles per face * 3 Vertices per Triangle * 6 Faces
    VtArray<int> vecIndices;
    vecIndices.resize(num_indices);
    for (int i = 0; i < num_indices; i++)
    {
      vecIndices[i] = gBoxVertexIndices[i];
    }
    mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));

    // Add vertex normals
    int num_normals = HW_ARRAY_COUNT(gBoxNormals);
    VtArray<GfVec3f> meshNormals;
    meshNormals.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
      meshNormals[i] = GfVec3f((float)gBoxNormals[i][0], (float)gBoxNormals[i][1], (float)gBoxNormals[i][2]);
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
      int uv_count = HW_ARRAY_COUNT(gBoxUV);
      VtVec2fArray valueArray;
      valueArray.resize(uv_count);
      for (int i = 0; i < uv_count; ++i)
      {
        valueArray[i].Set(gBoxUV[i]);
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