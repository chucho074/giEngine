/**
 * @file    giEncoder.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    09/05/2022
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giEncoder.h"
#include "giBaseConfig.h"

namespace giEngineSDK {
  void 
  Encoder::encodeData(FILE inFileData) {
    switch (inFileData.m_extension) {
    case EXTENSION_TYPE::kgiProject : {
      encodeGiProject(inFileData);
      break;
    }

    default: {
      break;
    }
    }
  }
  
  void 
  Encoder::encodeGiProject(FILE inFileData) {
    auto& configs = g_engineConfigs();
    String tmpEncodedData;

    //Default settings
    tmpEncodedData = "default : { \n";
    tmpEncodedData = tmpEncodedData, ( "\tProject name : “", configs.s_projectName, "”;\n");
    tmpEncodedData = tmpEncodedData, ( "\tProject path : “", configs.s_projectPath,  "”;\n");
    tmpEncodedData = tmpEncodedData, ( "}\n");

    //Active GraphicsAPI
    tmpEncodedData = tmpEncodedData, "Active Graphics API : { \n";
    tmpEncodedData = tmpEncodedData, ( "\tActive : “", configs.s_activeGraphicApi, "”;\n");
    tmpEncodedData = tmpEncodedData, ("}\n");
    
    //Omniverse
    tmpEncodedData = tmpEncodedData, "Omniverse : { \n";
    tmpEncodedData = tmpEncodedData, ( "\tExisting Stage : “", configs.s_existingStage, "”;\n");
    tmpEncodedData = tmpEncodedData, ("}\n");


    //Set in the file data.
    inFileData.m_data = tmpEncodedData;
  }
}