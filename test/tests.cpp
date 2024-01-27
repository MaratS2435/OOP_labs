#include <iostream>
#include "Figure.h"
#include "ArrFigure.h"
#include "Rhomb.h"
#include "Pentagon.h"
#include "Trapezoid.h"

#include <gtest/gtest.h>

bool constructortest() {
    Point p1 {1, 3}, p2 {3, 5}, p3 {5, 3}, p4 {3, 1};
    Figure<double> f1, f2;
    double d {5};

    Rhomb<int> r1(p1, p2, p3, p4);
    Rhomb<int> r2({1, 3}, {3, 5}, {5, 3}, {3, 1}); 
    Trapezoid<int> t1({2, 1}, {3, 4}, {6, 4}, {7, 1});
    Trapezoid<int> t2({9, 4}, {14, 4}, {13, 1}, {10, 1}); //Перенесённый и перевёрнутый
    Pentagon<double> pen1({1, 0}, {0.309016994375, 0.951056516295}, {-0.809016994375, 0.587785252292}, {-0.809016994375, -0.587785252292}, {0.309016994375, -0.951056516295});
    std::cout << (f1 == f2) << ' ' << (r1 == r2) << ' ' << (t1 == t2) << "\n";
    return (f1 == f2) && (r1 == r2) && (t1 == t2);
};

TEST(constructor, test_01) {
    ASSERT_TRUE(constructortest());
}

TEST(create, test_01) {
    EXPECT_THROW(Rhomb<int> ({2, 3}, {3, 5}, {5, 3}, {3, 1}), std::invalid_argument);
}

TEST(create, test_02) {
    EXPECT_ANY_THROW(Pentagon<double> ({0, 0}, {0.309016994375, 0.951056516295}, {-0.809016994375, 0.587785252292}, {-0.809016994375, -0.587785252292}, {0.309016994375, -0.951056516295}));
}

TEST(create, test_03) {
    EXPECT_ANY_THROW(Trapezoid<int> ({10, 4}, {14, 4}, {13, 0}, {10, 1}));
}

TEST(copy, test_01) {
    Rhomb<int> r1({1, 3}, {3, 5}, {5, 3}, {3, 1}), r2;
    r2 = r1;
    ASSERT_TRUE(r1 == r2);
}

TEST(PointEq, test_01) {
    Point p1 {1, 0}, p2 {1, 0};
    ASSERT_TRUE(p1 == p2);
}

TEST(PointEq, test_02) {
    Point p1 {1, 0}, p2 {3, 2};
    ASSERT_FALSE(p1 == p2);
}

TEST(PointOper, mult) {
    Point p1 {1, 2}, p2{2, 4};
    p1 = p1 * 2;
    ASSERT_TRUE(p1 == p2);
}

TEST(PointOper, copy) {
    Point<int> p1{1, 2}, p2;
    p2 = p1;
    ASSERT_TRUE(p1 == p2);
}

TEST(PointOper, sub) {
    Point p1 {2, 4}, p2 {1, 2};
    p1 = p1 / 2;
    ASSERT_TRUE(p1 == p2);
}

TEST(PointOper, plus) {
    Point p1{1, 0}, p2{0, 1}, p3{1, 1};
    p1 = p1 + p2;
    ASSERT_TRUE(p1 == p3); 
}

TEST(PointFunc, Vector) {
    Point p1{1, 2}, p2{3, 5}, p3{2, 3};
    ASSERT_TRUE(p3 == Vector(p1, p2));
}

TEST(PointFunc, Scalar) {
    Point p1{1, 0}, p2{0, 1};
    ASSERT_TRUE(Scalar(p1, p2) == 0);
}

TEST(PointFunc, Distance) {
    Point p1{0, 0}, p2{3, 4};
    ASSERT_TRUE(sqrDistance(p1, p2) == 25.0);
}

TEST(Center, rhomb) {
    Rhomb<int> r({1, 3}, {3, 5}, {5, 3}, {3, 1});
    Point p {3, 3};
    std::cout << r.center() << std::endl;
    ASSERT_TRUE(r.center() == p);
}

TEST(Center, trapezoid) {
    Trapezoid<double> t({2, 1}, {3, 4}, {6, 4}, {7, 1});
    Point p {4.5, 2.5};
    ASSERT_TRUE(t.center() == p);
}

TEST(Center, pentagon) {
    Pentagon<double> p({1, 0}, {0.309016994375, 0.951056516295}, {-0.809016994375, 0.587785252292}, {-0.809016994375, -0.587785252292}, {0.309016994375, -0.951056516295});
    double e {0.00001};

    ASSERT_TRUE(p.center().x <= e && p.center().y <= e);
}

TEST(FigureArray, AddRem) {
    Rhomb<double> r({1, 3}, {3, 5}, {5, 3}, {3, 1});
    Trapezoid<double> t1({2, 1}, {3, 4}, {6, 4}, {7, 1});
    Trapezoid<double> t2({9, 4}, {14, 4}, {13, 1}, {10, 1}); //Перенесённый и перевёрнутый
    Pentagon<double> p({1, 0}, {0.309016994375, 0.951056516295}, {-0.809016994375, 0.587785252292}, {-0.809016994375, -0.587785252292}, {0.309016994375, -0.951056516295});
    ArrFigure<double> a;
    a.Push(&r);
    a.Push(&t1);
    a.Push(&t2);
    a.Push(&p);
    std::cout << a << std::endl;
    EXPECT_TRUE(a.getsize() == 4);

    a.remove(0);
    EXPECT_TRUE(a.getsize() == 3);
}

TEST(FigureArray, SumArea) {
    Rhomb<double> r({1, 3}, {3, 5}, {5, 3}, {3, 1});
    Trapezoid<double> t1({2, 1}, {3, 4}, {6, 4}, {7, 1});
    Trapezoid<double> t2({9, 4}, {14, 4}, {13, 1}, {10, 1}); //Перенесённый и перевёрнутый
    ArrFigure<double> a;
    a.Push(&r);
    a.Push(&t1);
    a.Push(&t2);
    double sum = a.SumArea();
    ASSERT_EQ(sum, 32.0);
}

TEST(FigureArray, AllCenters) {
    Rhomb<int> r({1, 3}, {3, 5}, {5, 3}, {3, 1});
    Trapezoid<int> t1({2, 1}, {3, 4}, {6, 4}, {7, 1});
    Trapezoid<int> t2({9, 4}, {14, 4}, {13, 1}, {10, 1});
    ArrFigure<int> a;
    a.Push(&r);
    a.Push(&t1);
    a.Push(&t2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
