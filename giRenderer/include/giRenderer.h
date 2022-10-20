/**
 * @file    giRenderer.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    18/08/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include <giBaseRenderer.h>
#include <giResourceManager.h>
#include <giCamera.h>
#include <giVector2i.h>
#include <giVector3i.h>
#include "giPrerequisitesRenderer.h"

namespace giEngineSDK {
  class Model;
  class BaseVertexShader;
  class BasePixelShader;
  class DepthStateDX;
  class RasterizerDX;
}


namespace giEngineSDK {
  /**
   * @struct   CameraConstantBuffer.
   * @brief    The Camera constant buffer.   
   */
  struct CameraConstantBuffer {
    Matrix4 mView;
    Matrix4 mProjection;
  };

  /**
   * @struct   CBChangesEveryFrame.
   * @brief    The Changes Every Frames Constant Buffer.   
   */
  struct CBChangesEveryFrame {
    Matrix4 mWorld;
    //Vector4 vMeshColor;
  };


  /**
   * @struct   SSAOConstantBuffer.
   * @brief    The Camera constant buffer.   
   */
  struct SSAOConstantBuffer {
    float SampleRadius;
    float Intensity;
    float Scale;
    float Bias;
    Vector2 TextureSize;
    Vector2 empty;
  };

  /**
   * @struct   LightConstantBuffer.
   * @brief    The Camera constant buffer.   
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
     * brief     .
     */
    void
    renderData(Vector<SharedPtr<Texture2D>> inRendertarget,
               SharedPtr<Texture2D> inDS,
               SharedPtr<InputLayout> inInputLayout,
               SharedPtr<BaseVertexShader> inVertexShader,
               SharedPtr<BasePixelShader> inPixelShader,
               SharedPtr<SamplerState> inSampler,
               Vector<SharedPtr<Buffer>> inConstantBuffers,
               Vector<SharedPtr<Texture2D>> inShaderResources = Vector<SharedPtr<Texture2D>>(),
               bool inDrawSAQ = false, 
               bool inClear = true);

    /**
     * @brief    .
     */
    void 
    dispatchData(Vector<SharedPtr<Buffer>> inConstantBuffers,
                 SharedPtr<BaseComputeShader> inCS,
                 Vector<SharedPtr<Texture2D>> inShaderResources,
                 Vector<SharedPtr<Texture2D>> inUAVS,
                 SharedPtr<SamplerState> inSampler,
                 Vector3i inDispatch);
    /**
     * @brief    .
     */
    void
    setModels(Vector<SharedPtr<Model>> inModelList) override;


    void
    updateTextureSizes(Vector2i inSize);

    void 
    setTransform(Matrix4 inTransformation) override;

    //The main camera 
    SharedPtr<Camera> m_mainCamera;

    //The Constant Buffer (Never Change)
    SharedPtr<Buffer> m_cBufferCamera;

    //The Constant Buffer (Change Every Frame)
    SharedPtr<Buffer> m_cBufferChangeEveryFrame;

    //The input Layout
    SharedPtr<InputLayout> m_inputLayout;

    //The SamplerState
    SharedPtr<SamplerState> m_sampler;

    //The color For the mesh
    Vector4 m_meshColor{ 0.f, 0.f, 0.f, 1.f };
    //Depth Stencil State
    SharedPtr<DepthStateDX> m_depthStateGBuffer;

    //Rasterizer
    SharedPtr<RasterizerDX> m_rasterGBuffer;

    Vector<SharedPtr<Texture2D>> m_renderTargets;

                //GBUFFER
    //The Vertex shader
    SharedPtr<BaseVertexShader> m_vertexShader;

    //The Pixel Shader
    SharedPtr<BasePixelShader> m_pixelShader;

                //SSAO
    //The Vertex shader
    SharedPtr<BaseVertexShader> m_vertexShaderSSAO;

    //The Pixel Shader
    SharedPtr<BasePixelShader> m_pixelShaderSSAO;


    SharedPtr<InputLayout> m_inputLayoutSSAO;

    SharedPtr<Buffer> m_cBufferSSAO;
    
    Vector<SharedPtr<Texture2D>> m_SSAOTexture;

    

                //Blur
    //The Vertex Shader
    SharedPtr<BaseVertexShader> m_vertexShaderBlur;
    //The Pixel Shader
    SharedPtr<BasePixelShader> m_pixelShaderBlurH;

    //The Pixel Shader
    SharedPtr<BasePixelShader> m_pixelShaderBlurV;

    Vector<SharedPtr<Texture2D>> m_BlurTexture;

    SharedPtr<Buffer> m_cBufferBlur;

                //Shadows
    //The Vertex Shader
    SharedPtr<BaseVertexShader> m_vertexShaderShadow;
    //The Pixel Shader
    SharedPtr<BasePixelShader> m_pixelShaderShadow;
    //The texture
    Vector<SharedPtr<Texture2D>> m_ShadowTexture;
    //The buffer
    SharedPtr<Buffer> m_cBufferShadow;
    //Camera
    SharedPtr<Camera> m_ShadowCamera;

               //Light
    //The Vertex Shader
    SharedPtr<BaseVertexShader> m_vertexShaderLight;
    //The Pixel Shader
    SharedPtr<BasePixelShader> m_pixelShaderLight;
    //The input Layout
    SharedPtr<InputLayout> m_inputLayoutLight;
    //The Constant Buffer
    SharedPtr<Buffer> m_cBufferLight;



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