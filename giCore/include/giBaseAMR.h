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

    float m_learningRate = 0.01;

    Vector<String> m_skipTrain;

    int32 m_iterations = 5000;

    Path m_outputDir;

    Path m_refMesh;

    Path m_baseMesh = "G:/Dev/giEngine/bin/Resources/giAMR/sphere.obj";
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

    DescAMR m_savedData;


    //giAMR process image
    ResourceRef m_AMRprocess;

  };

  GI_CORE_EXPORT BaseAMR& 
  g_AMR();


  //For load the DLL
  using funCreateAMR = BaseAMR * (*)();
};