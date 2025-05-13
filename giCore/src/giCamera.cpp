/**
 * @file    giCamera.cpp
 * @author  Jesus Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/04/2021
 * @brief   A basic camera.
 */
 
/**
 * @include
 */
#include "giCamera.h"
#include "giRadians.h"

namespace giEngineSDK {
  Camera::Camera() {
    m_forward = (m_at - m_eye);
    m_forward.normalize();

    m_rightVector = m_upVect.cross(m_forward);
    m_rightVector.normalize();
    
    m_up2 = m_forward.cross(m_rightVector);
    //m_up2.normalize();

    m_front = false;
    m_back = false;
    m_left = false;
    m_right = false;
    m_up = false;
    m_down = false;

  }
  
  void 
  Camera::init(float inAngle, float inAR, float inNear, float inFar) {
    m_angle = inAngle;
    m_aspectRatio = inAR;
    m_near = inNear;
    m_far = inFar;
    updateRotations();
  }
  
  void 
  Camera::update(float inDT) {
    move(inDT);
  }

  
  void 
  Camera::move(float inDT) {
    
    float velocity = m_speed * inDT;
    if(m_front)
      m_eye += m_forward * velocity;
    if(m_back)
      m_eye -= m_forward * velocity;
    if(m_left)
      m_eye -= m_rightVector * velocity;
    if(m_right)
      m_eye += m_rightVector * velocity;
    if(m_up)
      m_eye -= m_upVect * velocity;
    if(m_down)
      m_eye += m_upVect * velocity;
    if(m_YawNeg) {
      m_YPR.x -= 1 * inDT;
      if(Radians(m_YPR.x) < Radians(0.f)) {
        m_YPR.x = Degrees(360.f).getRadians();
      }
      updateRotations();
    }
    if(m_YawPos) {
      m_YPR.x += 1 * inDT;
      if(Radians(m_YPR.x) > Degrees(360.f).getRadians()) {
        m_YPR.x = 0.f;
      }
      updateRotations();
    }
  }

  void 
  Camera::setPosition(Vector4 inVect, Vector4 inVect2, Vector4 inVect3) {
    m_eye = inVect;
    m_at = inVect2;
    m_upVect = inVect3;
  }
  
  Matrix4 
  Camera::getViewMatrix() {
    m_at = (m_eye + m_forward);
    m_viewMatrix = lookToLH(m_eye, m_at, m_upVect);
    return m_viewMatrix;
  }
  
  Matrix4 
  Camera::getProyectionMatrix() {
    m_projMatrix = perspectiveFovLH(m_angle, m_aspectRatio, m_near, m_far);
    return m_projMatrix;
  }

  void 
  Camera::resize(int32 inW, int32 inH) {
    int32 tmpAR = inW / inH;
    m_projMatrix = perspectiveFovLH(m_angle, float(tmpAR), m_near, m_far);
  }

  void 
  Camera::updateRotations() {
    /*Vector4 front;
    front.x = cos(Radians(m_YPR.x).getRadians());
    front.y = sin(Radians(m_YPR.y).getRadians());
    front.z = sin(Radians(m_YPR.x).getRadians());
    m_at = front;
    m_at.normalize();

    m_rightVector = m_at.cross(m_upVect);
    m_rightVector.normalize();
    m_upVect = m_rightVector.cross(m_at);
    m_upVect.normalize();*/


    float yawRad = Radians(m_YPR.x).getRadians();   // Yaw (horizontal)
    float pitchRad = Radians(m_YPR.y).getRadians(); // Pitch (vertical)

    // Cálculo correcto del vector forward
    m_forward.x = cos(yawRad) * cos(pitchRad);
    m_forward.y = sin(pitchRad);
    m_forward.z = sin(yawRad) * cos(pitchRad);
    m_forward.normalize();

    // Recalcular los vectores de cámara

    

    m_up2 = m_forward.cross(m_rightVector);
    m_rightVector = m_upVect.cross(m_forward);
    //m_rightVector = m_forward.cross({0.0f, 1.0f, 0.0f, 0.0f}); // Siempre sobre Y global
    m_rightVector.normalize();
    m_up2 = m_rightVector.cross(m_forward);
    m_up2.normalize();
  }

}