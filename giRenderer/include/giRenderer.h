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
    //Vector4 vMeshColor;
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
    Vector2 TextureSize;
    Vector2 kk;
  };
  /**
   * @struct   LightConstantBuffer.
   * @brief    The Camera constant buffer.
   * @bug      No known Bugs.
   */
  struct LightConstantBuffer {
    Vector3 LightPos;
    float LightIntensity;
    Vector4 ViewPos;
    Matrix4 InverseView;
  };

  /**
   * @struct   BlurConstantBuffer.
   * @brief    The Camera constant buffer.
   * @bug      No known Bugs.
   */
  struct BlurConstantBuffer {
    Vector2 Viewport;   
    float Gamma = 1.0f;
    Vector2 TextureSize;   
    Vector3 Garbage;   //Just for the 16 magic
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
    update() override;

    /**
     * @brief    .
     */
    void
    render() override;

    /**
     * brief
     */
    void
    renderData(Vector<Texture2D*> inRendertarget,
               Texture2D* inDS,
               InputLayout* inInputLayout,
               BaseVertexShader* inVertexShader,
               BasePixelShader* inPixelShader,
               Sampler* inSampler,
               Vector<Buffer*> inConstantBuffers,
               Vector<Texture2D*> inShaderResources = Vector<Texture2D*>(),
               bool inDrawSAQ = false, 
               bool inClear = true);

    /**
     * @brief
     */
    void 
    dispatchData(Vector<Buffer*> inConstantBuffers,
                 BaseComputeShader * inCS,
                 Vector<Texture2D*> inShaderResources,
                 Vector<Texture2D*> inUAVS,
                 Sampler* inSampler,
                 Vector3 inDispatch);
    /**
     * @brief    .
     */
    void
    setModels(Vector<SharedPtr<Model>> inModelList) override;

    //The main camera 
    SharedPtr<Camera> m_mainCamera;
    //The Constant Buffer (Never Change)
    Buffer * m_cBufferCamera = nullptr;
    //The Constant Buffer (Change Every Frame)
    Buffer * m_cBufferChangeEveryFrame = nullptr;
    //The input Layout
    InputLayout* m_inputLayout = nullptr;
    //The Sampler
    Sampler* m_sampler = nullptr;
    //The color For the mesh
    Vector4 m_meshColor{ 0.f, 0.f, 0.f, 1.f };
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
    //The Compute Shader
    BaseComputeShader* m_computeShaderSSAO = nullptr;
    Buffer* m_cBufferSSAO = nullptr;
    Vector<Texture2D*> m_SSAOTexture;

    //SAQ
    SharedPtr<Model> m_SAQ;

                  //Blur
    //The Compute Shader
    BaseComputeShader* m_csBlurH = nullptr;
    //The Compute Shader
    BaseComputeShader* m_csBlurV = nullptr;
    Vector<Texture2D*> m_BlurTexture;
    Buffer* m_cBufferBlur = nullptr;

                //Shadows
    //The Vertex Shader
    BaseVertexShader* m_vertexShaderShadow = nullptr;
    //The Pixel Shader
    BasePixelShader* m_pixelShaderShadow = nullptr;
    //The texture
    Vector<Texture2D*> m_ShadowTexture;
    //The buffer
    Buffer* m_cBufferShadow = nullptr;
    //Camera
    SharedPtr<Camera> m_ShadowCamera;

               //Light
    //The Vertex Shader
    BaseVertexShader* m_vertexShaderLight = nullptr;
    //The Pixel Shader
    BasePixelShader* m_pixelShaderLight = nullptr;
    //The input Layout
    InputLayout* m_inputLayoutLight = nullptr;
    //The Constant Buffer
    Buffer* m_cBufferLight = nullptr;


    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
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