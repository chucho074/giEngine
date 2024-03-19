/**
 * @file    giBaseAMR.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/02/2023
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giModule.h"
#include "giModel.h"
#include "giVector2i.h"
#include "giBaseConfig.h"
#include "giResourceManager.h"
#include "giTexture.h"

namespace giEngineSDK {


  struct DescAMR {
    int32 m_saveInterval = 512;

    bool m_randomTextures = false;

    Vector2i m_textureSize = { 2048, 2048 };

    int32 m_trainResolution = 512;

    int32 m_batch = 8;

    float m_learningRate = 0.01f;

    Vector<String> m_skipTrain;

    int32 m_iterations = 5000;

    Path m_outputDir;

    Path m_refMesh;

    Path m_baseMesh = "G:/Dev/giEngine/bin/Resources/Models/Generated/sphere.obj";
  };

  class BaseAMR : public Module<BaseAMR>
  {
   public:
  	BaseAMR() = default;
  	~BaseAMR() = default;
   
    virtual void
    setRefMesh(Path inData) {};

    virtual void
    run() {};
  	
    virtual void
    reset() {};

    bool m_renderWindow = false;

    bool m_processWindow = false;

    int32 m_processImg = 0;

    int32 m_showingImg = 1;

    DescAMR m_savedData;

    ModelInfo m_refInfo;
    
    ModelInfo m_outInfo;

    uint32 minimunTriang = 512;
    uint32 halfTriang = 512;
    uint32 partialTriang = 512;

    int32 finalTriang = 0;

    //giAMR process image
    Vector<ResourceRef> m_AMRprocess;

  };

  GI_CORE_EXPORT BaseAMR& 
  g_AMR();


  //For load the DLL
  using funCreateAMR = BaseAMR * (*)();
};