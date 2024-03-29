/**
 * @file    giBaseConfig.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giModule.h>
#include <giVector2i.h>
#include <giStdHeaders.h>

using namespace giEngineSDK;

namespace GIENGINE_API {
  enum E {
    kDX11 = 0, 
    kDX12, 
    kOGL,
    kVK13,
    kNumOfSuportedApis
  };
}

namespace GIPLUGINS {
  enum E {
    kOmniverse = 0,
    kgiAMR,
    kNumOfSuportedPlugins
  };
}

class EngineConfigs : public Module<EngineConfigs>
{
 public:
   EngineConfigs() = default;
   ~EngineConfigs() = default;

  //Basic App Configs
  static Vector2i s_resolution;
  static bool s_fullscreen;
  static bool s_maximized;
  static String s_projectName;
  static GIENGINE_API::E s_activeGraphicApi;
  static Path s_projectPath;


  //Plugins
  static Map<GIPLUGINS::E, bool> s_activePlugins;

  //Omniverse settings
  static String s_existingStage;
  static String s_destinationPath;

  //Editor settings


};

EngineConfigs&
g_engineConfigs();
