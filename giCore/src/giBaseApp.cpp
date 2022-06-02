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

  //Create the main window.
  createWindow();

  //Initialize every system.
  initSystems();

  auto& renderer = BaseRenderer::instance();

  //Send message to device.
  onCreate();

  //Initialize the inputs.
  m_inputManager->init();

  //Create the renderer.
  renderer.create();

  //Create the Omniverse conection.
  m_omniverse->init(EngineConfigs::s_existingStage, 
                    EngineConfigs::s_destinationPath);
  //m_omniverse->startConection();


  //App Loop.
  HWND hWnd = m_window.getSystemHandle();
  while (m_window.isOpen()) {
    m_inputManager->update();
    MSG msg;
    Event eventsWnd;
    while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);

      m_inputManager->sendEvent(msg);
      
      m_window.pollEvent(eventsWnd);
      if (eventsWnd.type == Event::Closed) {
        m_window.close();
        break;
      }
      if (eventsWnd.type == Event::Resized) {
        EngineConfigs::s_resolution = { m_window.getSize().x, m_window.getSize().y };
        m_width = EngineConfigs::s_resolution.x;
        m_height = EngineConfigs::s_resolution.y;
        //Unbind everything
        //Resize backbuffer
        //Resize other Textures {Albedo, pos, norm, SSAO, Bluhrs, Light}
        //Set the information to the ui
      }

      //Eventos propios.
      event(msg);
    }
    m_inputManager->runEvents();

    //Update Time.
    m_time->update();
    float deltaTime = g_time().getTime();

    //Update Game Logic.
    update(deltaTime);
    
    //Render Frame
    renderer.render();
    render();

    
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
BaseApp::update(float inDeltaTime) {
  onUpdate(inDeltaTime);
  //m_omniverse->update();
}

void 
BaseApp::render() {
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
  if (m_loaderOmniverse.loadPlugin("giOmniverse_d.dll")) {
    auto createOmniverse = reinterpret_cast<funCreateOmniverse>(m_loaderOmniverse.getProcedureByName("createOmniverse"));

    BaseOmni::startUp();
    BaseOmni* ov = createOmniverse();
    g_omniverse().setObject(ov);
    m_omniverse = &g_omniverse();
  }

}

void 
BaseApp::destroySystems() {
  m_window.close();
  BaseRenderer::shutDown();
  GraphicsAPI::shutDown();
  SceneGraph::shutDown();
  BaseOmni::shutDown();
  Time::shutDown();
  Logger::shutDown();
}