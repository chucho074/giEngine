/**
 * @file    giStaticMesh.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    17/08/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
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
    //Default Constructor
    StaticMesh() = default;

    //Desturctor
    ~StaticMesh() = default;

    void 
    update(float inDeltaTime) override;

    void 
    render() override;

    void
    setModel(SharedPtr<Model> inModel);


   private:

    SharedPtr<Model> m_model;
  };
}