/**
 * @file    giBaseApp.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/08/2020
 * @brief   A class for the basics functions of the apps.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include <SFML/Window.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <giLibraryLoader.h>
#include <giTime.h>
#include <giLogger.h>
#include "giPrerequisitesCore.h"
#include "giBaseGraphicsAPI.h"
#include "giBaseRenderer.h"
#include "giSceneGraph.h"
#include "giBaseInput.h"
#include "giBaseOmniverse.h"
#include "giBaseConfig.h"

using namespace giEngineSDK;

using sf::VideoMode;
using sf::Window;
using sf::WindowBase;
using sf::WindowHandle;
using sf::Event;

/**
 * @class    BaseApp.
 * @brief    A class for the basics functions of the apps.
 * @bug      No known Bugs.
 */
class GI_CORE_EXPORT BaseApp
{
 public:

  ///Default constructor
  BaseApp() = default;

  ///Destructor
  virtual
  ~BaseApp() = default;

  /**
   * @brief    Runs the app.
   * @bug      No known Bugs.
   * @return   Returns a 0 if it's ok.
   */
  int32 
  run();

  /**
   * @brief    Virtual Method in charge of creating a virtual method.
   * @bug      No known Bugs.
   */
  virtual void 
  onCreate() {};

  /**
   * @brief    Virtual Method in charge of destroying the settings and members.
   * @bug      No known Bugs.
   */
  virtual void 
  onDestroy() {};

  /**
   * @brief    Virtual method in charge to updating the logical information.
   * @param    inDeltaTime     For update the game time.
   * @bug      No known Bugs.
   */
  virtual void 
  onUpdate(float inDeltaTime = 0) { 
    (void)inDeltaTime; 
  };

  /**
   * @brief    Virtual method in charge of drawing on screen all the visual info.
   * @bug      No known Bugs.
   */
  virtual void 
  onRender() {};

  /**
   * @brief    Method in charge of get the events of the window
   * @param    inMsg           The message to process.
   * @bug      No known Bugs.
   */
  virtual void 
  onEvent(MSG inMsg) {
    GI_UNREFERENCED_PARAMETER(inMsg);
  };

 private:
  /**
   * @brief    Method in charge of drawing on the screen all the visual info.
   * @bug      No known Bugs.
   */
  void 
  createWindow();

  /**
   * @brief    Method in charge of the creation of the information.
   */
  void
  create();

  /**
   * @brief    Method in charge of updates the logic info.
   * @param    inDeltaTime     The delta time.
   * @bug      No known Bugs.
   */
  void 
  update(float inDeltaTime);

  /**
   * @brief    Method that draw the information Not Modified Func.
   * @bug      No known Bugs.
   */
  void 
  render();

  /**
   * @brief    Method in charge of destroy the information used.
   */
  void
  destroy();
  
  /**
   * @brief    Method that draw the information Not Modified Func.
   * @bug      No known Bugs.
   */
  void 
  processEvent(MSG inMsg);

  /**
   * @brief    Method that initialize the modules and plug-ins for the engine.
   * @bug      No known Bugs.
   */
  void 
  initSystems();
  
  /**
   * @brief    Method that destroys the systems of the engine.
   * @bug      No known Bugs.
   */
  void 
  destroySystems();


 public:
  
  ///The Width of the window with a default size.
  uint32 m_width = EngineConfigs::s_resolution.x;
  
  ///The Height of the window with a default size.
  uint32 m_height = EngineConfigs::s_resolution.y;
  
  ///The reference of the window.
  WindowBase m_window;

  //
  LibraryLoader m_loaderGAPI;

  LibraryLoader m_loaderRenderer;

  LibraryLoader m_loaderInput;

  LibraryLoader m_loaderOmniverse;

  GraphicsAPI* m_gapi = nullptr;

  BaseRenderer* m_renderer = nullptr;

  SceneGraph * m_sceneGraph = nullptr;
  
  ResourceManager * m_resoureceManager = nullptr;

  Time * m_time = nullptr;

  Logger * m_logger = nullptr;

  BaseInput * m_inputManager = nullptr;

  BaseOmni * m_omniverse = nullptr;

  sf::Clock m_appClock;

  float m_deltaTime = 0.f;
};