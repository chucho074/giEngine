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
  //EXPECT_FLOAT_EQ(Math::PI, 3.141592f);
  
  
}
