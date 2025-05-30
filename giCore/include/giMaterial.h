/**
 * @file    giMaterial.h
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    15/08/2021
 * @brief   A basic description of the what do the doc.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include "giResourceManager.h"
#include "giResource.h"
#include "giTexture2D.h"
#include "giTexture.h"  
#include "giSampler.h"
#include "giVector3.h"

namespace giEngineSDK {
  

  /**
   * @struct   MaterialConstantBuffer.
   * @brief    For the information of the materials.
   */
  struct MaterialConstantBuffer {
    Vector3 AlbedoColor = Vector3::ZERO;
    Vector3 EmissiveColor = Vector3::ZERO;
    float metalic = 0.f;
    float roughness = 0.f;
    float ambientOclussion = 0.f;
    float opacity = 0.f;
    float gloss = 0.f;
    float specular = 0.f;
  };


  namespace MATERIAL_FLAGS {
    enum E {
      kTWO_SIDES
    };
  }

  /**
   * @class   Material.
   */
  class Material : public Resource
  {
   public:
    //Default Constructor
    Material() = default;

    //Destructor
    ~Material() = default;
    
    inline void
    setTwoSide(bool inStatus) {
      m_twoSide = inStatus;
    }

    inline bool
    getTwoSide() {
      return m_twoSide;
    }

    inline void
    setName(StringView inName) {
      m_name = inName;
    }

    inline StringView
    getName() const {
      return m_name;
    }

    /**
     * @brief    Gets the texture reference from a type.
     * @param    inType        The type of the texture.
     * @return   The reference of the texture.
     */
    inline ResourceRef
    getTextureRefByType(TEXTURE_TYPE::E inType) {
      return m_textureMaps.find(inType)->second;
    }

    /**
     * @brief    Binds a texture to the material.
     * @param    inType        The type of the texture.
     * @param    inRef         The reference of the texture to bind.
     */
    inline void
    bindTexture(TEXTURE_TYPE::E inType, ResourceRef inRef) {
      m_textureMaps.insert({inType, inRef});
    }

    /**
     * @brief    Unbinds the texture from the material.
     * @param    inType        The type of the texture to unbind.
     */
    inline void
    unbindTextureByType(TEXTURE_TYPE::E inType) {
      m_textureMaps.erase(m_textureMaps.find(inType));
    }

    /**
     * @brief    Give the material a name.
     * @param    inName        The name of the material.
     */
    inline void
    setName(String inName) {
      m_name = inName;
    }

    /**
     * @brief    Sets the albedo color of the material.
     * @param    inColor       The color to set to the albedo.
     */
    inline void
    setAlbedoColor(Vector3 inColor) {
      m_albedoColor = inColor;
    }
    
    /**
     * @brief    Sets the emissive color of the material.
     * @param    inColor       The color to set to the emissive.
     */
    inline void
    setEmissiveColor(Vector3 inColor) {
      m_emissiveColor = inColor;
    }

    /**
     * @brief    Sets the metallic value of the material.
     * @param    inMetallic    The value to set to the metallic.
     */
    inline void
    setMetallicValue(float inMetallic) {
      m_metalic = inMetallic;
    }

    /**
     * @brief    Sets the roughness value of the material.
     * @param    inRoughness   The value to set to the roughness.
     */
    inline void
    setRoughnessValue(float inRoughness) {
      m_roughness = inRoughness;
    }

    /**
     * @brief    Sets the ambient oclussion value of the material.
     * @param    inAmbientOclussion   The value to set to the ambient oclussion.
     */
    inline void
    setAmbientOclussionValue(float inAmbientOclussion) {                       // ????????????
      m_ambientOclussion = inAmbientOclussion;
    }

    /**
     * @brief    Sets the opacity value of the material.
     * @param    inOpacity     The value to set to the opacity.
     */
    inline void
    setOpacityValue(float inOpacity) {
      m_opacity = inOpacity;
    }

    /**
     * @brief    Sets the gloss value of the material.
     * @param    inGloss       The value to set to the gloss.
     */
    inline void
    setGlossValue(float inGloss) {
      m_gloss = inGloss;
    }

    /**
     * @brief    Sets the specular value of the material.
     * @param    inSpecular    The value to set to the specular.
     */
    inline void
    setSpecularValue(float inSpecular) {
      m_specular = inSpecular;
    }

    /**
     * @brief    Gets the albedo color of the material.
     * @return   The albedo color of the material.
     */
    inline Vector3
    getAlbedoColor() const {
      return m_albedoColor;
    }

    /**
     * @brief    Gets the emissive color of the material.
     * @return   The emissive color of the material.
     */
    inline Vector3
    getEmissiveColor() const {
      return m_emissiveColor;
    }

    /**
     * @brief    Gets the metallic value of the material.
     * @return   The metallic value of the material.
     */
    inline float
    getMetallicValue() const {
      return m_metalic;
    }

    /**
     * @brief    Gets the roughness value of the material.
     * @return   The roughness value of the material.
     */
    inline float
    getRoughnessValue() const {
      return m_roughness;
    }

    /**
     * @brief    Gets the ambient oclussion value of the material.
     * @return   The ambient oclussion value of the material.
     */
    inline float
    getAmbientOclussionValue() const {
      return m_ambientOclussion;
    }

    /**
     * @brief    Gets the opacity value of the material.
     * @return   The opacity value of the material.
     */
    inline float
    getOpacityValue() const {
      return m_opacity;
    }
    
    /**
     * @brief    Gets the gloss value of the material.
     * @return   The gloss value of the material.
     */
    inline float
    getGlossValue() const {
      return m_gloss;
    }

    /**
     * @brief    Gets the specular value of the material.
     * @return   The specular value of the material.
     */
    inline float
    getSpecularValue() const {
      return m_specular;
    }

    void
    render();

   protected:
  	
    String m_name;

    Vector3 m_albedoColor = Vector3::ZERO;
    Vector3 m_emissiveColor = Vector3::ZERO;
    float m_metalic = 0.f;
    float m_roughness = 0.f;
    float m_ambientOclussion = 0.f;
    float m_opacity = 0.f;
    float m_gloss = 0.f;
    float m_specular = 0.f;

    Map<TEXTURE_TYPE::E, ResourceRef> m_textureMaps;

    bool m_twoSide = false;

  };

  class baseMaterial : public Material {
   public:
    baseMaterial() {
      m_albedoColor      = {1, 1, 1};
      m_emissiveColor    = {0, 0, 0};
      m_metalic          = 0.5;
      m_roughness        = 0.5;
      m_ambientOclussion = 0.5;
      m_opacity          = 0.5;
      m_gloss            = 0.5;
      m_specular         = 0.5;
    }
  };

}