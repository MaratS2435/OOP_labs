#include <gtest/gtest.h>
#include "Five.h"

bool constructorTest() {
    Five s1 {'1', '2', '3'};
    std::string test = "123";
    Five s2(test);
    Five s3 {'3', '4', '1'}, s3_1(s3), s4(std::move(s3)), s5(5, '1');
    std::cout << s1 << ": s1 " << s2 << ": s2 " << " : s3_1 " << s4 << " : s4 " << s5 << " : s5 " << std::endl;
    return (s1 == s2 and s3_1 == s4 and s3_1 != s5);
}

TEST(constructorTest, test_01) {
    ASSERT_TRUE(constructorTest());
}

TEST(throw_constructor_test, test_01) {
    ASSERT_ANY_THROW(Five s1("689"));
}

TEST(throw_constructor_test, test_02) {
    ASSERT_ANY_THROW(Five s1("12%"));
}

TEST(throw_constructor_test, test_03) {
    std::string test = "24 1";
    ASSERT_ANY_THROW(Five s1(test));
}


TEST(equal, test01) {
    Five num1("0"), num2("0");
    ASSERT_TRUE(num1 == num2);
}

TEST(equal,test02) {
    Five num1("00000000"), num2("0");
    std::cout << num1 << ' ' << num2 << std::endl;
    ASSERT_TRUE(num1 == num2);
}

TEST(equal, test03) {
    Five num1("12"), num2("11");
    ASSERT_FALSE(num1 == num2);
}

TEST(equal, test04) {
    Five num1("31");
    ASSERT_TRUE(num1 == Five("31"));
}

TEST(equal, test05) {
    Five num1("111");
    ASSERT_FALSE(num1 == Five("112"));
}

TEST(equal, test06) {
    Five num1("0000000111"), num2("111");
    ASSERT_TRUE(num1 == num2);
}


TEST(not_equal, test01) {
    Five num1("1044"), num2("1044");
    ASSERT_FALSE(num1 != num2);
}

TEST(not_equal, test02) {
    Five num1("1100"), num2("1212");
    ASSERT_TRUE(num1 != num2);
}

TEST(not_equal, test03) {
    Five num1("322");
    ASSERT_TRUE(num1 != Five());
}

TEST(greater, test01) {
    Five num1("1222"), num2("1000");
    ASSERT_TRUE(num1 > num2);
}

TEST(greater, test02) {
    Five num1("123");
    ASSERT_FALSE(num1 > num1);
}

TEST(greater, test03) {
    Five num1("10101"), num2("100");
    ASSERT_TRUE(num1 > num2);
}

TEST(greater, test04) {
    Five num1("102"), num2("103");
    ASSERT_FALSE(num1 > num2);
}


TEST(greater_or_eq, test01) {
    Five num1("10123"), num2("101");
    ASSERT_TRUE(num1 >= num2);
}

TEST(greater_or_eq, test02) {
    Five num1("101");
    ASSERT_TRUE(num1 >= num1);
}

TEST(greater_or_eq, test03) {
    Five num1("0"), num2("1220");
    ASSERT_FALSE(num1 >= num2);
}


TEST(less, test01) {
    Five num1("10123"), num2("223");
    ASSERT_FALSE(num1 < num2);
}

TEST(less, test02) {
    Five num1("123");
    ASSERT_FALSE(num1 < num1);
}

TEST(less, test03) {
    Five num1("10100"), num2("10010");
    ASSERT_FALSE(num1 < num2);
}

TEST(less, test04) {
    Five num1("10"), num2("1220");
    ASSERT_TRUE(num1 < num2);
}


TEST(less_or_eq, test01) {
    Five num1("223"), num2("12");
    ASSERT_FALSE(num1 <= num2);
}

TEST(less_or_eq, test02) {
    Five num1("123");
    ASSERT_TRUE(num1 <= num1);
}

TEST(less_or_eq, test03) {
    Five num1("223"), num2("12");
    ASSERT_FALSE(num1 <= num2);
}

TEST(less_or_eq, test04) {
    Five num1("10"), num2("1220");
    ASSERT_TRUE(num1 <= num2);
}


TEST(add, test01) {
    Five num1("0"), num2("10234");
    ASSERT_TRUE(num1 + num2 == Five("10234"));
}

TEST(add, test02) {
    Five num1("103"), num2("0");
    ASSERT_TRUE(num1 + num2 == Five("103"));
}

TEST(add, test03) {
    Five num1("134"), num2("1");
    ASSERT_TRUE(num1 + num2 == Five("140"));
}

TEST(add, test04) {
    Five num1("1034"), num2("132");
    ASSERT_TRUE(num1 + num2 == Five("1221"));
}

TEST(add, test05) {
    Five num1("4444"), num2("1");
    ASSERT_TRUE(num1 + num2 == Five("10000"));
}

TEST(add_r, test01) {
    Five num1("0"), num2("123");
    num1 += num2;
    ASSERT_TRUE(num1 == num2);
}

TEST(add_r, test02) {
    Five num1("102"), num2("0");
    num1 += num2;
    ASSERT_TRUE(num1 == Five("102"));
}

TEST(add_r, test03) {
    Five num1("102"), num2("102");
    num1 += num2;
    ASSERT_TRUE(num1 == Five("204"));
}

TEST(sub, test01) {
    Five num1("102"), num2("101");
    std::cout << num1 - num2 << std::endl;
    ASSERT_TRUE(num1 - num2 == Five("1"));
}

TEST(sub, test02) {
    Five num1("102"), num2("0");
    ASSERT_TRUE(num1 - num2 == num1);
}

TEST(sub, test03) {
    Five num1("10"), num2("102");
    ASSERT_ANY_THROW(num1 - num2);
}

TEST(sub_r, test01) {
    Five num1("10"), num2("102");
    ASSERT_ANY_THROW(num1 -= num2);
}

TEST(sub_r, test02) {
    Five num1("102"), num2("0");
    num1 -=num2;
    ASSERT_TRUE(num1 == Five("102"));
}

TEST(sub_r,test03) {
    Five num1 ("102"), num2("1");
    num1 -= num2;
    ASSERT_TRUE(num1 == Five("101"));
};

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
