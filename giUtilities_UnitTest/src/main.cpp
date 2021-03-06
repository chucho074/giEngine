#define GTEST_HAS_TR1_TUPLE 0
#define GTEST_USE_OWN_TR1_TUPLE 0
#include <gtest/gtest.h>

#include <giPrerequisitesUtilities.h>
#include <giPlatformMath.h>
#include <giVector2.h>
#include <giVector2i.h>
#include <giVector3.h>
#include <giVector3i.h>
#include <giVector4.h>
#include <giVector4i.h>
#include <giMatrix4.h>

using namespace giEngineSDK;


int
main(int argc, char** argv) {
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


TEST(giUtilities, BasicTest) {
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

  //EXPECT_EQ(static_cast<uint32>(-1), NumLimit::MAX_UINT32);
  //EXPECT_FLOAT_EQ(PlatformMath::PI, 3.141592f);
  
  
}



TEST(VectorTest, VectorTest) {
  //giVector2i tmpVector(2,2);
  //giVector2i tmpVector2 = {3, 3};
  //giVector2i tmpVectorRes = tmpVector + tmpVector2;
  //auto tmpData = tmpVectorRes.getX();
  //EXPECT_EQ(tmpData, 5);

}


TEST(VectorTest, MathTest) {
  EXPECT_EQ(PlatformMath::sqr(10), 3);
  //EXPECT_FLOAT_EQ(PlatformMath::sqr(10.f), 3.16227766f);
  EXPECT_EQ(PlatformMath::pow(10, 2), 100);
  EXPECT_FLOAT_EQ(PlatformMath::cos(10), -0.83907151f);
  EXPECT_FLOAT_EQ(PlatformMath::cosh(10), 11013.2329201f);
  EXPECT_FLOAT_EQ(PlatformMath::sin(10), -0.54402111f);
  EXPECT_FLOAT_EQ(PlatformMath::sinh(10), 11013.2328747f);
  EXPECT_FLOAT_EQ(PlatformMath::tan(10), 0.64836082f);
  EXPECT_FLOAT_EQ(PlatformMath::tanh(10), 1.f);
  EXPECT_EQ(PlatformMath::ln(10), 2);


}