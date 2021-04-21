#define GTEST_HAS_TR1_TUPLE 0
#define GTEST_USE_OWN_TR1_TUPLE 0
#include <gtest/gtest.h>

#include <giPrerequisitesUtilities.h>
#include <giMath.h>
#include <giVector2.h>
#include <giVector2i.h>
#include <giVector3.h>
#include <giVector3i.h>
#include <giVector4.h>
#include <giVector4i.h>
#include <giMatrix4.h>

using namespace giEngineSDK;

/**
 * Main
 */
int
main(int argc, char** argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/**
 * Unit types test (Basic)
 */
TEST(giUtilities, BasicTypesTest) {
  EXPECT_EQ(sizeof(unsigned char), 1U);
  EXPECT_EQ(sizeof(uint8), 1U);
  EXPECT_EQ(sizeof(uint16), 2U);
  EXPECT_EQ(sizeof(uint32), 4U);
  EXPECT_EQ(sizeof(uint64), 8U);
  

  EXPECT_EQ(sizeof(char), 1);
  EXPECT_EQ(sizeof(int8), 1);
  EXPECT_EQ(sizeof(int16), 2);
  EXPECT_EQ(sizeof(int32), 4);
  EXPECT_EQ(sizeof(int64), 8);

  EXPECT_EQ(sizeof(float), 4);
  EXPECT_EQ(sizeof(double), 8);

  EXPECT_FLOAT_EQ(Math::PI, 3.141592f);
  
}

/**
 * Math functions
 */
TEST(BasicMathTest, MathTest) {
  //Quitar numeros magicos
  EXPECT_EQ(Math::sqr(10), 3);
  EXPECT_FLOAT_EQ(Math::sqr(10.f), 3.16227766f);
  EXPECT_EQ(Math::pow(10, 2), 100);
  EXPECT_FLOAT_EQ(Math::cos(10), -0.83907151f);
  EXPECT_FLOAT_EQ(Math::cosh(10), 11013.2329201f);
  EXPECT_FLOAT_EQ(Math::sin(10), -0.54402111f);
  EXPECT_FLOAT_EQ(Math::sinh(10), 11013.2328747f);
  EXPECT_FLOAT_EQ(Math::tan(10), 0.64836082f);
  EXPECT_FLOAT_EQ(Math::tanh(10), 1.f);
  EXPECT_EQ(Math::ln(10), 2);

}


/**
 * Vectors types
 */
TEST(VectorTest, VectorTest) {
  /**
   * Vectors 2i
   */
  {
    Vector2i tmpVector(2, 2);
    Vector2i tmpVector2 = { 3, 3 };
    //Increment
    Vector2i tmpVectorRes = tmpVector + tmpVector2;
    auto tmpIncrement2i = tmpVectorRes.x;
    EXPECT_EQ(tmpIncrement2i, 5);
    //Decrement
    tmpVectorRes = tmpVector2 - tmpVector;
    auto tmpDecrement2i = tmpVectorRes.x;
    EXPECT_EQ(tmpDecrement2i, 1);
    //Division
    tmpVectorRes = tmpVector2 / tmpVector;
    auto tmpDivision2i = tmpVectorRes.x;
    EXPECT_EQ(tmpDivision2i, 1);
    //Multiply
    tmpVectorRes = tmpVector2 * tmpVector;
    auto tmpMultiply2i = tmpVectorRes.x;
    EXPECT_EQ(tmpMultiply2i, 6);
  }
  /**
   * Vectors 2 floats
   */
  {
    Vector2 tmpVector(2, 2);
    Vector2 tmpVector2 = { 3, 3 };
    //Increment
    Vector2 tmpVectorRes = tmpVector + tmpVector2;
    auto tmpIncrement2 = tmpVectorRes.x;
    EXPECT_FLOAT_EQ(tmpIncrement2, 5.f);
    //Decrement
    tmpVectorRes = tmpVector2 - tmpVector;
    auto tmpDecrement2 = tmpVectorRes.x;
    EXPECT_FLOAT_EQ(tmpDecrement2, 1.f);
    //Division
    tmpVectorRes = tmpVector2 / tmpVector;
    auto tmpDivision2 = tmpVectorRes.x;
    EXPECT_FLOAT_EQ(tmpDivision2, 1.5f);
    //Multiply
    tmpVectorRes = tmpVector2 * tmpVector;
    auto tmpMultiply2 = tmpVectorRes.x;
    EXPECT_FLOAT_EQ(tmpMultiply2, 6.f);
  }
  /**
   * Vectors 3i
   */
  {
    Vector3i tmpVector(2, 2, 2);
    Vector3i tmpVector2 = { 3, 3, 3 };
    //Increment
    Vector3i tmpVectorRes = tmpVector + tmpVector2;
    auto tmpIncrement3i = tmpVectorRes.z;
    EXPECT_EQ(tmpIncrement3i, 5);
    //Decrement
    tmpVectorRes = tmpVector2 - tmpVector;
    auto tmpDecrement3i = tmpVectorRes.z;
    EXPECT_EQ(tmpDecrement3i, 1);
    //Division
    tmpVectorRes = tmpVector2 / tmpVector;
    auto tmpDivision3i = tmpVectorRes.z;
    EXPECT_EQ(tmpDivision3i, 1);
    //Multiply
    tmpVectorRes = tmpVector2 * tmpVector;
    auto tmpMultiply3i = tmpVectorRes.z;
    EXPECT_EQ(tmpMultiply3i, 6);
  }
  /**
   * Vectors 3 floats
   */
  {
    Vector3 tmpVector(2, 2, 2);
    Vector3 tmpVector2 = { 3, 3, 3 };
    //Increment
    Vector3 tmpVectorRes = tmpVector + tmpVector2;
    auto tmpIncrement3 = tmpVectorRes.z;
    EXPECT_FLOAT_EQ(tmpIncrement3, 5.f);
    //Decrement
    tmpVectorRes = tmpVector2 - tmpVector;
    auto tmpDecrement3 = tmpVectorRes.z;
    EXPECT_FLOAT_EQ(tmpDecrement3, 1.f);
    //Division
    tmpVectorRes = tmpVector2 / tmpVector;
    auto tmpDivision3 = tmpVectorRes.z;
    EXPECT_FLOAT_EQ(tmpDivision3, 1.5f);
    //Multiply
    tmpVectorRes = tmpVector2 * tmpVector;
    auto tmpMultiply3 = tmpVectorRes.z;
    EXPECT_FLOAT_EQ(tmpMultiply3, 6.f);
  }
  /**
   * Vectors 4i
   */
  {
    Vector4i tmpVector(2, 2, 2, 2);
    Vector4i tmpVector2 = { 3, 3, 3, 3 };
    //Increment
    Vector4i tmpVectorRes = tmpVector + tmpVector2;
    auto tmpIncrement4i = tmpVectorRes.w;
    EXPECT_EQ(tmpIncrement4i, 5);
    //Decrement
    tmpVectorRes = tmpVector2 - tmpVector;
    auto tmpDecrement4i = tmpVectorRes.w;
    EXPECT_EQ(tmpDecrement4i, 1);
    //Division
    tmpVectorRes = tmpVector2 / tmpVector;
    auto tmpDivision4i = tmpVectorRes.w;
    EXPECT_EQ(tmpDivision4i, 1);
    //Multiply
    tmpVectorRes = tmpVector2 * tmpVector;
    auto tmpMultiply4i = tmpVectorRes.w;
    EXPECT_EQ(tmpMultiply4i, 6);
  }
  /**
   * Vectors 4 floats
   */
  {
    Vector4 tmpVector(2, 2, 2, 2);
    Vector4 tmpVector2 = { 3, 3, 3, 3 };
    //Increment
    Vector4 tmpVectorRes = tmpVector + tmpVector2;
    auto tmpIncrement4 = tmpVectorRes.z;
    EXPECT_FLOAT_EQ(tmpIncrement4, 5.f);
    //Decrement
    tmpVectorRes = tmpVector2 - tmpVector;
    auto tmpDecrement4 = tmpVectorRes.z;
    EXPECT_FLOAT_EQ(tmpDecrement4, 1.f);
    //Division
    tmpVectorRes = tmpVector2 / tmpVector;
    auto tmpDivision4 = tmpVectorRes.z;
    EXPECT_FLOAT_EQ(tmpDivision4, 1.5f);
    //Multiply
    tmpVectorRes = tmpVector2 * tmpVector;
    auto tmpMultiply4 = tmpVectorRes.z;
    EXPECT_FLOAT_EQ(tmpMultiply4, 6.f);

  }


}

/**
 * Matrix types
 */
TEST(MatrixTest, MatixTest) {
  //Matrix declarations
  Vector4 vec1(1, 5, 9, 13);
  Vector4 vec2(2, 6, 10, 14);
  Vector4 vec3(3, 7, 11, 15);
  Vector4 vec4(4, 8, 12, 16);

  Matrix4 A(vec1, vec2, vec3, vec4);

  Matrix4 B({16, 12, 8, 4}, 
  /********/{15, 11, 7, 3}, 
  /********/{14, 10, 6, 2}, 
  /********/{13, 9, 5, 1});

  //Matrix increment test
  Matrix4 result = A + B;
  auto increment = result.m_wColumn.w;
  EXPECT_EQ(increment, 17);

  //Matrix Multpily test
  result = A * B;
  auto multiply = result.m_wColumn.w;
  EXPECT_EQ(multiply, 386);
  
  //Matrix Decrement test
  result = A - B;
  auto decrement = result.m_wColumn.w;
  EXPECT_EQ(decrement, 15);

  //Matrix determinant test
  EXPECT_EQ(A.determinant(), 0);

  Matrix4 C({ 5, 5, 5, 3 },    //1, -1, -1, 1
  /********/{ 5, 3, 5, 3 },    //0.5, -0.5, 0, 0 
  /********/{ 2, 5, 8, 3 },    //0.666, -1, -0.666, 1
  /********/{ 3, 3, 8, 3 });   //-3.277, 4.166, 2.777, -3.333
  
  //Matrix inverse test
  EXPECT_FLOAT_EQ(C.inverse().m_xColumn.w, -3.27777798f);
  EXPECT_FLOAT_EQ(C.inverse().m_zColumn.w, 2.77777778f);
}

/**
 * Std types
 */
TEST(STDTest, STDTest) {
  String str;

}