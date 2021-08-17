/**
 * @file    giMatrix4.cpp
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    12/02/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */

#include "giMatrix4.h"
#include "giVector4.h"

namespace giEngineSDK {
  
  const Matrix4 
  Matrix4::IDENTITY = Matrix4({ 1, 0, 0, 0 },
                              { 0, 1, 0, 0 },
                              { 0, 0, 1, 0 },
                              { 0, 0, 0, 1 });

  Matrix4::Matrix4(Matrix4& inMatrix) {
    m_xColumn = inMatrix.m_xColumn;
    m_yColumn = inMatrix.m_yColumn;
    m_zColumn = inMatrix.m_zColumn;
    m_wColumn = inMatrix.m_wColumn;
  }

  Matrix4
  Matrix4::operator+(const Matrix4& inMatrix) const {
    Matrix4 tmpMat;
    tmpMat.m_xColumn = m_xColumn + inMatrix.m_xColumn;
    tmpMat.m_yColumn = m_yColumn + inMatrix.m_yColumn;
    tmpMat.m_zColumn = m_zColumn + inMatrix.m_zColumn;
    tmpMat.m_wColumn = m_wColumn + inMatrix.m_wColumn;
    return tmpMat;
  }

  Matrix4
  Matrix4::operator-(const Matrix4& inMatrix) const {
    Matrix4 tmpMat;
    tmpMat.m_xColumn = m_xColumn - inMatrix.m_xColumn;
    tmpMat.m_yColumn = m_yColumn - inMatrix.m_yColumn;
    tmpMat.m_zColumn = m_zColumn - inMatrix.m_zColumn;
    tmpMat.m_wColumn = m_wColumn - inMatrix.m_wColumn;
    return tmpMat;
  }

