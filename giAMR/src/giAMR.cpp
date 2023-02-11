/**
 * @file    giAMR.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/02/2023
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#include "giAMR.h"
#include <iostream>

namespace giEngineSDK {
  void
  AMR::setRefMesh(Path inData) {
    m_savedData.m_refMesh = inData;
    String tmpPath = g_engineConfigs().s_contentPath.string() 
                      + "/giAMR/"+ inData.filename().string();
    m_savedData.m_outputDir = tmpPath;
    m_renderWindow = true;
  }

  void
  AMR::run() {
    //Add a way to verify if there's info to use
    createJSON();
    system("cmd /c start giAMR.bat");
  }

  void 
  AMR::reset() {
    m_processImg = 0;
  }


  void 
  AMR::createJSON() {
    json tmpFile;
    
    tmpFile["base_mesh"] = m_savedData.m_baseMesh.c_str();
    
    tmpFile["ref_mesh"] = m_savedData.m_refMesh.c_str();

    tmpFile["camera_eye"] = {2.5, 0.0, 2.5};
    
    tmpFile["camera_up"] = {0.0, 1.0, 0.0};
    
    tmpFile["save_interval"] = m_savedData.m_saveInterval;
    
    tmpFile["random_textures"] = m_savedData.m_randomTextures;
    
    tmpFile["train_res"] = m_savedData.m_trainResolution;
    
    tmpFile["barch"] = m_savedData.m_batch;
    
    tmpFile["learning_rate"] = m_savedData.m_learningRate;
    
    tmpFile["skip_train"] = {"kd","ks"};
    
    tmpFile["iter"] = m_savedData.m_iterations;
    
    tmpFile["out_dir"] = m_savedData.m_outputDir.c_str();

    ofstream o("Resources/giAMR/giAMR.json");
    o << std::setw(4) << tmpFile << std::endl;
  }


};