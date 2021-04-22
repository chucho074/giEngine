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


int 
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
    static int dwTimeStart = 0;
    int dwTimeCur = getGetTickCount();
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
  /**************/tmpTitle.c_str(),
  /**************/sf::Style::Default);

  m_window.setPosition({ 0, 0 });

  
}

void 
BaseApp::update(float inDeltaTime) {
  onUpdate(inDeltaTime);
}

void 
BaseApp::render() {
  onRender();
  m_GAPI->show();
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
    m_GAPI = &g_GraphicsAPI();
    //Initialize the Graphics API
    m_GAPI->init(reinterpret_cast<void*>(handle), 
    /***********/m_width, 
    /***********/m_height);
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

void 
BaseApp::activateConsole() {

  //AllocConsole();

  //HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  //int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
  //FILE* COutputHandle = _fdopen(SystemOutput, "w");

  //HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
  //int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
  //FILE* CErrorHandle = _fdopen(SystemError, "w");

  //HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
  //int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
  //FILE* CInputHandle = _fdopen(SystemInput, "r");

  //std::ios::sync_with_stdio(true);

  //freopen_s(&CInputHandle, "CONIN$", "r", stdin);
  //freopen_s(&COutputHandle, "CONOUT$", "w", stdout);
  //freopen_s(&CErrorHandle, "CONOUT$", "w", stderr);

  //std::wcout.clear();
  //std::cout.clear();
  //std::wcerr.clear();
  //std::cerr.clear();
  //std::wcin.clear();
  //std::cin.clear();
}