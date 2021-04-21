/**
 * @file    giCamera.cpp
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/04/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#include "giCamera.h"

namespace giEngineSDK {
  CCamera::CCamera() {
    m_Front = (m_At - m_Eye);
    m_Front.normalize();

    m_Right = crossProduct(m_Up, m_Front);
    m_Right.normalize();
    
    m_Up2 = crossProduct(m_Front, m_Right);
    m_Up2.normalize();
  }
  
  void 
  CCamera::init(float inAngle, float inAR, float inNear, float inFar) {
    m_Angle = inAngle;
    m_AspectRatio = inAR;
    m_Near = inNear;
    m_Far = inFar;
    update();
  }
  
  void 
  CCamera::update() {
    m_VM = lookToLH(m_Eye, m_At, m_Up);
    m_VM = m_VM.transpose();
    updateVM();

    m_PM = perspectiveFovLH(m_Angle, m_AspectRatio, m_Near, m_Far);
    m_PM = m_PM.transpose();
  }
  
  void 
  CCamera::updateVM() {
    m_Right = m_VM.m_xColumn;
    m_Up2 = m_VM.m_yColumn;
    m_Front = m_VM.m_zColumn;
    m_At = m_Front + m_Eye;
  }
  
  void 
  CCamera::move(Vector4 inVect) {
    
    if (inVect.x != 0.f) {
      m_Eye += (m_Right * inVect.x);
    }
    if (inVect.y != 0.f) {
      m_Eye += (m_Up2 * inVect.y);
    }
    if (inVect.z != 0.f) {
      m_Eye += (m_Front * inVect.z);
    }

    m_Up2.normalize();
    m_Right.normalize();
    m_Front.normalize();

    Matrix4 Axis({ m_Right.x,	m_Right.y,	m_Right.z,		0 },
    /***********/{ m_Up2.x,	m_Up2.y,	m_Up2.z,		0 },
    /***********/{ m_Front.x,	m_Front.y,	m_Front.z,		0 },
    /***********/{ 0,			0,			0,				1 });

    Matrix4 Pos({1,0,0,-m_Eye.x},
    /**********/{0,1,0,-m_Eye.y},
    /**********/{0,0,1,-m_Eye.z},
    /**********/{0,0,0,1});

    Pos *= Axis;
    m_VM = Pos;
  }
  
  Matrix4 
  CCamera::getViewMatrix() {
    update();
    return m_VM;
  }
  
  Matrix4 
  CCamera::getProyectionMatrix() {
    //Update the matrix
    update();

    //Returns the matrix
    return m_PM;
  }
}