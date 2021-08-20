/**
 * @file    giRenderer.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giBaseRenderer.h>
#include "giPrerequisitesRenderer.h"

namespace giEngineSDK {
  class Model;
  class BaseVertexShader;
  class BasePixelShader;
}


namespace giEngineSDK {

  /**
   * @struct   SSAOConstantBuffer.
   * @brief    The Camera constant buffer.
   * @bug      No known Bugs.
   */
  struct SSAOConstantBuffer {
    float SampleRadius;
    float Intensity;
    float Scale;
    float Bias;
  };

  /**
   * @struct   BlurConstantBuffer.
   * @brief    The Camera constant buffer.
   * @bug      No known Bugs.
   */
  struct BlurConstantBuffer {
    float Viewport[2] = { 1280 , 720 };   //TODO
    float Gamma = 1.0f;
  };


  class Renderer : public BaseRenderer
  {
   public:
    //Default Constructor
  	Renderer() = default;

    //Destructor
  	~Renderer() = default;

    /**
     * @brief    .
     */
    void
    create() override;
    
    /**
     * @brief    .
     */
    void
    render() override;

    /**
     * @brief    .
     */
    void
    setModels(Vector<SharedPtr<Model>> inModelList) override;

    //The input Layout
    InputLayout* m_inputLayout = nullptr;

    //The Sampler
    Sampler* m_sampler = nullptr;

    //The Vertex Buffer
    //Buffer * m_vertexBuffer = nullptr;

    //The Index Buffer 
    //Buffer * m_indexBuffer = nullptr;

    //The color For the mesh
    Vector4 m_meshColor{ 0.f, 0.f, 0.f, 0.f };

    //Depth Stencil State
    SharedPtr<DepthState> m_depthStateGBuffer;

    //Rasterizer
    SharedPtr<Rasterizer> m_rasterGBuffer;

    Vector<Texture2D*> m_renderTargets;

    //GBUFFER
    //The Vertex shader
    BaseVertexShader* m_vertexShader = nullptr;

    //The Pixel Shader
    BasePixelShader* m_pixelShader = nullptr;

    //SSAO
    //The Vertex shader
    BaseVertexShader* m_vertexShaderSSAO = nullptr;

    //The Pixel Shader
    BasePixelShader* m_pixelShaderSSAO = nullptr;


    InputLayout* m_inputLayoutSSAO = nullptr;

    Buffer* m_cBufferSSAO = nullptr;
    
    Vector<Texture2D*> m_SSAOTexture;

    //SAQ
    SharedPtr<Model> m_SAQ;

    //Blur

    //The Pixel Shader
    BasePixelShader* m_pixelShaderBlurH = nullptr;

    //The Pixel Shader
    BasePixelShader* m_pixelShaderBlurV = nullptr;

    InputLayout* m_inputLayoutBlur = nullptr;

    Vector<Texture2D*> m_BlurTexture;

    Buffer* m_cBufferBlur = nullptr;
  };

  /**
   * @brief   Create the gAPI with a dll.
   */
  extern "C" GI_PLUGIN_EXPORT Renderer *
    createRenderer() {
    auto renderer = new Renderer();
    return renderer;
  }

}