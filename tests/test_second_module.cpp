/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2021 J.Marple
/// @brief Unit testing for second_module

#include <gtest/gtest.h>

#include <string>

// cppcheck-suppress unusedFunction
TEST(DummyTest, TestDummy) { EXPECT_EQ(1.0, 1.0); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  auto test_results = RUN_ALL_TESTS();

  return test_results;
}
