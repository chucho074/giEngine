/**
 * @file    giCamera.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/04/2021
 * @brief   A basic camera.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giCamera.h"


namespace giEngineSDK {
  Camera::Camera() {
    m_front = (m_at - m_eye);
    m_front.normalize();

    m_right = m_up.cross(m_front);
    m_right.normalize();
    
    m_up2 = m_front.cross(m_right);
    //m_up2.normalize();
  }
  
  void 
  Camera::init(float inAngle, float inAR, float inNear, float inFar) {
    m_angle = inAngle;
    m_aspectRatio = inAR;
    m_near = inNear;
    m_far = inFar;
    updateData();
  }
  
  void 
  Camera::update(float inDT) {
    
  }

  void
  Camera::updateData() {
    m_viewMatrix = lookToLH(m_eye, m_at, m_up);
    
    //updateVM();
    //m_viewMatrix = m_viewMatrix.transpose();
    
    m_projMatrix = perspectiveFovLH(m_angle, m_aspectRatio, m_near, m_far);
  }
  
  void 
  Camera::updateVM() {
    m_right = m_viewMatrix.m_xColumn;
    m_right.w = 0.f;

    m_up2 = m_viewMatrix.m_yColumn;
    m_up2.w = 0.f;
    
    m_front = m_viewMatrix.m_zColumn;
    m_front.w = 0.f;
    
    m_at = m_eye + m_front;
  }
  
  void 
  Camera::move(Vector4 inVect) {
    
    if (inVect.x != 0.f) {
      m_eye += (m_right * inVect.x);
    }
    if (inVect.y != 0.f) {
      m_eye += (m_up2 * inVect.y);
    }
    if (inVect.z != 0.f) {
      m_eye += (m_front * inVect.z);
    }

    m_up2.normalize();
    m_right.normalize();
    m_front.normalize();

    Matrix4 Axis({ m_right.x,  m_right.y,  m_right.z,    0 },
                 { m_up2.x,    m_up2.y,    m_up2.z,      0 },
                 { m_front.x,  m_front.y,  m_front.z,    0 },
                 { 0,      0,      0,        1 });
    Axis.transpose();

    Matrix4 Pos({1, 0, 0, -m_eye.x},
                {0, 1, 0, -m_eye.y},
                {0, 0, 1, -m_eye.z},
                {0, 0, 0, 1});
    //Pos.transpose();

    
    m_viewMatrix = Axis * Pos;
  }

  void 
  Camera::setPosition(Vector4 inVect, Vector4 inVect2, Vector4 inVect3) {
    m_eye = inVect;
    m_at = inVect2;
    m_up = inVect3;
  }
  
  Matrix4 
  Camera::getViewMatrix() {
    updateData();
    return m_viewMatrix;
  }
  
  Matrix4 
  Camera::getProyectionMatrix() {
    //Update the matrix
    updateData();

    //Returns the matrix
    return m_projMatrix;
  }
}