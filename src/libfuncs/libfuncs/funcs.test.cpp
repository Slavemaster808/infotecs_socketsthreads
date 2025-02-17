#include <gtest/gtest.h>
#include <libfuncs/funcs.hpp>

TEST(helperTests, strTransform) {
  std::string str1 = "12345678";
  helper::strTransform(str1);

  std::string str2 = "7777";
  helper::strTransform(str2);

  ASSERT_EQ(str1, "KB7KB5KB3KB1");
  ASSERT_EQ(str2, "7777");
}

TEST(helperTests, strDigitSum) {
  const std::string& str1 = "22KB3KBKB1";
  unsigned int sum1 = helper::strDigitSum(str1);

  const std::string& str2 = "KBKBKB";
  unsigned int sum2 = helper::strDigitSum(str2);

  ASSERT_EQ(sum1, 8);
  ASSERT_EQ(sum2, 0);
}

TEST(helperTests, checkDigit) {
  bool res1 = helper::checkDigit(64);
  bool res2 = helper::checkDigit(77);

  ASSERT_EQ(res1, true);
  ASSERT_EQ(res2, false);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}