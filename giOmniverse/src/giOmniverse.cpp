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
#include <giMath.h>
#include <giVector3.h>
#include <giTransform.h>
//#include "giMesh.h"

namespace giEngineSDK {

  void
  getFromSG();

  
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
  findGeomMesh(/*const String& existingStage*/) {
    
    //omniUsdLiveWaitForPendingUpdates();
    //// Open this file from Omniverse
    ////gStage = UsdStage::Open(existingStage);
    //if (!gStage) {
    //  failNotify("Failure to open stage in Omniverse:", existingStage.c_str());

    //  g_logger().SetError(ERROR_TYPE::kOmniConnection,
    //                      "Failure to open stage in Omniverse:" + existingStage);
    //  return UsdGeomMesh();
    //}

    //{
    //  std::unique_lock<std::mutex> lk(gLogMutex);
    //  ConsoleOut << "Existing stage opened: " << existingStage << ConsoleLine;
    //}

    //if (UsdGeomTokens->y != UsdGeomGetStageUpAxis(gStage)) {
    //  std::unique_lock<std::mutex> lk(gLogMutex);
    //  ConsoleOut << "Stage is not Y-up so live xform edits will be incorrect.  Stage is " 
    //             << UsdGeomGetStageUpAxis(gStage) << "-up" << ConsoleLine;
    //}

    //// Traverse the stage and return the first UsdGeomMesh we find
    //auto range = gStage->Traverse();
    //for (const auto& node : range) {
    //  if (node.IsA<UsdGeomMesh>()) {
    //    {
    //      std::unique_lock<std::mutex> lk(gLogMutex);
    //      ConsoleOut << "Found UsdGeomMesh: " << node.GetName() << ConsoleLine;
    //    }
    //    return UsdGeomMesh(node);
    //  }
    //}

    //// No UsdGeomMesh found in stage.
    //// (what kind of stage is this anyway!?) - idk man, just in case.
    //ConsoleOut << "ERROR: No UsdGeomMesh found in stage: " << existingStage << ConsoleLine;
    //g_logger().SetError(ERROR_TYPE::kOmniConnection,
    //                    "ERROR: No UsdGeomMesh found in stage: " + existingStage);
    //return UsdGeomMesh();

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
    // Make path for "/Root/Looks/Fieldstone".
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


    //TODO:
    // Meter en un for para todas las texturas del mesh
    // Obtener el tipo de textura que es segun lo que soporta el motor
    // En base a la informacion del tipo de textura, dar un string para el nombre
    // Guardar la informacion dentro de un vector de tipo UsdShadeOutput
    String tmpTextureName;
    String tmpFileName;
    TfToken tmpTextureToken;
    Vector<UsdShadeOutput> tmpOuputShaders; 
    for (auto textures : inOwnMesh.m_textures) {
      
      if (textures.type == "texture_diffuse") {
        //The name of the texture.
        tmpTextureName = "DiffuseColorTex";
        //The token of the texture.
        tmpTextureToken = _tokens->sRGB;
        //The name of the file.
        tmpFileName = "BaseColor";
      }
      
      if (textures.type == "texture_normal") {
        tmpTextureName = "NormalTex";

        tmpTextureToken = _tokens->RAW;

        tmpFileName = "Norm";
      }

      if (textures.type == "texture_specular") {
        break;
      }
      
      if (textures.type == "texture_shininess") {
        break;
      }

      // Create the shader.
      String tmpShaderName = materialName + tmpTextureName;
      //String tmpFilePath = "./Materials/" + tmpFileName + ".png";
      String tmpFilePath = "./Materials" + textures.path;
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
      //exit(1);
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
  Omni::createEmptyUSD(String inProjectName) {
    
    // Create an empty folder, just as an example
    createEmptyFolder(m_destinationPath + inProjectName);
    // Saving the new existing stage
    m_existingStage = m_destinationPath + inProjectName;
    // Saving the destination path with the projectName
    m_destinationPath = m_existingStage;

    m_existingStage += "/scene.usd";
  }

  void 
  Omni::createSGFromUSD() {

    auto& gapi = g_graphicsAPI();
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

    // Traverse the stage and return the first UsdGeomMesh we find.
    auto range = gStage->Traverse();
    for (const auto& node : range) {
      if (node.IsA<UsdGeomMesh>()) {
          std::unique_lock<std::mutex> lk(gLogMutex);

          SharedPtr<Actor> tmpActor;

          SharedPtr<Model> tmpModel;

          tmpActor.reset(new Actor);

          tmpModel.reset(new Model);

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

                  Vector<Vector3> tmpVertexMesh;
                  Vector<Vector3> tmpNormalsMesh;
                  Vector<uint32>  tmpFacesMesh;
                  //Points / Vertex.
                  UsdAttribute tmpMeshVertex = meshGeoMesh.GetPointsAttr();
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
                  UsdAttribute tmpMeshNormals = meshGeoMesh.GetNormalsAttr();
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
                  UsdAttribute tmpMeshFaces = meshGeoMesh.GetFaceVertexIndicesAttr();
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

                  //Create the mesh.
                  Vector<SimpleVertex> tmpVertexListMesh;
                  //Set the vertex data to the Vector.
                  for (int i = 0; i < sizeMesh; ++i) {
                    //Create the vertex.
                    SimpleVertex tmpSimpleVertexMesh;
                    //Set positions.
                    tmpSimpleVertexMesh.Pos = tmpVertexMesh[i];
                    //Set UVs.
                    //tmpSimpleVertexMesh.Tex = {0.f, 0.f};
                    //Set Normals.
                    tmpSimpleVertexMesh.Nor = tmpNormalsMesh[i];

                    //Set to the list.
                    tmpVertexListMesh.push_back(tmpSimpleVertexMesh);

                  }

                  //TODO: Read the textures binded in the model and charge it from memory.      \\\\\\\\\\\\\\\\\\*
                  Vector<Texture> tmpTextureMesh;

                  Texture texture;
                  texture.texture = gapi.TextureFromFile("/missingTexture.png", "Resources/");
                  SamplerDesc sampDesc;
                  sampDesc.filter = GI_FILTER::kFILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
                  sampDesc.addressU = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
                  sampDesc.addressV = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
                  sampDesc.addressW = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
                  sampDesc.comparisonFunc = 1;
                  sampDesc.minLOD = 0;
                  sampDesc.maxLOD = 3.402823466e+38f;
                  texture.samplerState = gapi.createSampler(sampDesc);
                  tmpTextureMesh.push_back(texture);

                  Mesh tmpMeshMesh(tmpVertexListMesh, tmpFacesMesh, tmpTextureMesh);

                  //Save a reference to the mesh.
                  tmpMeshMesh.m_omniRefPath = tmpIter.GetPath().GetString();

                  //Set in the meshes.
                  tmpModel->m_meshes.push_back(tmpMeshMesh);

                }
              }
            }
            else {
              //Case of just a model without multiple meshes
              Vector<GfVec3f> pointArray;
              
              uint32 size = tmpPointArray.size();
              auto tmpStart = reinterpret_cast<GfVec3f*>(tmpPointArray.data());
              auto tmpEnd = tmpStart + size;
              pointArray.reserve(size);
              pointArray.insert(pointArray.end(), tmpStart, tmpEnd);
              
              for (int i = 0; i < size; ++i) {
              tmpVertexModel.push_back(Vector3(pointArray[i].GetArray()[0],
                                               pointArray[i].GetArray()[1],
                                               pointArray[i].GetArray()[2]));
              }
              
              //Normals.
              UsdAttribute tmpNormals = geoMesh.GetNormalsAttr();
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
              
              //Faces.
              UsdAttribute tmpFaces = geoMesh.GetFaceVertexIndicesAttr();
              VtArray<int32> tmpFacesArray;
              tmpFaces.Get(&tmpFacesArray);
              
              Vector<int32> faceArray;
              
              uint32 sizeFace = tmpFacesArray.size();
              auto tmpStartFaces = tmpFacesArray.data();
              auto tmpEndFaces = tmpStartFaces + sizeFace;
              faceArray.reserve(sizeFace);
              faceArray.insert(faceArray.end(), tmpStartFaces, tmpEndFaces);
              
              for (int i = 0; i < sizeFace; ++i) {
                tmpFacesModel.push_back(faceArray[i]);
              }
              
              //Create the mesh.
              Vector<SimpleVertex> tmpVertexList;
              //Set the vertex data to the Vector.
              for (int i = 0; i < size; ++i) {
                //Create the vertex.
                SimpleVertex tmpSimpleVertex;
                //Set positions.
                tmpSimpleVertex.Pos = tmpVertexModel[i];
                //Set UVs.
                
                //Set Normals.
                tmpSimpleVertex.Nor = tmpNormalsModel[i];
              
                //Set to the list.
                tmpVertexList.push_back(tmpSimpleVertex);

              }

              //TODO: Read the textures binded in the model and charge it from memory.      \\\\\\\\\\\\\\\\\\*
              Vector<Texture> tmpTexture;
              Texture texture;
              texture.texture = gapi.TextureFromFile("/missingTexture.png", "Resources/");
              SamplerDesc sampDesc;
              sampDesc.filter = GI_FILTER::kFILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT;
              sampDesc.addressU = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
              sampDesc.addressV = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
              sampDesc.addressW = GI_TEXTURE_ADDRESS_MODE::kTEXTURE_ADDRESS_WRAP;
              sampDesc.comparisonFunc = 1;
              sampDesc.minLOD = 0;
              sampDesc.maxLOD = 3.402823466e+38f;
              texture.samplerState = gapi.createSampler(sampDesc);
              tmpTexture.push_back(texture);
              Mesh tmpMesh(tmpVertexList, tmpFacesModel, tmpTexture);
              
              //Save a reference to the mesh.
              tmpMesh.m_omniRefPath = node.GetPath().GetString();

              //Set in the meshes.
              tmpModel->m_meshes.push_back(tmpMesh);
            }
            
            //Set the actor model to the Root in SG.
            tmpActor->m_actorName = node.GetName();
            SharedPtr<StaticMesh> modelComponent = make_shared<StaticMesh>();
            modelComponent->setModel(tmpModel);
            tmpActor->addComponent(modelComponent, COMPONENT_TYPE::kStaticMesh);
            tmpActor->m_omniRefPath = node.GetPath().GetString();
            sgraph.addActor(tmpActor, sgraph.getRoot());

          }
      }
    }
  }

  void 
  Omni::setTransformOp(Vector3 inData, 
                       GI_OMNI_OP::E inOp, 
                       GI_OMNI_PRECISION::E inPrecision, 
                       String omniPath) {
    
    UsdGeomXformable xform(gStage->GetPrimAtPath(SdfPath(omniPath)));


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
  getFromSG() {
    auto& sgraph = SceneGraph::instance();

    // Keep the model contained inside of "Root", only need to do this once per model
    SdfPath rootPrimPath = SdfPath::AbsoluteRootPath().AppendChild(_tokens->Root);
    UsdGeomXform::Define(gStage, rootPrimPath);

    //Get the actor from the Scene Graph
    Vector<SharedPtr<Actor>> tmpActors = sgraph.getActorsFromRoot();

    for (auto actors : tmpActors) {

      if (actors->isStaticMesh) {
        
        // Create the geometry inside of "Root"
        SdfPath modelPath = rootPrimPath.AppendChild(TfToken(actors->m_actorName));
        UsdGeomMesh model = UsdGeomMesh::Define(gStage, modelPath);

        if (!model) {
          return;
        }

        //Get the Static Mesh component
        SharedPtr<StaticMesh> tmpModelBase = static_pointer_cast<StaticMesh>(actors->getComponent(COMPONENT_TYPE::kStaticMesh));
        //Get the Model
        SharedPtr<Model> tmpModel = tmpModelBase->getModel();
        int32 noMesh = 0;

        for (auto actualMesh : tmpModel->m_meshes) {
          // Create the geometry inside of "model_"
          String meshName("mesh_");
          meshName.append(std::to_string(noMesh));
          SdfPath meshPath = modelPath.AppendChild(TfToken(meshName));
          UsdGeomMesh mesh = UsdGeomMesh::Define(gStage, meshPath);

          if (!mesh) {
            return;
          }

          // Set orientation
          mesh.CreateOrientationAttr(VtValue(UsdGeomTokens->leftHanded));

          //Get the num of vertex
          int32 num_vertices = actualMesh.m_vertexVector.size();
          //Get the vertex
          Vector<Vector3> vertex;
          vertex.reserve(num_vertices);
          for (int32 i = 0; i < num_vertices; i++) {
            vertex.push_back(actualMesh.m_vertexVector.at(i).Pos);
          }

          //Get the index
          auto tmpIndex = actualMesh.m_facesList;

          //Get Normals
          Vector<Vector3> Normals;
          Normals.reserve(num_vertices);
          for (int32 i = 0; i < num_vertices; i++) {
            Normals.push_back(actualMesh.m_vertexVector.at(i).Nor);
          }

          //Get UVs
          Vector<Vector2> uvs;
          uvs.reserve(num_vertices);
          for (int32 i = 0; i < num_vertices; i++) {
            uvs.push_back(actualMesh.m_vertexVector.at(i).Tex);
          }

          // Add all of the vertices
          VtArray<GfVec3f> points;
          points.resize(num_vertices);
          for (int32 i = 0; i < num_vertices; i++) {
            points[i] = GfVec3f(vertex.at(i).x, vertex.at(i).y, vertex.at(i).z);
          }
          mesh.CreatePointsAttr(VtValue(points));

          // Calculate indices for each triangle
          int32 num_indices = tmpIndex.size(); // 2 Triangles per face * 3 Vertices per Triangle * 6 Faces
          VtArray<int32> vecIndices;
          vecIndices.resize(num_indices);
          for (int32 i = 0; i < num_indices; i++) {
            vecIndices[i] = tmpIndex[i];
          }
          mesh.CreateFaceVertexIndicesAttr(VtValue(vecIndices));

          // Add vertex normals
          int32 num_normals = Normals.size();
          VtArray<GfVec3f> meshNormals;
          meshNormals.resize(num_vertices);
          for (int32 i = 0; i < num_vertices; i++) {
            meshNormals[i] = GfVec3f(Normals[i].x, Normals[i].y, Normals[i].z);
          }
          mesh.CreateNormalsAttr(VtValue(meshNormals));

          // Add face vertex count
          VtArray<int32> faceVertexCounts;
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

          createMaterial(mesh, actualMesh, actors->m_actorName + "_" + meshName);

        }
      }
    }
    
    // Commit the changes to the USD
    gStage->Save();
    omniUsdLiveProcess();

    //return model;
  }
}