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
Vector2 EngineConfigs::s_resolution = Vector2(650, 480);
bool EngineConfigs::s_fullscreen = false;
String EngineConfigs::s_projectName = "giTestProject";
GIENGINE_API::E EngineConfigs::s_activeGraphicApi = GIENGINE_API::kDX11;
Path EngineConfigs::s_projectPath = ("G:/Dev/giEngineTestProject/");

//Plugins
Map<int32, GIPLUGINS::E> EngineConfigs::s_activePlugins;

//Omniverse settings
String EngineConfigs::s_existingStage = "";





EngineConfigs&
g_engineConfigs() {
  return EngineConfigs::instance();
}