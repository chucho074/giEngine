/**
 * @file    giStaticMesh.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    17/08/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giModel.h"
#include "giComponent.h"

namespace giEngineSDK {
  class GI_CORE_EXPORT StaticMesh : public Component
  {
   public:
    StaticMesh() = default;

    //Default Constructor
    StaticMesh(ResourceRef inRes) : m_model(inRes) {};

    //Desturctor
    ~StaticMesh();

    void
    setNewModel(ResourceRef inRes) {
      m_model = inRes;
    }

    void 
    update(float inDeltaTime) override;

    void 
    render() override;

    void 
    destroy() override;

    ResourceRef
    getModel();

   private:

    ResourceRef m_model;
  };
}