  Matrix4
  Matrix4::operator*(const Matrix4& inMatrix)  {
    
    
    Matrix4 tmpMatrix = inMatrix.transpose();
    Vector4 tmpX((m_xColumn.dotProd(tmpMatrix.m_xColumn)),
                 (m_yColumn.dotProd(tmpMatrix.m_xColumn)),
                 (m_zColumn.dotProd(tmpMatrix.m_xColumn)),
                 (m_wColumn.dotProd(tmpMatrix.m_xColumn)));

    Vector4 tmpY((m_xColumn.dotProd(tmpMatrix.m_yColumn)), 
                 (m_yColumn.dotProd(tmpMatrix.m_yColumn)),
                 (m_zColumn.dotProd(tmpMatrix.m_yColumn)),
                 (m_wColumn.dotProd(tmpMatrix.m_yColumn)));
    
    Vector4 tmpZ((m_xColumn.dotProd(tmpMatrix.m_zColumn)),
                 (m_yColumn.dotProd(tmpMatrix.m_zColumn)),
                 (m_zColumn.dotProd(tmpMatrix.m_zColumn)),
                 (m_wColumn.dotProd(tmpMatrix.m_zColumn)));
    
    Vector4 tmpW((m_xColumn.dotProd(tmpMatrix.m_wColumn)),
                 (m_yColumn.dotProd(tmpMatrix.m_wColumn)),
                 (m_zColumn.dotProd(tmpMatrix.m_wColumn)),
                 (m_wColumn.dotProd(tmpMatrix.m_wColumn)));

    Matrix4 Result(tmpX, tmpY, tmpZ, tmpW);

    //xColumn
    /*Result.m_xColumn.x = ((m_xColumn.x * inMatrix.m_xColumn.x)
                          + (m_yColumn.x * inMatrix.m_xColumn.y)
                          + (m_zColumn.x * inMatrix.m_xColumn.z)
                          + (m_wColumn.x * inMatrix.m_xColumn.w));

    Result.m_xColumn.y = ((m_xColumn.y * inMatrix.m_xColumn.x)
                          + (m_yColumn.y * inMatrix.m_xColumn.y)
                          + (m_zColumn.y * inMatrix.m_xColumn.z)
                          + (m_wColumn.y * inMatrix.m_xColumn.w));

    Result.m_xColumn.z = ((m_xColumn.z * inMatrix.m_xColumn.x)
                          + (m_yColumn.z * inMatrix.m_xColumn.y)
                          + (m_zColumn.z * inMatrix.m_xColumn.z)
                          + (m_wColumn.z * inMatrix.m_xColumn.w));

    Result.m_xColumn.w = ((m_xColumn.w * inMatrix.m_xColumn.x)
                          + (m_yColumn.w * inMatrix.m_xColumn.y)
                          + (m_zColumn.w * inMatrix.m_xColumn.z)
                          + (m_wColumn.w * inMatrix.m_xColumn.w));

    //yColumn
    Result.m_yColumn.x = ((m_xColumn.x * inMatrix.m_yColumn.x)
                          + (m_yColumn.x * inMatrix.m_yColumn.y)
                          + (m_zColumn.x * inMatrix.m_yColumn.z)
                          + (m_wColumn.x * inMatrix.m_yColumn.w));

    Result.m_yColumn.y = ((m_xColumn.y * inMatrix.m_yColumn.x)
                          + (m_yColumn.y * inMatrix.m_yColumn.y)
                          + (m_zColumn.y * inMatrix.m_yColumn.z)
                          + (m_wColumn.y * inMatrix.m_yColumn.w));

    Result.m_yColumn.z = ((m_xColumn.z * inMatrix.m_yColumn.x)
                          + (m_yColumn.z * inMatrix.m_yColumn.y)
                          + (m_zColumn.z * inMatrix.m_yColumn.z)
                          + (m_wColumn.z * inMatrix.m_yColumn.w));

    Result.m_yColumn.w = ((m_xColumn.w * inMatrix.m_yColumn.x)
                          + (m_yColumn.w * inMatrix.m_yColumn.y)
                          + (m_zColumn.w * inMatrix.m_yColumn.z)
                          + (m_wColumn.w * inMatrix.m_yColumn.w));

    //zColumn
    Result.m_zColumn.x = ((m_xColumn.x * inMatrix.m_zColumn.x)
                          + (m_yColumn.x * inMatrix.m_zColumn.y)
                          + (m_zColumn.x * inMatrix.m_zColumn.z)
                          + (m_wColumn.x * inMatrix.m_zColumn.w));

    Result.m_zColumn.y = ((m_xColumn.y * inMatrix.m_zColumn.x)
                          + (m_yColumn.y * inMatrix.m_zColumn.y)
                          + (m_zColumn.y * inMatrix.m_zColumn.z)
                          + (m_wColumn.y * inMatrix.m_zColumn.w));

    Result.m_zColumn.z = ((m_xColumn.z * inMatrix.m_zColumn.x)
                          + (m_yColumn.z * inMatrix.m_zColumn.y)
                          + (m_zColumn.z * inMatrix.m_zColumn.z)
                          + (m_wColumn.z * inMatrix.m_zColumn.w));

    Result.m_zColumn.w = ((m_xColumn.w * inMatrix.m_zColumn.x)
                          + (m_yColumn.w * inMatrix.m_zColumn.y)
                          + (m_zColumn.w * inMatrix.m_zColumn.z)
                          + (m_wColumn.w * inMatrix.m_zColumn.w));

    //wColumn
    Result.m_wColumn.x = ((m_xColumn.x * inMatrix.m_wColumn.x)
                          + (m_yColumn.x * inMatrix.m_wColumn.y)
                          + (m_zColumn.x * inMatrix.m_wColumn.z)
                          + (m_wColumn.x * inMatrix.m_wColumn.w));

    Result.m_wColumn.y = ((m_xColumn.y * inMatrix.m_wColumn.x)
                          + (m_yColumn.y * inMatrix.m_wColumn.y)
                          + (m_zColumn.y * inMatrix.m_wColumn.z)
                          + (m_wColumn.y * inMatrix.m_wColumn.w));

    Result.m_wColumn.z = ((m_xColumn.z * inMatrix.m_wColumn.x)
                          + (m_yColumn.z * inMatrix.m_wColumn.y)
                          + (m_zColumn.z * inMatrix.m_wColumn.z)
                          + (m_wColumn.z * inMatrix.m_wColumn.w));

    Result.m_wColumn.w = ((m_xColumn.w * inMatrix.m_wColumn.x)
                          + (m_yColumn.w * inMatrix.m_wColumn.y)
                          + (m_zColumn.w * inMatrix.m_wColumn.z)
                          + (m_wColumn.w * inMatrix.m_wColumn.w));*/
      
    //Result.transpose();
    return Result;
  }

