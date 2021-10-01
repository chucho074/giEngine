/**
 * @file    giCamera.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/04/2021
 * @brief   A basic camera.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giVector4.h>
#include <giMatrix4.h>
#include "giPrerequisitesCore.h"
#include "giComponent.h"

namespace giEngineSDK {
  /**
   * @class   Camera. 
   * @brief   A basic uses for the camera.
   */
  class GI_CORE_EXPORT Camera : Component
  {
   public:
    ///Default Constructor
    Camera();

    ///Destructor
    ~Camera() = default;

    /**
     * @brief   Initialize the information of the camera.
     * @param   inAngle  The aperture angle for the camera.
     * @param   inAR     The aspect Ratio for the camera.
     * @param   inNear   The near distance to render in the camera.
     * @param   inFar    The far distance to render in the camera.
     */
    void 
    init(float inAngle, float inAR, float inNear, float inFar);

    /**
     * @brief   Update the buffers.
     */
    void
    update(float inDT) override;

    /**
     * @brief   Update the Camera information.
     */
    void 
    updateData();

    /**
     * @brief   Update the View Matrix information.
     */
    void
    updateVM();

    /**
     * @brief   Apply a movement in the camera position.
     * @param   inVect   The direction to move the camera.
     */
    void 
    move(Vector4 inVect);
    
    /**
     * @brief   Apply a new camera position.
     * @param   inVect   The position to set the camera.
     */
    void 
    setPosition(Vector4 inVect1, Vector4 inVect2, Vector4 inVect3);

    /**
     * @brief   Update and get the View Matrix.
     * @return  Returns the view matrix.
     */
    Matrix4 
    getViewMatrix();

    /**
     * @brief   Update and get the proyection Matrix.
     * @return  Returns the proyection Matrix
     */
    Matrix4 
    getProyectionMatrix();

   //private:
    float m_angle = 0;
    float m_aspectRatio = 0;
    float m_near = 0;
    float m_far = 0;
    //Vector4 m_eye = { 0.0f, -8.0f, -6.0f, 1.0f };  //En posicion del mundo
    //Vector4 m_at = { 0.0f, 0.0f, 0.0f, 1.0f };  //En posicion del mundo
    //Vector4 m_up = { 0.0f, 1.0f, 0.0f, 1.0f };  //Up del mundo
    Vector4 m_eye = { 100.0f,  -50.0f, -180.0f, 1.0f };  // En posicion del mundo
    //Vector4 m_at  = { -0.9f,  0.2f,  0.0f, 1.0f };  // En posicion del mundo
    Vector4 m_at  = { -0.9f,  0.2f,  0.0f, 1.0f };  // En posicion del mundo
    Vector4 m_up  = { 0.0f,  1.0f,  0.0f, 1.0f };  // Up del mundo
    Matrix4 m_viewMatrix;
    Matrix4 m_projMatrix;
    Vector4 m_right;
    Vector4 m_up2;    //Up de la camara
    Vector4 m_front;

  };
}