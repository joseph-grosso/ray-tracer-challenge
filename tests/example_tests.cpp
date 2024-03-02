#include "gtest/gtest.h"

TEST(BasicTests, testName) {
    EXPECT_EQ(1, 2);
}

TEST(BasicTests, testName2) {
    ASSERT_EQ(2, 2);
}

TEST(BasicTests, testName3) {
    ASSERT_EQ(3, 3);
}

TEST(BasicTests, testName4) {
    ASSERT_EQ(4, 4);
}