  void
  Matrix4::operator*=(float inValue) {
    m_xColumn = m_xColumn * inValue;
    m_yColumn = m_yColumn * inValue;
    m_zColumn = m_zColumn * inValue;
    m_wColumn = m_wColumn * inValue;
  }

  bool
  Matrix4::operator==(const Matrix4& inMatrix) const {
    if ((m_xColumn == inMatrix.m_xColumn) &&
      (m_yColumn == inMatrix.m_yColumn) &&
      (m_zColumn == inMatrix.m_zColumn) &&
      (m_wColumn == inMatrix.m_wColumn)) {

      return true;
    }

    return false;
  }

  bool
  Matrix4::operator!=(const Matrix4& inMatrix) const {
    return !this->operator==(inMatrix);
  }

  Matrix4 
  Matrix4::inverse() const {

    Matrix4 Result;
    
    if (0.0f == determinant()) {
      Result = Matrix4::IDENTITY;
    }
    else {
      Matrix4 tmpMat;
    
      tmpMat.m_xColumn.x = m_zColumn.z * m_wColumn.w - m_zColumn.w * m_wColumn.z;
      tmpMat.m_xColumn.y = m_yColumn.z * m_wColumn.w - m_yColumn.w * m_wColumn.z;
      tmpMat.m_xColumn.z = m_yColumn.z * m_zColumn.w - m_yColumn.w * m_zColumn.z;
    
      tmpMat.m_yColumn.x = m_zColumn.z * m_wColumn.w - m_zColumn.w * m_wColumn.z;
      tmpMat.m_yColumn.y = m_xColumn.z * m_wColumn.w - m_xColumn.w * m_wColumn.z;
      tmpMat.m_yColumn.z = m_xColumn.z * m_zColumn.w - m_xColumn.w * m_zColumn.z;
    
      tmpMat.m_zColumn.x = m_yColumn.z * m_wColumn.w - m_yColumn.w * m_wColumn.z;
      tmpMat.m_zColumn.y = m_xColumn.z * m_wColumn.w - m_xColumn.w * m_wColumn.z;
      tmpMat.m_zColumn.z = m_xColumn.z * m_yColumn.w - m_xColumn.w * m_yColumn.z;
    
      tmpMat.m_wColumn.x = m_yColumn.z * m_zColumn.w - m_yColumn.w * m_zColumn.z;
      tmpMat.m_wColumn.y = m_xColumn.z * m_zColumn.w - m_xColumn.w * m_zColumn.z;
      tmpMat.m_wColumn.z = m_xColumn.z * m_yColumn.w - m_xColumn.w * m_yColumn.z;
    
      float Det0 = m_yColumn.y * tmpMat.m_xColumn.x - m_zColumn.y * 
                   tmpMat.m_xColumn.y + m_wColumn.y * tmpMat.m_xColumn.z;

      float Det1 = m_xColumn.y * tmpMat.m_yColumn.x - m_zColumn.y * 
                   tmpMat.m_yColumn.y + m_wColumn.y * tmpMat.m_yColumn.z;

      float Det2 = m_xColumn.y * tmpMat.m_zColumn.x - m_yColumn.y * 
                   tmpMat.m_zColumn.y + m_wColumn.y * tmpMat.m_zColumn.z;

      float Det3 = m_xColumn.y * tmpMat.m_wColumn.x - m_yColumn.y * 
                   tmpMat.m_wColumn.y + m_zColumn.y * tmpMat.m_wColumn.z;
    
      float Determinant = m_xColumn.x * Det0 - m_yColumn.x * Det1 + m_zColumn.x * Det2 - m_wColumn.x * Det3;
      float  RDet = 1.0f / Determinant;
    
      //x
      Result.m_xColumn.x =  RDet * Det0;
      Result.m_xColumn.y = -RDet * (m_yColumn.x * tmpMat.m_xColumn.x -
                                 m_zColumn.x * tmpMat.m_xColumn.y +
                                 m_wColumn.x * tmpMat.m_xColumn.z);
      Result.m_xColumn.z =  RDet * (m_yColumn.x * (m_zColumn.y * m_wColumn.w - m_zColumn.w * m_wColumn.y) -
                                 m_zColumn.x * (m_yColumn.y * m_wColumn.w - m_yColumn.w * m_wColumn.y) +
                                 m_wColumn.x * (m_yColumn.y * m_zColumn.w - m_yColumn.w * m_zColumn.y));
      Result.m_xColumn.w = -RDet * (m_yColumn.x * (m_zColumn.y * m_wColumn.z - m_zColumn.z * m_wColumn.y) -
                                 m_zColumn.x * (m_yColumn.y * m_wColumn.z - m_yColumn.z * m_wColumn.y) +
                                 m_wColumn.x * (m_yColumn.y * m_zColumn.z - m_yColumn.z * m_zColumn.y));
      //y
      Result.m_yColumn.x = -RDet * Det1;
      Result.m_yColumn.y =  RDet * (m_xColumn.x * tmpMat.m_yColumn.x -
                                 m_zColumn.x * tmpMat.m_yColumn.y +
                                 m_wColumn.x * tmpMat.m_yColumn.z);
      Result.m_yColumn.z = -RDet * (m_xColumn.x * (m_zColumn.y * m_wColumn.w - m_zColumn.w * m_wColumn.y) -
                                 m_zColumn.x * (m_xColumn.y * m_wColumn.w - m_xColumn.w * m_wColumn.y) +
                                 m_wColumn.x * (m_xColumn.y * m_zColumn.w - m_xColumn.w * m_zColumn.y));
      Result.m_yColumn.w =  RDet * (m_xColumn.x * (m_zColumn.y * m_wColumn.z - m_zColumn.z * m_wColumn.y) -
                                 m_zColumn.x * (m_xColumn.y * m_wColumn.z -m_xColumn.z * m_wColumn.y) +
                                 m_wColumn.x * (m_xColumn.y * m_zColumn.z -m_xColumn.z * m_zColumn.y));
      //z
      Result.m_zColumn.x =  RDet * Det2;
      Result.m_zColumn.y = -RDet * (m_xColumn.x * tmpMat.m_zColumn.x -
                                 m_yColumn.x * tmpMat.m_zColumn.y +
                                 m_wColumn.x * tmpMat.m_zColumn.z);
      Result.m_zColumn.z =  RDet * (m_xColumn.x * (m_yColumn.y * m_wColumn.w - m_yColumn.w * m_wColumn.y) -
                                 m_yColumn.x * (m_xColumn.y * m_wColumn.w - m_xColumn.w * m_wColumn.y) +
                                 m_wColumn.x * (m_xColumn.y * m_yColumn.w - m_xColumn.w * m_yColumn.y));
      Result.m_zColumn.w = -RDet * (m_xColumn.x * (m_yColumn.y * m_wColumn.z - m_yColumn.z * m_wColumn.y) -
                                 m_yColumn.x * (m_xColumn.y * m_wColumn.z -m_xColumn.z * m_wColumn.y) +
                                 m_wColumn.x * (m_xColumn.y * m_yColumn.z -m_xColumn.z * m_yColumn.y));
      //w
      Result.m_wColumn.x = -RDet * Det3;
      Result.m_wColumn.w =  RDet * (m_xColumn.x * tmpMat.m_wColumn.x -
                                 m_yColumn.x * tmpMat.m_wColumn.y +
                                 m_zColumn.x * tmpMat.m_wColumn.z);
      Result.m_wColumn.w = -RDet * (m_xColumn.x * (m_yColumn.y * m_zColumn.w - m_yColumn.w * m_zColumn.y) -
                                 m_yColumn.x * (m_xColumn.y * m_zColumn.w - m_xColumn.w * m_zColumn.y) +
                                 m_zColumn.x * (m_xColumn.y * m_yColumn.w - m_xColumn.w * m_yColumn.y));
      Result.m_wColumn.w =  RDet * (m_xColumn.x * (m_yColumn.y * m_zColumn.z - m_yColumn.z * m_zColumn.y) -
                                 m_yColumn.x * (m_xColumn.y * m_zColumn.z -m_xColumn.z * m_zColumn.y) +
                                 m_zColumn.x * (m_xColumn.y * m_yColumn.z -m_xColumn.z * m_yColumn.y));
    }
     
    
    return Result;
  }

