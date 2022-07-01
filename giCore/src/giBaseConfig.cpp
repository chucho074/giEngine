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


//Basic App Configs
Vector2i EngineConfigs::s_resolution = Vector2i(1280, 720);
bool EngineConfigs::s_fullscreen = false;
bool EngineConfigs::s_maximized = true;
String EngineConfigs::s_projectName = "giTestProject";
GIENGINE_API::E EngineConfigs::s_activeGraphicApi = GIENGINE_API::kDX11;
Path EngineConfigs::s_projectPath = ("E:/Dev/giTestProject");

//Plugins
Map<GIPLUGINS::E, bool> EngineConfigs::s_activePlugins;

//Omniverse settings
//String EngineConfigs::s_existingStage = "omniverse://localhost/Users/giProjects/giTestProject/scene.usd";
//String EngineConfigs::s_existingStage = "http://localhost:8080/omniverse://127.0.0.1/Users/giProjects/giTestProject/sceneSphere.usd";
//String EngineConfigs::s_existingStage = "http://localhost:8080/omniverse://127.0.0.1/Users/chucho074/ovEngine1.usd";
//String EngineConfigs::s_existingStage = "C:/Users/HEADQUARTERV2/Downloads/scene.usd";
String EngineConfigs::s_existingStage = "";
String EngineConfigs::s_destinationPath = "omniverse://localhost/Users/giProjects/";

//Editor Settings



EngineConfigs&
g_engineConfigs() {
  return EngineConfigs::instance();
}
