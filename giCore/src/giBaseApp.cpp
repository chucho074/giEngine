/**
 * @file    giBaseApp.cpp
 * @author  Jes�s Alberto Del Moral Cupil
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

  //Create the main window
  createWindow();

  //Initialize every system
  initSystems();
  auto& renderer = BaseRenderer::instance();

  //Send message to device
  onCreate();

  m_inputManager->init();

  renderer.create();

  //App Loop
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

      //Eventos propios
      event(msg);
    }
    m_inputManager->runEvents();
    //Update Time
    m_time->update();
    float deltaTime = g_time().getTime();

    //Update Game Logic
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

  //Get the window handle
  WindowHandle handle = m_window.getSystemHandle();

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
  //Start the inputManager
  if (m_loaderInput.loadPlugin("giInput_d.dll")) {
    auto createInputManager = reinterpret_cast<funCreateInputManager>(m_loaderInput.getProcedureByName("createInputManager"));

    BaseInput::startUp();
    BaseInput * input = createInputManager();
    g_inputManager().setObject(input);
    m_inputManager = &g_inputManager();
    
  }

  //Start the time
  Time::startUp();
  m_time = &g_time();

  //Start the Logger
  Logger::startUp();
  m_logger = &g_logger();

  //Start the Scene Graph
  SceneGraph::startUp();
  m_sceneGraph = &g_sceneGraph();

  //Activate the console only on Debug
#ifdef DEBUG
  activateConsole();
#endif
}

void 
BaseApp::destroySystems() {
  m_window.close();
  GraphicsAPI::shutDown();
  BaseRenderer::shutDown();
  Time::shutDown();
  Logger::shutDown();
  SceneGraph::shutDown();
}