  float
  Matrix4::determinant() const {
    return m_xColumn.x * (
             m_yColumn.y * (m_zColumn.z * m_wColumn.w - m_zColumn.w * m_wColumn.z) -
             m_zColumn.y * (m_yColumn.z * m_wColumn.w - m_yColumn.w * m_wColumn.z) +
             m_wColumn.y * (m_yColumn.z * m_zColumn.w - m_yColumn.w * m_zColumn.z)
             ) - m_yColumn.x * (
             m_xColumn.y * (m_zColumn.z * m_wColumn.w - m_zColumn.w * m_wColumn.z) -
             m_zColumn.y * (m_xColumn.z * m_wColumn.w - m_xColumn.w * m_wColumn.z) +
             m_wColumn.y * (m_xColumn.z * m_zColumn.w - m_xColumn.w * m_zColumn.z)
             ) + m_zColumn.x * (
             m_xColumn.y * (m_yColumn.z * m_wColumn.w - m_yColumn.w * m_wColumn.z) -
             m_yColumn.y * (m_xColumn.z * m_wColumn.w - m_xColumn.w * m_wColumn.z) +
             m_wColumn.y * (m_xColumn.z * m_yColumn.w - m_xColumn.w * m_yColumn.z)
             ) - m_wColumn.x * (
             m_xColumn.y * (m_yColumn.z * m_zColumn.w - m_yColumn.w * m_zColumn.z) -
             m_yColumn.y * (m_xColumn.z * m_zColumn.w - m_xColumn.w * m_zColumn.z) +
             m_zColumn.y * (m_xColumn.z * m_yColumn.w - m_xColumn.w * m_yColumn.z));
  }
  
