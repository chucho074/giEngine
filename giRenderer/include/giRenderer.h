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
#include <giCamera.h>
#include "giPrerequisitesRenderer.h"

namespace giEngineSDK {
  class Model;
  class BaseVertexShader;
  class BasePixelShader;
}


namespace giEngineSDK {
  /**
   * @struct   CameraConstantBuffer.
   * @brief    The Camera constant buffer.
   * @bug      No known Bugs.
   */
  struct CameraConstantBuffer {
    Matrix4 mView;
    Matrix4 mProjection;
  };

  /**
   * @struct   CBChangesEveryFrame.
   * @brief    The Changes Every Frames Constant Buffer.
   * @bug      No known Bugs.
   */
  struct CBChangesEveryFrame {
    Matrix4 mWorld;
    Vector4 vMeshColor;
  };


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
   * @struct   LightConstantBuffer.
   * @brief    The Camera constant buffer.
   * @bug      No known Bugs.
   */
  struct LightConstantBuffer {
    Vector3 LightPos;
    float LightIntensity;
  };

  /**
   * @struct   BlurConstantBuffer.
   * @brief    The Camera constant buffer.
   * @bug      No known Bugs.
   */
  struct BlurConstantBuffer {
    Vector2 Viewport;   
    float Gamma = 1.0f;
    float Garbage = 0;   //Just for the 16 magic
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

    //The main camera 
    Camera m_mainCamera;

    //The Constant Buffer (Never Change)
    Buffer * m_cBufferCamera = nullptr;


    //The Constant Buffer (Change Every Frame)
    Buffer * m_cBufferChangeEveryFrame = nullptr;


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
    //The Vertex Shader
    BaseVertexShader* m_vertexShaderBlur = nullptr;
    //The Pixel Shader
    BasePixelShader* m_pixelShaderBlurH = nullptr;

    //The Pixel Shader
    BasePixelShader* m_pixelShaderBlurV = nullptr;

    Vector<Texture2D*> m_BlurTexture;

    Buffer* m_cBufferBlur = nullptr;


    //Light
    //The Vertex Shader
    BaseVertexShader* m_vertexShaderLight = nullptr;
    //The Pixel Shader
    BasePixelShader* m_pixelShaderLight = nullptr;
    //The input Layout
    InputLayout* m_inputLayoutLight = nullptr;
    //The Constant Buffer
    Buffer* m_cBufferLight = nullptr;
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