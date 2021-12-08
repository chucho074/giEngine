/**
 * @file    giParticleSystem.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    08/12/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giVector2.h>
#include <giVector3.h>
#include "giPrerequisitesCore.h"

namespace giEngineSDK {
  struct Particle {
    bool    m_isLiving = false;
    float   m_lifeTime = 0.0f;
    float   m_maxLifeTime = 0.0f;
    Vector3 m_position;
  };


  namespace EMISSION_SHAPE {
    enum E {

    };
  };


  class ParticleSystem {
    ParticleSystem() = default;
    ~ParticleSystem() = default;

    virtual void 
    init() {}

    virtual void 
    update(float& inDeltaTime) {}
    
    virtual void 
    destroy() {}


    bool m_isLooping = false;
    float m_lifeTime = 0.0f;
    Vector2 m_particlesPerSecond;
    Vector2 m_rangeLifeTime;
    Vector3 m_position;
    Vector<Particle> m_particles;
  };
}