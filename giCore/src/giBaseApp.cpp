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


BaseApp::~BaseApp() {

}

int 
BaseApp::run() {
  //Initialize every system
  initSystems();

  //Create the main window
  createWindow();

  //Send message to device
  onCreate();

  //Main Loop
  MSG msg = { 0 };
  while (WM_QUIT != msg.message) {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      //Eventos propios
      onEvent(msg.message, msg.wParam);
    }
    else {

      //Update Time
      static float t = 0.0f;
      static int dwTimeStart = 0;
      int dwTimeCur = GetTickCount();
      if (dwTimeStart == 0) {
        dwTimeStart = dwTimeCur;
      }
      t = (dwTimeCur - dwTimeStart) / 1000.0f;

      //Update Game Logic
      update(t);

      //Render Frame
      render();
    }
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
  
  m_window.create(VideoMode(m_width, m_height),
  /**************/"Default Title",
  /**************/sf::Style::Default);

  m_window.setPosition({ 0,0 });

  //Focus
  //m_windowHasFocus = m_window.hasFocus();
}

void 
BaseApp::update(float inDeltaTime) {
  onUpdate(inDeltaTime);
}

void 
BaseApp::render() {
  onRender();
}

void 
BaseApp::initSystems() {

  //Get the window handle
  WindowHandle handle = m_window.getSystemHandle();


  CBaseGraphicsAPI::startUp();

  //Initialize the Graphics API
  g_GraphicsAPI().init(handle, m_width, m_height);

  //Activate the console only on Debug
#ifdef DEBUG
  activateConsole();
#endif
}

void 
BaseApp::destroySystems() {
  CBaseGraphicsAPI::shutDown();
}

void 
BaseApp::activateConsole() {

  AllocConsole();

  HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
  FILE* COutputHandle = _fdopen(SystemOutput, "w");

  HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
  int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
  FILE* CErrorHandle = _fdopen(SystemError, "w");

  HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
  int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
  FILE* CInputHandle = _fdopen(SystemInput, "r");

  std::ios::sync_with_stdio(true);

  freopen_s(&CInputHandle, "CONIN$", "r", stdin);
  freopen_s(&COutputHandle, "CONOUT$", "w", stdout);
  freopen_s(&CErrorHandle, "CONOUT$", "w", stderr);

  std::wcout.clear();
  std::cout.clear();
  std::wcerr.clear();
  std::cerr.clear();
  std::wcin.clear();
  std::cin.clear();
}

LRESULT 
BaseApp::handleWindowEvent(HWND inHw, UINT inMsg, WPARAM inwParam, LPARAM inlParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  switch (inMsg) {
  case WM_PAINT: {
    hdc = BeginPaint(inHw, &ps);
    EndPaint(inHw, &ps);
    break;
  }
  case WM_DESTROY: {
    PostQuitMessage(0);
    break;
  }


  default: {

    return DefWindowProc(inHw, inMsg, inwParam, inlParam);
    break;
  }
  }


}

namespace giEngineSDK {
  CBaseGraphicsAPI&
  g_GraphicsAPI() {
    return CBaseGraphicsAPI::instance();
  }
}