  Matrix4 
  Matrix4::transpose() const {
    Matrix4  Result;
    //
    Result.m_xColumn.x = m_xColumn.x;
    Result.m_xColumn.y = m_yColumn.x;
    Result.m_xColumn.z = m_zColumn.x;
    Result.m_xColumn.w = m_wColumn.x;
    //
    Result.m_yColumn.x = m_xColumn.y;
    Result.m_yColumn.y = m_yColumn.y;
    Result.m_yColumn.z = m_zColumn.y;
    Result.m_yColumn.w = m_wColumn.y;
    //
    Result.m_zColumn.x = m_xColumn.z;
    Result.m_zColumn.y = m_yColumn.z;
    Result.m_zColumn.z = m_zColumn.z;
    Result.m_zColumn.w = m_wColumn.z;
    //
    Result.m_wColumn.x = m_xColumn.w;
    Result.m_wColumn.y = m_yColumn.w;
    Result.m_wColumn.z = m_zColumn.w;
    Result.m_wColumn.w = m_wColumn.w;

    return Result;
  }

  void 
  Matrix4::negateMatrix() {
    //X Column
    m_xColumn.x = -m_xColumn.x;
    m_xColumn.y = -m_xColumn.y;
    m_xColumn.z = -m_xColumn.z;
    m_xColumn.w = -m_xColumn.w;
    //Y Column
    m_yColumn.x = -m_yColumn.x;
    m_yColumn.y = -m_yColumn.y;
    m_yColumn.z = -m_yColumn.z;
    m_yColumn.w = -m_yColumn.w;
    //Z Column
    m_zColumn.x = -m_zColumn.x;
    m_zColumn.y = -m_zColumn.y;
    m_zColumn.z = -m_zColumn.z;
    m_zColumn.w = -m_zColumn.w;
    //W Column
    m_wColumn.x = -m_wColumn.x;
    m_wColumn.y = -m_wColumn.y;
    m_wColumn.z = -m_wColumn.z;
    m_wColumn.w = -m_wColumn.w;
  }

