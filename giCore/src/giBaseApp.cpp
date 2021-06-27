/**
 * @file    giBaseApp.cpp
 * @author  Jesús Alberto Del Moral Cupil
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


int32 
BaseApp::run() {

  //Create the main window
  createWindow();

  //Initialize every system
  initSystems();

  //Send message to device
  onCreate();

  //App Loop
  while (m_window.isOpen()) {
    Event eventsWnd;
    while (m_window.pollEvent(eventsWnd)) {
      if (eventsWnd.type == Event::Closed) {
        m_window.close();
        break;
      }
      
      //Eventos propios
      onEvent(eventsWnd);
    }


    //Update Time
    /*static float t = 0.0f;
    static int32 dwTimeStart = 0;
    int32 dwTimeCur = getGetTickCount();
    if (dwTimeStart == 0) {
      dwTimeStart = dwTimeCur;
    }
    t = (dwTimeCur - dwTimeStart) / 1000.0f;*/
    
    //Update Game Logic
    update(/*t*/0);
    
    //Render Frame
    render();
    
  }

  //Destroy the resources
  onDestroy();


  return 0;
}

void 
BaseApp::createWindow() {
  
  if (m_window.isOpen()) {
    return;
  }
  
  String tmpTitle = "Changos wapos";

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
BaseApp::initSystems() {

  //Get the window handle
  WindowHandle handle = m_window.getSystemHandle();

  if (m_loader.loadPlugin("giDirectX_d.dll")) {
    auto createGraphicsAPI = reinterpret_cast<funCreateGraphicsAPI>(m_loader.getProcedureByName("createGraphicsAPI"));

    GraphicsAPI::startUp();
    GraphicsAPI* GAPI = createGraphicsAPI();
    g_GraphicsAPI().setObject(GAPI);
    m_gapi = &g_GraphicsAPI();
    //Initialize the Graphics API
    m_gapi->init(reinterpret_cast<void*>(handle));
  }


  

  //Activate the console only on Debug
#ifdef DEBUG
  activateConsole();
#endif
}

void 
BaseApp::destroySystems() {
  m_window.close();
  GraphicsAPI::shutDown();
}