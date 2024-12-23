// all_tests.cpp
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  // uncomment below to run subset of tests based on filter
  ::testing::GTEST_FLAG(filter) = "TestFresnel*";
  return RUN_ALL_TESTS();
}
