/**
 * @file    giBaseApp.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/08/2020
 * @brief   A class for the basics functions of the apps.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#include "giBaseApp.h"
#include "giBaseGraphicsAPI.h"
#include "giBaseRenderer.h"
#include "giBaseInput.h"



int32 
BaseApp::run() {

  //EngineConfigs::s_activePlugins.insert({GIPLUGINS::kOmniverse, true});
  m_configs->s_activePlugins.insert({ GIPLUGINS::kgiAMR, true });

  //Create the main window.
  createWindow();

  //Initialize every system.
  initSystems();

  //Send message to device.
  create();

  //App Loop.
  MSG msg;
  Event eventsWnd;
  HWND hWnd = m_window.getSystemHandle();
  while (m_window.isOpen()) {

    //m_deltaTime = m_appClock.getElapsedTime().asSeconds();
    m_deltaTime = m_appClock.restart().asSeconds();

    if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      
      m_window.pollEvent(eventsWnd);
      if (eventsWnd.type == Event::Closed) {
        m_window.close();
        break;
      }
      if (eventsWnd.type == Event::Resized) {
        m_configs->s_resolution = { (int32)m_window.getSize().x, 
                                        (int32)m_window.getSize().y };
        m_width = m_configs->s_resolution.x;
        m_height = m_configs->s_resolution.y;
        //Unbind everything
        //Resize backbuffer
        //Resize other Textures {Albedo, pos, norm, SSAO, Bluhrs, Light}
        //Set the information to the ui
      }

      //Eventos propios.
      event(msg);
    }
    else {

      //Update Time.
      m_time->update();
      //float deltaTime = g_time().getTime();

      //Update Game Logic.
      update(m_deltaTime);

      //Render Frame
      render();
    }
  }

  //Write the logs
  m_logger->SendToFile();

  //Destroy the resources
  onDestroy();

  return 0;
}

void 
BaseApp::createWindow() {
  
  if (m_window.isOpen()) {
    return;
  }
  
  String tmpTitle = "giEngine";

  m_window.create(VideoMode(m_width, m_height),
                  tmpTitle.c_str(),
                  sf::Style::Default);

  m_window.setPosition({ 0, 0 });

  
}

void 
BaseApp::create() {
  //Create externs.
  onCreate();

  //Create the renderer.
  m_renderer->create();

  //Evaluate if Omniverse is active.
  auto iter = m_configs->s_activePlugins.find(GIPLUGINS::kOmniverse);
  if (iter != m_configs->s_activePlugins.end()) {

    //Create the Omniverse conection.
    m_omniverse->init(m_configs->s_existingStage,
                      m_configs->s_destinationPath);
    m_omniverse->startConection();

  }
}

void 
BaseApp::update(float inDeltaTime) {
  m_inputManager->update();
  onUpdate(inDeltaTime);

  m_renderer->update();

  if (nullptr != m_omniverse) {
    m_omniverse->update();
  }
}

void 
BaseApp::render() {
  m_renderer->render();
  onRender();
  m_gapi->show();

}

void 
BaseApp::event(MSG inMsg) {
  onEvent(inMsg);
}

void 
BaseApp::initSystems() {

  //Start the time
  Time::startUp();
  m_time = &g_time();

  //Start the configs
  EngineConfigs::startUp();
  m_configs = &g_engineConfigs();

  //Start the Logger
  Logger::startUp();
  m_logger = &g_logger();

  //Get the window handle
  WindowHandle handle = m_window.getSystemHandle();

  //Start the inputManager
  if (m_loaderInput.loadPlugin("giInput_d.dll")) {
    auto createInputManager = reinterpret_cast<funCreateInputManager>(m_loaderInput.getProcedureByName("createInputManager"));

    BaseInput::startUp();
    BaseInput* input = createInputManager();
    g_inputManager().setObject(input);
    m_inputManager = &g_inputManager();
    //Initialize the inputs.
    m_inputManager->init(m_window.getSystemHandle());
    m_inputManager->updateSize(m_width, m_height);

  }

  //Start the Graphics
  if (m_loaderGAPI.loadPlugin("giDirectX_d.dll")) {
    auto createGraphicsAPI = reinterpret_cast<funCreateGraphicsAPI>(m_loaderGAPI.getProcedureByName("createGraphicsAPI"));

    GraphicsAPI::startUp();
    GraphicsAPI * GAPI = createGraphicsAPI();
    g_graphicsAPI().setObject(GAPI);
    m_gapi = &g_graphicsAPI();
    //Initialize the Graphics API
    m_gapi->init(reinterpret_cast<void*>(handle));
  }

  //Start the Renderer
  if (m_loaderRenderer.loadPlugin("giRenderer_d.dll")) {
    auto createRenderer = reinterpret_cast<funCreateRenderer>(m_loaderRenderer.getProcedureByName("createRenderer"));

    BaseRenderer::startUp();
    BaseRenderer* renderer = createRenderer();
    g_renderer().setObject(renderer);
    m_renderer = &g_renderer();
    
  }

  //Start the Scene Graph
  SceneGraph::startUp();
  m_sceneGraph = &g_sceneGraph();

  //Start the Omniverse
  auto iter = m_configs->s_activePlugins.find(GIPLUGINS::kOmniverse);
  if (iter != m_configs->s_activePlugins.end()) {
    if (m_loaderOmniverse.loadPlugin("giOmniverse_d.dll")) {
      auto createOmniverse = reinterpret_cast<funCreateOmniverse>(m_loaderOmniverse.getProcedureByName("createOmniverse"));

      BaseOmni::startUp();
      BaseOmni* ov = createOmniverse();
      g_omniverse().setObject(ov);
      m_omniverse = &g_omniverse();
    }
  }
  
  //Start giAMR
  auto iterAmr = m_configs->s_activePlugins.find(GIPLUGINS::kgiAMR);
  if (iterAmr != m_configs->s_activePlugins.end()) {
    if (m_loaderAMR.loadPlugin("giAMR_d.dll")) {
      auto createAMR = reinterpret_cast<funCreateAMR>(m_loaderAMR.getProcedureByName("createAMR"));

      BaseAMR::startUp();
      BaseAMR* amr = createAMR();
      g_AMR().setObject(amr);
      m_AMR = &g_AMR();
    }
  }
}

void 
BaseApp::destroySystems() {
  m_window.close();
  m_renderer->shutDown();
  m_gapi->shutDown();
  m_sceneGraph->shutDown();
  m_omniverse->shutDown();
  m_time->shutDown();
  m_logger->shutDown();
  m_configs->shutDown();
}

void 
BaseApp::readConfigs() {
  
}
