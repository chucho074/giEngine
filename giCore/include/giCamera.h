/**
 * @file    giCamera.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/04/2021
 * @brief   A basic camera.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include "giPrerequisitesCore.h"
#include <giVector4.h>
#include <giMatrix4.h>

namespace giEngineSDK {
  /**
   * @class   Camera. 
   * @brief   A basic uses for the camera.
   */
  class GI_CORE_EXPORT Camera
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
     * @brief   Update the Camera information.
     */
    void 
    update();

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
    Vector4 m_eye = { 0.0f, 3.0f, -6.0f, 1.0f };  //En posicion del mundo
    Vector4 m_at = { 0.0f, 1.0f, 0.0f, 1.0f };  //En posicion del mundo
    Vector4 m_up = { 0.0f, 1.0f, 0.0f, 0.0f };  //Up del mundo
    Matrix4 m_viewMatrix;
    Matrix4 m_projMatrix;
    Vector4 m_right;
    Vector4 m_up2;    //Up de la camara
    Vector4 m_front;

  };
}