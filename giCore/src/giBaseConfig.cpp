/**
 * @file    giBaseConfig.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giBaseConfig.h"

//Basoc App Configs
Vector2i EngineConfigs::s_resolution = Vector2i(640, 480);
bool EngineConfigs::s_fullscreen = false;
String EngineConfigs::s_projectName = "giTestProject";
GIENGINE_API::E EngineConfigs::s_activeGraphicApi = GIENGINE_API::kDX11;
Path EngineConfigs::s_projectPath = ("G:/Dev/giTestProject/");

//Plugins
Map<GIPLUGINS::E, bool> EngineConfigs::s_activePlugins;

//Omniverse settings
//String EngineConfigs::s_existingStage = "omniverse://localhost/Users/giProjects/scene.usd";
String EngineConfigs::s_existingStage = "";
String EngineConfigs::s_destinationPath = "omniverse://localhost/Users/giProjects/";





EngineConfigs&
g_engineConfigs() {
  return EngineConfigs::instance();
}