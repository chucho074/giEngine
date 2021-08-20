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

    //The Vertex shader
    BaseVertexShader* m_vertexShader = nullptr;

    //The Pixel Shader
    BasePixelShader* m_pixelShader = nullptr;
    
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