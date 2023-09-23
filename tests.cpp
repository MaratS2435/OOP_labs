#include <gtest/gtest.h>
#include <string>
#include "change.h"

TEST(test_01, basic_test_set) 
{
    ASSERT_TRUE(change("aabb")=="bbaa");
}

TEST(test_02, basic_test_set) 
{
    ASSERT_TRUE(change("a")=="b");
}

TEST(test_03, basic_test_set) 
{
    ASSERT_TRUE(change("acbb")=="bcaa");
}

TEST(test_04, basic_test_set) 
{
    ASSERT_TRUE(change("ccc")=="ccc");
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
