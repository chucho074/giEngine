/**
 * @file    giCamera.cpp
 * @author  Jesus Alberto Del Moral Cupil
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
    m_forward = (m_at - m_eye);
    m_forward.normalize();

    m_rightVector = m_upVect.cross(m_forward);
    m_rightVector.normalize();
    
    m_up2 = m_forward.cross(m_rightVector);
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
    move(inDT);
  }

  void
  Camera::updateData() {
    m_viewMatrix = lookToLH(m_eye, m_at, m_upVect);
    
    //updateVM();
    //m_viewMatrix = m_viewMatrix.transpose();
    
    m_projMatrix = perspectiveFovLH(m_angle, m_aspectRatio, m_near, m_far);
  }
  
  void 
  Camera::updateVM() {
    m_rightVector = m_viewMatrix.m_xColumn;
    m_rightVector.w = 0.f;

    m_up2 = m_viewMatrix.m_yColumn;
    m_up2.w = 0.f;
    
    m_forward = m_viewMatrix.m_zColumn;
    m_forward.w = 0.f;
    
    m_at = m_eye + m_forward;
  }
  
  void 
  Camera::move(float inDT) {
    
    Vector3 pos = Vector3(m_viewMatrix.m_wColumn.x,
                          m_viewMatrix.m_wColumn.y,
                          m_viewMatrix.m_wColumn.z);

    Vector3 tmpVect;

    if(m_front || m_back) {
      tmpVect.x = m_viewMatrix.m_zColumn.x;
      tmpVect.y = m_viewMatrix.m_zColumn.y;
      tmpVect.z = m_viewMatrix.m_zColumn.z;
    }
    
    if(m_right || m_left) {
      tmpVect.x = m_viewMatrix.m_xColumn.x;
      tmpVect.y = m_viewMatrix.m_xColumn.y;
      tmpVect.z = m_viewMatrix.m_xColumn.z;
    }

    if(m_up || m_down) {
      tmpVect.x = m_viewMatrix.m_yColumn.x;
      tmpVect.y = m_viewMatrix.m_yColumn.y;
      tmpVect.z = m_viewMatrix.m_yColumn.z;
    }


    float tmpSpeed = m_speed;

    if(m_down || m_right || m_front) {
      tmpSpeed = -m_speed;
    }

    auto tmpResult = tmpVect * (tmpSpeed * inDT);

    pos += tmpResult;

    m_viewMatrix.m_wColumn.x = pos.x;
    m_viewMatrix.m_wColumn.y = pos.y;
    m_viewMatrix.m_wColumn.z = pos.z;
  }

  void 
  Camera::setPosition(Vector4 inVect, Vector4 inVect2, Vector4 inVect3) {
    m_eye = inVect;
    m_at = inVect2;
    m_upVect = inVect3;
    updateData();
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