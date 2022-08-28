/**
 * @file    giOmniverse.cpp
 * @author  Jesus Alberto Del Moral Cupil
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
#include <giBaseGraphicsAPI.h>
#include <giTransform.h>
#include <giResourceManager.h>
#include <giUUID.h>
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
      ConsoleOut << "Connection Status: " 
                 << omniClientGetConnectionStatusString(status) 
                 << " [" << url << "]" << ConsoleLine;
    }
    if (status == eOmniClientConnectionStatus_ConnectError) {
      // We shouldn't just exit here - we should clean up a bit, 
      // but we're going to do it anyway
      ConsoleOut << "[ERROR] Failed connection, exiting." << ConsoleLine;
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
      ConsoleOut << "Connected username: " << userName << ConsoleLine;
    }
  }

  // Create a new connection for this model in Omniverse, 
  // returns the created stage URL.
  static String 
  createOmniverseModel(const String& destinationPath) {
    String stageUrl = destinationPath + "/scene.usd";
    // Delete the old version of this file on Omniverse and wait for the operation to complete
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Waiting for " << stageUrl << " to delete... " << ConsoleLine;
    }
    omniClientWait(omniClientDelete(stageUrl.c_str(), nullptr, nullptr));
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "finished" << ConsoleLine;
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
      ConsoleOut << "New stage created: " << stageUrl << ConsoleLine;
    }

    // Always a good idea to declare your up-ness
    UsdGeomSetStageUpAxis(gStage, UsdGeomTokens->y);

    return stageUrl;
  }

  // Create a light source in the scene.
  static void 
  createDistantLight() {
    // Construct /Root/Light path
    SdfPath lightPath = SdfPath::AbsoluteRootPath()
                                 .AppendChild(_tokens->Root)
                                 .AppendChild(_tokens->DistantLight);
    UsdLuxDistantLight newLight = UsdLuxDistantLight::Define(gStage, lightPath);

    // Set the attributes
    newLight.CreateAngleAttr(VtValue(0.53f));
    GfVec3f color(1.0f, 1.0f, 0.745f);
    newLight.CreateColorAttr(VtValue(color));
    newLight.CreateIntensityAttr(VtValue(5000.0f));

    // Commit the changes to the USD
    gStage->Save();
    omniUsdLiveProcess();
  }

  static void 
  createEmptyFolder(const String& emptyFolderPath) {
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Waiting to create a new folder: " << emptyFolderPath << " ... ";
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
      ConsoleOut << "finished [" << omniClientGetResultString(localResult) 
                 << "]" << ConsoleLine;
    }
  }

  static void 
  checkpointFile(const String stageUrl, const char* comment) {
    bool bCheckpointsSupported = false;
    omniClientWait(omniClientGetServerInfo(stageUrl.c_str(), &bCheckpointsSupported,
      [](void* UserData, OmniClientResult Result, OmniClientServerInfo const* Info) noexcept
      {
        if (Result == eOmniClientResult_Ok && Info && UserData) {
          bool* bCheckpointsSupported = static_cast<bool*>(UserData);
          *bCheckpointsSupported = Info->checkpointsEnabled;
        }
      }));

    if (bCheckpointsSupported) {
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
    if (detail != nullptr) {
      fprintf(stderr, "%s\n", detail);
    }
  }

  // Opens an existing stage and finds the first UsdGeomMesh
  static Vector<UsdPrim>
  findGeomMesh() {
   
    omniUsdLiveWaitForPendingUpdates();
    Vector<UsdPrim> geomMeshes;
    auto range = gStage->Traverse();
    for (const auto& node : range) {
      if ("Root" == node.GetParent().GetName().GetString()) {
        if (node.IsA<UsdGeomMesh>()) {
          geomMeshes.push_back(node);
        }
      }
    }
    return geomMeshes;

  }

  // Upload a material and its textures to the Omniverse Server
  static void 
  uploadMaterial(const String& destinationPath) {
    String uriPath = destinationPath + "/Materials";

    // Delete the old version of this folder on Omniverse and wait for the 
    // operation to complete.
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Waiting for " << uriPath << " to delete... ";
    }
    omniClientWait(omniClientDelete(uriPath.c_str(), nullptr, nullptr));

    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Finished" << ConsoleLine;
    }

    // Upload the material folder (MDL and textures)
    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Waiting for the resources/Materials folder to upload to " 
                 << uriPath << " ... ";
    }

    omniClientWait(omniClientCopy("resources/Materials", 
                                  uriPath.c_str(), 
                                  nullptr, 
                                  nullptr));

    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Finished" << ConsoleLine;
    }
  }

  // Bind a material to this geometry
  static void 
  createMaterial(UsdGeomMesh inUsdMesh, Mesh inOwnMesh, String inMeshName) {
    
    auto& RM = g_resourceManager().instance();

    //If the mesh doesn't have textures. 
    if (0 == inOwnMesh.m_textures.size()) {
      return;
    }
    
    // Get the material name.
    String materialName = inMeshName;
    String tmpPath = "./Materials/";
    tmpPath = tmpPath + inMeshName;

    // Create a material instance for this in USD.
    TfToken materialNameToken(materialName);
    // Make path for "/Root/Looks/MODELNAME".
    SdfPath matPath = SdfPath::AbsoluteRootPath()
                               .AppendChild(_tokens->Root)
                               .AppendChild(_tokens->Looks)
                               .AppendChild(materialNameToken);
    UsdShadeMaterial newMat = UsdShadeMaterial::Define(gStage, matPath);

    // MDL Shader.
    // Create the MDL shader to bind to the material.
    SdfAssetPath mdlShaderModule = SdfAssetPath(tmpPath + ".mdl");
    SdfPath tmpShaderPath = matPath.AppendChild(materialNameToken);
    UsdShadeShader mdlShader = UsdShadeShader::Define(gStage, tmpShaderPath);
    mdlShader.CreateIdAttr(VtValue(_tokens->shaderId));

    // These attributes will be reworked or replaced in the official MDL schema for USD.
    // https://developer.nvidia.com/usd/MDLschema
    mdlShader.SetSourceAsset(mdlShaderModule, _tokens->mdl);
    mdlShader.GetPrim().CreateAttribute(TfToken("info:mdl:sourceAsset:subIdentifier"), 
                                        SdfValueTypeNames->Token, 
                                        false, 
                                        SdfVariabilityUniform).Set(materialNameToken);

    // Set the linkage between material and MDL shader.
    UsdShadeOutput mdlOutput = newMat.CreateSurfaceOutput(_tokens->mdl);
    mdlOutput.ConnectToSource(mdlShader, _tokens->out);
    

    // USD Preview Surface Shaders.
    
    // Create the "USD Primvar reader for float2" shader.
    SdfPath shaderPath = matPath.AppendChild(_tokens->PrimST);
    UsdShadeShader primStShader = UsdShadeShader::Define(gStage, shaderPath);
    primStShader.CreateIdAttr(VtValue(_tokens->PrimStShaderId));
    primStShader.CreateOutput(_tokens->result, SdfValueTypeNames->Float2);
    primStShader.CreateInput(_tokens->varname, SdfValueTypeNames->Token).Set(_tokens->st);

    String tmpTextureName;
    String tmpFileName;
    TfToken tmpTextureToken;
    Vector<UsdShadeOutput> tmpOuputShaders; 
    for (auto textures : inOwnMesh.m_textures) {

      //Get the resource of the texture.
      auto tmpResource = RM.getResource(textures.m_id);
      auto tmpTexture = static_pointer_cast<Texture>(tmpResource.lock());
     
      if (TEXTURE_TYPE::kAlbedo == tmpTexture->m_type) {
        //The name of the texture.
        tmpTextureName = "DiffuseColorTex";
        //The token of the texture.
        tmpTextureToken = _tokens->sRGB;
        //The name of the file.
        tmpFileName = "BaseColor";
      }
      
      if (TEXTURE_TYPE::kNormal == tmpTexture->m_type) {
        tmpTextureName = "NormalTex";

        tmpTextureToken = _tokens->RAW;

        tmpFileName = "Norm";
      }

      if (TEXTURE_TYPE::kSpecular == tmpTexture->m_type) {
        break;
      }
      
      if (TEXTURE_TYPE::kGloss == tmpTexture->m_type) {
        break;
      }

      // Create the shader.
      String tmpShaderName = materialName + tmpTextureName;
      String tmpFilePath = "./Materials" + tmpTexture->m_path.string();
      shaderPath = matPath.AppendChild(TfToken(tmpShaderName));
      UsdShadeShader tmpShader = UsdShadeShader::Define(gStage, shaderPath);
      tmpShader.CreateIdAttr(VtValue(_tokens->UsdUVTexture));
      UsdShadeInput texInput = tmpShader.CreateInput(_tokens->file, 
                                                     SdfValueTypeNames->Asset);
      texInput.Set(SdfAssetPath(tmpFilePath));
      texInput.GetAttr().SetColorSpace(tmpTextureToken);
      tmpShader.CreateInput(_tokens->st, SdfValueTypeNames->Float2)
                            .ConnectToSource(primStShader
                                            .CreateOutput(_tokens->result, 
                                                          SdfValueTypeNames->Float2));
      UsdShadeOutput tmpShaderOutput = tmpShader.CreateOutput(_tokens->rgb, 
                                                              SdfValueTypeNames->Float3);

      tmpOuputShaders.push_back(tmpShaderOutput);
    }

    // Create the USD Preview Surface shader
    String usdPreviewSurfaceShaderName = materialName + "PreviewSurface";
    shaderPath = matPath.AppendChild(TfToken(usdPreviewSurfaceShaderName));
    UsdShadeShader usdPreviewSurfaceShader = UsdShadeShader::Define(gStage, shaderPath);
    usdPreviewSurfaceShader.CreateIdAttr(VtValue(_tokens->UsdPreviewSurface));
    UsdShadeInput diffuseColorInput = usdPreviewSurfaceShader.CreateInput(_tokens->diffuseColor, 
                                                                          SdfValueTypeNames->Color3f);
    diffuseColorInput.ConnectToSource(tmpOuputShaders[0]);
    if (tmpOuputShaders.size() > 1) {
      UsdShadeInput normalInput = usdPreviewSurfaceShader.CreateInput(_tokens->normal, 
                                                                      SdfValueTypeNames->Normal3f);
      normalInput.ConnectToSource(tmpOuputShaders[1]);
    }

    // Set the linkage between material and USD Preview surface shader
    UsdShadeOutput usdPreviewSurfaceOutput = newMat.CreateSurfaceOutput();
    usdPreviewSurfaceOutput.ConnectToSource(usdPreviewSurfaceShader, _tokens->surface);

    // Final step, associate the material with the face
    UsdShadeMaterialBindingAPI usdMaterialBinding(inUsdMesh);
    usdMaterialBinding.Bind(newMat);
    // Commit the changes to the USD
    gStage->Save();
    omniUsdLiveProcess();
  }

  // Create a light source in the scene.
  static void 
  createDomeLight(const String& texturePath) {
    // Construct /Root/Light path
    SdfPath lightPath = SdfPath::AbsoluteRootPath()
                                 .AppendChild(_tokens->Root)
                                 .AppendChild(_tokens->DomeLight);
    UsdLuxDomeLight newLight = UsdLuxDomeLight::Define(gStage, lightPath);

    // Set the attributes
    newLight.CreateIntensityAttr(VtValue(1000.0f));
    newLight.CreateTextureFileAttr(VtValue(SdfAssetPath(texturePath)));
    newLight.CreateTextureFormatAttr(VtValue(UsdLuxTokens->latlong));

    // Set rotation on domelight
    UsdGeomXformable xForm = newLight;
    UsdGeomXformOp rotateOp;
    GfVec3f rotZYX(270, 0, 0);
    rotateOp = xForm.AddXformOp(UsdGeomXformOp::TypeRotateZYX, UsdGeomXformOp::Precision::PrecisionFloat);
    rotateOp.Set(rotZYX);

    // Commit the changes to the USD
    gStage->Save();
    omniUsdLiveProcess();
  }


  // Returns true if the provided maybeURL contains a host and path
  static bool 
  isValidOmniURL(const String& maybeURL) {
    bool isValidURL = false;
    OmniClientUrl* url = omniClientBreakUrl(maybeURL.c_str());
    if (url->host && url->path &&
      (String(url->scheme) == String("omniverse") ||
        String(url->scheme) == String("omni"))) {
      isValidURL = true;
    }
    omniClientFreeUrl(url);
    return isValidURL;
  }

  void 
  Omni::startConection() {

    if (!startOmniverse(m_liveEditActivation)) {
      Logger::instance().SetError(ERROR_TYPE::kOmniConnection,
                                  "Error creating the conection with NVIDIA Omniverse");
    }

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
      createSGFromUSD();
    }
  
  }

  void
  Omni::update() {
    if (m_liveEditActivation) {
      liveEdit(findGeomMesh());
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
      
    }
    
    // Create the USD model in Omniverse.
    const String stageUrl = createOmniverseModel(m_destinationPath);

    // Print the username for the server.
    printConnectedUsername(stageUrl);

    // Adding a checkpoint for the added models.
    checkpointFile(stageUrl, "Added a Model(s) from the Scene Graph existans info.");

    // Create lights in the scene.
    createDistantLight();

    //Create the skybox with the skybox texture.
    createDomeLight("./Materials/skyboxDefault.hdr");

    // Add a Nucleus Checkpoint to the stage.
    checkpointFile(stageUrl, "Added a default skybox to the scene");

    // Upload a material and textures to the Omniverse server.
    uploadMaterial(m_destinationPath);

    // Add a material to the box.
    getFromSG();

    // Add a Nucleus Checkpoint to the stage.
    checkpointFile(stageUrl, "Added a material to the Model(s)");

    // All done, shut down our connection to Omniverse.
    //shutdownOmniverse();

  }

  void
  Omni::liveEdit(Vector<UsdPrim> inMesh) {

    // Process any updates that may have happened to the stage from another client.
    auto& sgraph = SceneGraph::instance();

    omniUsdLiveWaitForPendingUpdates();

    for (auto& prim : inMesh) {
      if (m_liveEditActivation) {
        
        UsdGeomMesh geomMesh(prim);
        // Get the transform on the mesh.
        UsdGeomXformable xForm = geomMesh;

        // Define storage for the different xform ops that Omniverse Kit likes to use.
        UsdGeomXformOp translateOp;
        UsdGeomXformOp rotateOp;
        UsdGeomXformOp scaleOp;
        GfVec3d position(0);
        GfVec3f rotZYX(0);
        GfVec3f scale(1);

        // Get the xform ops stack.
        bool resetXformStack = false;
        Vector<UsdGeomXformOp> xFormOps = xForm.GetOrderedXformOps(&resetXformStack);

        // Get the current xform op values.
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

        //SetOp(xForm, translateOp, UsdGeomXformOp::TypeTranslate, position, UsdGeomXformOp::Precision::PrecisionDouble);
        //SetOp(xForm, rotateOp, UsdGeomXformOp::TypeRotateZYX, rotZYX, UsdGeomXformOp::Precision::PrecisionFloat);
        //SetOp(xForm, scaleOp, UsdGeomXformOp::TypeScale, scale, UsdGeomXformOp::Precision::PrecisionFloat);

        // Make sure the xform op order is correct (translate, rotate, scale).
        //Vector<UsdGeomXformOp> xFormOpsReordered;
        //xFormOpsReordered.push_back(translateOp);
        //xFormOpsReordered.push_back(rotateOp);
        //xFormOpsReordered.push_back(scaleOp);
        //xForm.SetXformOpOrder(xFormOpsReordered);

        //Get corresponding actor in scenegraph      
        SharedPtr<Actor> tmpActor = sgraph.getActorByName(prim.GetName().GetString());
        Vector3 tmpPos(position.GetArray()[0],
                       position.GetArray()[1],
                       position.GetArray()[2]);

        Vector3 tmpScale(scale.GetArray()[0],
                         scale.GetArray()[1],
                         scale.GetArray()[2]);

        //Set Translation
        tmpActor->m_transform.m_translation = tmpPos;

        //Set Rotations


        //Set Scale
        tmpActor->m_transform.m_scale = tmpScale;
        
        //ConsoleOut << "Pos: X " << tmpPos.x << " Y " << tmpPos.y << " Z " << tmpPos.z << ConsoleLine;
        //ConsoleOut << "Scale: X " << tmpScale.x << " Y " << tmpScale.y << " Z " << tmpScale.z << ConsoleLine;

        // Commit the change to USD / Just to send our information to save.
        gStage->Save();
      }
    }
  }

  void 
  Omni::createEmptyUSD(StringView inProjectName) {
    
    // Create an empty folder, just as an example
    createEmptyFolder(m_destinationPath + inProjectName.data());
    // Saving the new existing stage
    m_existingStage = m_destinationPath + inProjectName.data();
    // Saving the destination path with the projectName
    m_destinationPath = m_existingStage;

    m_existingStage += "/scene.usd";
  }

  void 
  Omni::createSGFromUSD() {

    auto& gapi = g_graphicsAPI();
    auto& RM = g_resourceManager();
    auto& sgraph = SceneGraph::instance();

    omniUsdLiveWaitForPendingUpdates();

    // Open this file from Omniverse.
    gStage = UsdStage::Open(m_existingStage);
    if (!gStage) {
      failNotify("Failure to open stage in Omniverse:", m_existingStage.c_str());

      g_logger().SetError(ERROR_TYPE::kOmniConnection,
                          "Failure to open stage in Omniverse:" + m_existingStage);
      return;
    }

    {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Existing stage opened: " << m_existingStage << ConsoleLine;
    }

    if (UsdGeomTokens->y != UsdGeomGetStageUpAxis(gStage)) {
      std::unique_lock<std::mutex> lk(gLogMutex);
      ConsoleOut << "Stage is not Y-up so live xform edits will be incorrect.  Stage is "
                 << UsdGeomGetStageUpAxis(gStage) << "-up" << ConsoleLine;
    }

    Vector<Vector3> tmpVertexModel;
    Vector<Vector3> tmpNormalsModel;
    Vector<uint32>  tmpFacesModel;
    Vector<Vector2> tmpUVsModel;

    // Traverse the stage and return the first UsdGeomMesh we find.
    auto range = gStage->Traverse();
    for (const auto& node : range) {
      if (node.IsA<UsdGeomMesh>()) {
        std::unique_lock<std::mutex> lk(gLogMutex);

        SharedPtr<Actor> tmpActor;
        tmpActor.reset(new Actor);
        Vector<SharedPtr<Mesh>> tmpMeshes;

        UsdPrim parent = node.GetParent();
        if ("Root" == parent.GetName()) {
          ConsoleOut << "Found UsdGeomMesh: " << node.GetName() << ConsoleLine;

          UsdGeomMesh geoMesh(node);

          //Get the information.
          
          //Points / Vertex.
          UsdAttribute tmpVertex = geoMesh.GetPointsAttr();
          VtArray<GfVec3f> tmpPointArray;
          tmpVertex.Get(&tmpPointArray);
          //Check if it has points / vertex.
          if (NULL == tmpPointArray.size() && !node.GetAllChildren().empty()) {
            //
            for (const auto& tmpIter : node.GetAllChildren()) {
              //Check if is a GeoMesh
              if(tmpIter.IsA<UsdGeomMesh>()) {
                UsdGeomMesh meshGeoMesh(tmpIter);
                ConsoleOut << "Found a mesh in: " << node.GetName() << " named: " 
                           << tmpIter.GetName() << ConsoleLine;

                //Create the mesh and set in the meshes.
                tmpMeshes.push_back(createMeshFromGeoMesh(meshGeoMesh,
                                                          tmpIter.GetPath().GetString()));

              }
            }
          }
          else {
            
            //Set in the meshes.
            tmpMeshes.push_back(createMeshFromGeoMesh(geoMesh,
                                                      node.GetPath().GetString()));
          }
          
          //Set the actor model to the Root in SG.
          tmpActor->m_actorName = node.GetName();
          SharedPtr<StaticMesh> modelComponent = make_shared<StaticMesh>(RM.createModelFromMem(tmpMeshes));
          tmpActor->addComponent(modelComponent, COMPONENT_TYPE::kStaticMesh);
          tmpActor->m_omniRefPath = node.GetPath().GetString();
          sgraph.addActor(tmpActor, sgraph.getRoot());

        }
      }
    }
  }

  SharedPtr<Mesh> 
  Omni::createMeshFromGeoMesh(UsdGeomMesh inMesh, StringView inPath) {
    auto& gapi = g_graphicsAPI();
    auto& RM = g_resourceManager();

    Vector<Vector3> tmpVertexMesh;
    Vector<Vector3> tmpNormalsMesh;
    Vector<uint32>  tmpFacesMesh;
    Vector<Vector2> tmpUVsMesh;

    //Points / Vertex.
    UsdAttribute tmpMeshVertex = inMesh.GetPointsAttr();
    VtArray<GfVec3f> tmpMeshPointArray;
    tmpMeshVertex.Get(&tmpMeshPointArray);

    Vector<GfVec3f> pointMeshArray;

    uint32 sizeMesh = tmpMeshPointArray.size();
    auto tmpMeshStart = reinterpret_cast<GfVec3f*>(tmpMeshPointArray.data());
    auto tmpMeshEnd = tmpMeshStart + sizeMesh;
    pointMeshArray.reserve(sizeMesh);
    pointMeshArray.insert(pointMeshArray.end(), tmpMeshStart, tmpMeshEnd);

    for (int i = 0; i < sizeMesh; ++i) {
      tmpVertexMesh.push_back(Vector3(pointMeshArray[i].GetArray()[0],
        pointMeshArray[i].GetArray()[1],
        pointMeshArray[i].GetArray()[2]));
    }

    //Normals.
    UsdAttribute tmpMeshNormals = inMesh.GetNormalsAttr();
    VtArray<GfVec3f> tmpMeshNormalArray;
    tmpMeshNormals.Get(&tmpMeshNormalArray);

    Vector<GfVec3f> norArrayMesh;

    uint32 sizeNorMesh = tmpMeshNormalArray.size();
    auto tmpMeshStartNor = reinterpret_cast<GfVec3f*>(tmpMeshNormalArray.data());
    auto tmpMeshEndNor = tmpMeshStartNor + sizeNorMesh;
    norArrayMesh.reserve(sizeNorMesh);
    norArrayMesh.insert(norArrayMesh.end(), tmpMeshStartNor, tmpMeshEndNor);

    for (int i = 0; i < sizeMesh; ++i) {
      tmpNormalsMesh.push_back(Vector3(norArrayMesh[i].GetArray()[0],
        norArrayMesh[i].GetArray()[1],
        norArrayMesh[i].GetArray()[2]));
    }

    //Faces.
    UsdAttribute tmpMeshFaces = inMesh.GetFaceVertexIndicesAttr();
    VtArray<int32> tmpMeshFacesArray;
    tmpMeshFaces.Get(&tmpMeshFacesArray);

    Vector<int32> faceMeshArray;

    uint32 sizeFaceMesh = tmpMeshFacesArray.size();

    auto tmpMeshStartFaces = tmpMeshFacesArray.data();
    auto tmpMeshEndFaces = tmpMeshStartFaces + sizeFaceMesh;
    faceMeshArray.reserve(sizeFaceMesh);
    faceMeshArray.insert(faceMeshArray.end(), tmpMeshStartFaces, tmpMeshEndFaces);

    for (int i = 0; i < sizeFaceMesh; ++i) {
      tmpFacesMesh.push_back(faceMeshArray[i]);
    }


    //UVs
    auto tmpUVs = inMesh.GetPrimvar(_tokens->st);
    VtArray<GfVec2f> tmpMeshUVsArray;
    tmpUVs.Get(&tmpMeshUVsArray);
    uint32 tmpSizeUV = tmpMeshUVsArray.size();

    Vector<GfVec2f> uvsArrayMesh;

    auto tmpMeshStartUV = reinterpret_cast<GfVec2f*>(tmpMeshUVsArray.data());
    auto tmpMeshEndUV = tmpMeshStartUV + tmpSizeUV;
    uvsArrayMesh.reserve(tmpSizeUV);
    uvsArrayMesh.insert(uvsArrayMesh.end(), tmpMeshStartUV, tmpMeshEndUV);

    for (int i = 0; i < tmpSizeUV; ++i) {
      tmpUVsMesh.push_back(Vector2(uvsArrayMesh[i].GetArray()[0],
        uvsArrayMesh[i].GetArray()[1]));
    }

    //Create the mesh.
    Vector<SimpleVertex> tmpVertexListMesh;
    //Set the vertex data to the Vector.
    for (int i = 0; i < sizeMesh; ++i) {
      //Create the vertex.
      SimpleVertex tmpSimpleVertexMesh;
      //Set positions.
      tmpSimpleVertexMesh.Pos = tmpVertexMesh[i];
      //Set UVs.
      tmpSimpleVertexMesh.Tex = tmpUVsMesh[i];
      //Set Normals.
      tmpSimpleVertexMesh.Nor = tmpNormalsMesh[i];

      //Set to the list.
      tmpVertexListMesh.push_back(tmpSimpleVertexMesh);

    }

    //TODO: Read the textures binded in the model and charge it from memory.             \\\\\\\\\\\\\\\\\\*
    Vector<ResourceRef> tmpTextureMesh;
    tmpTextureMesh.push_back(RM.m_missingTextureRef);

    //Create the own mesh.
    SharedPtr<Mesh> tmpMeshMesh = make_shared<Mesh>(tmpVertexListMesh, 
                                                    tmpFacesMesh, 
                                                    tmpTextureMesh);

    //Save a reference to the mesh.
    tmpMeshMesh->m_omniRefPath = inPath;

    return tmpMeshMesh;
    
  }

  void 
  Omni::setTransformOp(Vector3 inData, 
                       GI_OMNI_OP::E inOp, 
                       GI_OMNI_PRECISION::E inPrecision, 
                       StringView omniPath) {
    
    UsdGeomXformable xform(gStage->GetPrimAtPath(SdfPath(omniPath.data())));


    UsdGeomXformOp::Type op;
    switch (inOp) {
    case giEngineSDK::GI_OMNI_OP::kTRANSLATE:
      op = UsdGeomXformOp::TypeTranslate;
      break;
    case giEngineSDK::GI_OMNI_OP::kROTATE:
      op = UsdGeomXformOp::TypeRotateZYX;
      break;
    case giEngineSDK::GI_OMNI_OP::kSCALE:
      op = UsdGeomXformOp::TypeScale;
      break;
    }

    UsdGeomXformOp::Precision pr;
    switch (inPrecision) {
    case giEngineSDK::GI_OMNI_PRECISION::kDOUBLE:
      pr = UsdGeomXformOp::PrecisionDouble;
      break;
    case giEngineSDK::GI_OMNI_PRECISION::kFLOAT:
      pr = UsdGeomXformOp::PrecisionFloat;
      break;
    }

    bool resetXformStack = false;
    UsdGeomXformOp xformOp;
    Vector<UsdGeomXformOp> xFormOps = xform.GetOrderedXformOps(&resetXformStack);

    if (GI_OMNI_OP::kTRANSLATE == inOp) {
      xformOp = xFormOps[0];
    }
    else if (GI_OMNI_OP::kROTATE == inOp) {
      xformOp = xFormOps[1];
    }
    else if (GI_OMNI_OP::kSCALE == inOp) {
      xformOp = xFormOps[2];
    }

    SetOp(xform, xformOp, op, GfVec3d(inData.x, inData.y, inData.z), pr);

    gStage->Save();
  }

  void
  Omni::getFromSG() {
    auto& RM = g_resourceManager().instance();
    auto& sgraph = SceneGraph::instance();

    // Keep the model contained inside of "Root", only need to do this once per model
    SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);

    //Get the actor from the Scene Graph
    Vector<SharedPtr<Actor>> tmpActors = sgraph.getActorsFromRoot();

    for (auto actors : tmpActors) {

      if (actors->isStaticMesh) {
        
        // Create the geometry inside of "Root"
        SdfPath modelPath = rootPrimPath.AppendChild(TfToken(actors->m_actorName));
        UsdGeomMesh model = UsdGeomMesh::Define(gStage, modelPath);
        
        //Set the reference of the model in omni.
        actors->m_omniRefPath = modelPath.GetString();

        UsdGeomXformable xform(model);

        xform.AddXformOp(UsdGeomXformOp::TypeTranslate, UsdGeomXformOp::PrecisionDouble);
        xform.AddXformOp(UsdGeomXformOp::TypeRotateZYX, UsdGeomXformOp::PrecisionFloat);
        xform.AddXformOp(UsdGeomXformOp::TypeScale, UsdGeomXformOp::PrecisionFloat);


        if (!model) {
          return;
        }

        //Get the Static Mesh component
        SharedPtr<StaticMesh> tmpModelBase = static_pointer_cast<StaticMesh>(actors->getComponent(COMPONENT_TYPE::kStaticMesh));
        //Get the Model
        ResourceRef tmpModelRef = tmpModelBase->getModel();
        int32 noMesh = 0;

        auto tmpResource = RM.getResource(tmpModelRef.m_id);
        auto tmpModel = static_pointer_cast<Model>(tmpResource.lock());

        for (auto actualMesh : tmpModel->m_meshes) {
          // Create the geometry inside of "model_"
          String meshName("mesh_");
          meshName.append(std::to_string(noMesh));
          SdfPath meshPath = modelPath.AppendChild(TfToken(meshName));
          UsdGeomMesh mesh = UsdGeomMesh::Define(gStage, meshPath);

          //Set the reference of the mesh in omni.
          actualMesh->m_omniRefPath = meshPath.GetString();

          UsdGeomXformable xformMesh(mesh);

          xformMesh.AddXformOp(UsdGeomXformOp::TypeTranslate, UsdGeomXformOp::PrecisionDouble);
          xformMesh.AddXformOp(UsdGeomXformOp::TypeRotateZYX, UsdGeomXformOp::PrecisionFloat);
          xformMesh.AddXformOp(UsdGeomXformOp::TypeScale, UsdGeomXformOp::PrecisionFloat);

          if (!mesh) {
            return;
          }

          // Set orientation
          mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->rightHanded));

          //Get the num of vertex
          int32 num_vertices = actualMesh->m_vertexVector.size();
          //Get the vertex
          Vector<Vector3> vertex;
          vertex.reserve(num_vertices);
          for (int32 i = 0; i < num_vertices; i++) {
            vertex.push_back(actualMesh->m_vertexVector.at(i).Pos);
          }

          //Get the index
          auto tmpIndex = actualMesh->m_facesList;

          //Get Normals
          Vector<Vector3> Normals;
          Normals.reserve(num_vertices);
          for (int32 i = 0; i < num_vertices; i++) {
            Normals.push_back(actualMesh->m_vertexVector.at(i).Nor);
          }

          //Get UVs
          Vector<Vector2> uvs;
          uvs.reserve(num_vertices);
          for (int32 i = 0; i < num_vertices; i++) {
            uvs.push_back(actualMesh->m_vertexVector.at(i).Tex);
          }

          // Add all of the vertices
          VtArray<GfVec3f> points;
          points.resize(num_vertices);
          for (int32 i = 0; i < num_vertices; ++i) {
            points[i] = GfVec3f(vertex.at(i).x, vertex.at(i).y, vertex.at(i).z);
          }
          mesh.CreatePointsAttr(VtValue(points));

          // Calculate indices for each triangle
          int32 num_indices = tmpIndex.size(); // 2 Triangles per face * 3 Vertices per Triangle * 6 Faces
          VtArray<int32> vecIndices;
          vecIndices.resize(num_indices);
          for (int32 i = 0; i < num_indices; ++i) {
            vecIndices[i] = tmpIndex[i];
          }
          mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));

          // Add vertex normals
          int32 num_normals = Normals.size();
          VtArray<GfVec3f> meshNormals;
          meshNormals.resize(num_vertices);
          for (int32 i = 0; i < num_vertices; ++i) {
            meshNormals[i] = GfVec3f(Normals[i].x, Normals[i].y, Normals[i].z);
          }
          mesh.CreateNormalsAttr(VtValue(meshNormals));

          // Add face vertex count
          VtArray<int32> faceVertexCounts;
          faceVertexCounts.resize(num_indices / 3); // 2 Triangles per face * 6 faces
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
            int32 uv_count = uvs.size();
            VtVec2fArray valueArray;
            valueArray.resize(uv_count);
            for (int32 i = 0; i < uv_count; ++i) {
              valueArray[i].Set(uvs[i].x, uvs[i].y);
            }

            bool status = attr2.Set(valueArray);
          }
          attr2.SetInterpolation(UsdGeomTokens->vertex);
          rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(TfToken(meshName));
          noMesh++;

          //createMaterial(mesh, actualMesh, actors->m_actorName + "_" + meshName);

        }
      }
    }
    
    // Commit the changes to the USD
    gStage->Save();
    omniUsdLiveProcess();

    //return model;
  }
}