/**
 * @file    giBaseApp.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    27/08/2020
 * @brief   A class for the basics functions of the apps.
 * @bug     No known Bugs.
 */

/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giBaseGraphicsAPI.h"
#include <SFML/Window.hpp>
#include <SFML/Window/WindowBase.hpp>
#include "giLibraryLoader.h"


#include <iostream>         //Delete this
#include <io.h>             //Delete this
#include <fcntl.h>          //Delete this

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
class BaseApp 
{
 public:

  ///Default constructor
  BaseApp() = default;

  ///Destructor
  ~BaseApp();

  /**
   * @brief    Runs the app.
   * @bug      No known Bugs.
   * @return   Returns a 0 if its ok.
   */
  int 
  run();

 protected:
  /**
   * @brief    Virtual Method in charge of creating a virtual method.
   * @bug      No known Bugs.
   */
  virtual void 
  onCreate() = 0;

  /**
   * @brief    Virtual Method in charge of destroying the settings and members.
   * @bug      No known Bugs.
   */
  virtual void 
  onDestroy() = 0;

  /**
   * @brief    Virtual method in charge to updating the logical information.
   * @param    inDeltaTime    For update the game time.
   * @bug      No known Bugs.
   */
  virtual void 
  onUpdate(float inDeltaTime = 0) { (void)inDeltaTime; };

  /**
   * @brief    Virtual method in charge of drawing on screen all the visual info.
   * @bug      No known Bugs.
   */
  virtual void 
  onRender() = 0;

  /**
   * @brief    Method in charge of get the events of the window
   * @param    
   * @bug      No known Bugs.
   */
  virtual void 
  onEvent(Event inEvent)  = 0;

 private:
  /**
   * @brief    Method in charge of drawing on the screen all the visual info.
   * @bug      No known Bugs.
   */
  void 
  createWindow();

  /**
   * @brief    Method in charge of updates the logic info.
   * @param    inDeltaTime 
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

  /**
   * @brief    Method that actives the console.
   * @bug      No known Bugs.
   */
  void 
  activateConsole();


 public:
  /**
   * @brief    Method that set the events and messages for the game.
   * @param    inHw      The HWND
   * @param    msg       The message
   * @param    wParam    The W Parameter
   * @param    lParam    The L Parameter
   * @bug      No known Bugs.
   * @return   Returns the result of the handle event.
   */
  //static LRESULT CALLBACK handleWindowEvent(HWND inHw, UINT msg, WPARAM wParam, LPARAM lParam);

  ///The Width of the window with a default size
  int m_width = 640;
  
  ///The Height of the window with a default size
  int m_height = 480;
  
  ///The reference of the window
  WindowBase m_window;

  //
  LibraryLoader m_loader;

  CBaseGraphicsAPI* m_GAPI = nullptr;
};

