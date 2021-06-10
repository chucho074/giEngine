/**
 * @file    giCuaternion.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    04/06/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesUtilities.h"


namespace giEngineSDK {
  class Vector3;


  /**
   * @class    Quaternion.
   * @brief    .
   * @bug      No known Bugs.
   */
  class GI_UTILITY_EXPORT Quaternion
  {
   public:
    //Default Constructor.
    Quaternion() = default;

    //Constructor from vector3 
    Quaternion(const Vector3& inVector, const float inScalar);
    
    //Constructor from 4 floats
    Quaternion(const float inX, 
    /*********/const float inY, 
    /*********/const float inZ, 
    /*********/const float inW) : m_X(inX), 
    /****************************/m_Y(inY), 
    /****************************/m_Z(inZ), 
    /****************************/m_W(inW) { };

    //Destructor.
    ~Quaternion() = default;

    Quaternion
    operator+(const Quaternion& inOterQuat);
    
    Quaternion
    operator-(const Quaternion& inOterQuat);

    Quaternion
    operator*(const Quaternion& inOterQuat);
    
    Quaternion
    operator*(const float inScalar);

    Quaternion
    normalize();

   float m_X;   

   float m_Y;   

   float m_Z;   

   float m_W;  
  };



}