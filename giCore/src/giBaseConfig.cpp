/**
 * @file    giBaseConfig.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giBaseConfig.h"


//Basic App Configs
Vector2i EngineConfigs::s_resolution = Vector2i(1280, 720);
bool EngineConfigs::s_fullscreen = false;
bool EngineConfigs::s_maximized = true;
String EngineConfigs::s_projectName = "";
GIENGINE_API::E EngineConfigs::s_activeGraphicApi = GIENGINE_API::kDX11;
Path EngineConfigs::s_projectPath = ("G:/Dev/giTestProject");
Path EngineConfigs::s_contentPath = ("G:/Dev/giTestProject/content");
//Path EngineConfigs::s_projectPath = ("");
//Path EngineConfigs::s_contentPath = ("");
Path EngineConfigs::s_generatedPath = ("Resources/Models/Generated/");
Path EngineConfigs::s_binPath = fsys::current_path();

//Plugins
Map<GIPLUGINS::E, bool> EngineConfigs::s_activePlugins;


//giAMR
//Path EngineConfigs::s_generatedPath = "G:/Dev/giEngine/bin/Resources/Models/Generated/";
Path EngineConfigs::s_anacondaPath = "%USERPROFILE%/anaconda3/Scripts";
Path EngineConfigs::s_nvdiffPath = "G:/Dev/nvdiffmodeling";
String EngineConfigs::s_enviromentName = "dmodel";

//Omniverse Settings
String EngineConfigs::s_existingStage = "";
String EngineConfigs::s_destinationPath = "omniverse://localhost/Users/giProjects/";

bool EngineConfigs::s_decoratedWindow = true;

//Editor Settings

//Renderer Settings



EngineConfigs&
g_engineConfigs() {
  return EngineConfigs::instance();
}