  lookToLH::lookToLH(Vector4 inEyePos, 
                     Vector4 inEyeDirection, 
                     Vector4 inUpDirection) {
    
    Vector4 z = (inEyeDirection - inEyePos);
    z.normalize();

    Vector4 x;
    x = inUpDirection.cross(z);
    x.normalize();

    Vector4 y;
    y = z.cross(x);

    x.w = x.dotProd(-inEyePos);
    y.w = y.dotProd(-inEyePos);
    z.w = z.dotProd(-inEyePos);

    m_xColumn = x; 
    m_yColumn = y; 
    m_zColumn = z; 
    m_wColumn = { 0, 0, 0, 1 };

  }


  perspectiveFovLH::perspectiveFovLH(float inFov, 
                                     float inAR, 
                                     float inNear, 
                                     float inFar) {

    //float h = cosf(inFov) / sinf(inFov);
    //float w = h / inAR;
    //float viewRange = inFar / (inFar - inNear);

    float    SinFov = sinf(0.5f * inFov);
    float    CosFov = cosf(0.5f * inFov);

    float Height = CosFov / SinFov;
    float Width = Height / inAR;
    float fRange = inFar / (inFar - inNear);


    m_xColumn = { Width, 0, 0, 0 };
    m_yColumn = { 0, Height, 0, 0 };
    m_zColumn = { 0, 0, fRange, 1 };
    m_wColumn = { 0, 0, -fRange * inNear, 0 };


  }

  
  matrixRotationX::matrixRotationX(float inAngle) {
    float    fSinAngle = Math::sin(inAngle);
    float    fCosAngle = Math::cos(inAngle);

    
    m_xColumn = {1, 0.0f, 0.0f, 0.0f};

    m_yColumn = {0.0f, fCosAngle, fSinAngle, 0.0f};

    m_zColumn = {0.0f, -fSinAngle, fCosAngle, 0.0f};

    m_wColumn = {0.0f, 0.0f, 0.0f, 1.0f};

  }
  
  matrixRotationY::matrixRotationY(float inAngle) {
    float    fSinAngle = Math::sin(inAngle);
    float    fCosAngle = Math::cos(inAngle);

    
    m_xColumn = {fCosAngle, 0.0f, -fSinAngle, 0.0f};

    m_yColumn = {0.0f, 1.0f, 0.0f, 0.0f};

    m_zColumn = {fSinAngle, 0.0f, fCosAngle, 0.0f};

    m_wColumn = {0.0f, 0.0f, 0.0f, 1.0f};

  }
  
  matrixRotationZ::matrixRotationZ(float inAngle) {
    float    fSinAngle = Math::sin(inAngle);
    float    fCosAngle = Math::cos(inAngle);

    
    m_xColumn = {fCosAngle, -fSinAngle, 0.0f, 0.0f};

    m_yColumn = {fSinAngle, fCosAngle, 0.0f, 0.0f};

    m_zColumn = {0.0f, 0.0f, 1.0f, 0.0f};

    m_wColumn = {0.0f, 0.0f, 0.0f, 1.0f};
    
  }

  matrixTranslation::matrixTranslation(Vector3 inVector) {
    
    m_xColumn = {1.0f, 0.0f, 0.0f, 0.0f};

    m_yColumn = {0.0f, 1.0f, 0.0f, 0.0f};

    m_zColumn = {0.0f, 0.0f, 1.0f, 0.0f};

    m_wColumn = {inVector.x, inVector.y, inVector.z, 1.0f};
    
    /*m_xColumn = {1.0f, 0.0f, 0.0f, inVector.x};

    m_yColumn = {0.0f, 1.0f, 0.0f, inVector.y};

    m_zColumn = {0.0f, 0.0f, 1.0f, inVector.z};

    m_wColumn = {0, 0, 0, 1.0f};*/

  }

}