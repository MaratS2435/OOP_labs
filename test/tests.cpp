#include <gtest/gtest.h>
#include "Trapezoid.hpp"
#include "Rhombus.hpp"
#include "Pentagon.hpp"
#include "List.hpp"

const double EPS = 0.0001;

TEST(trapezoid_center, test_01){
    Trapezoid<int> trap{Point{2, 3}, Point{5, 3}, Point{0, 0}, Point{7, 0}};
    ASSERT_EQ(trap.getCenter(), Point<int>(3.5, 1.5));
}

TEST(trapezoid_center, test_02){
    Trapezoid<int> trap{Point{0, 13}, Point{3, 13}, Point{-2, 10}, Point{5, 10}};
    ASSERT_EQ(trap.getCenter(), Point<int>(1.5, 11.5));
}

TEST(trapezoid_center, test_03){
    Trapezoid<int> trap{Point{1, 4}, Point{6, 4}, Point{-1, -1}, Point{8, -1}};
    ASSERT_EQ(trap.getCenter(), Point<int>(3.5, 1.5));
}

TEST(trapezoid_area, test_01){
    Trapezoid<int> trap{Point{2, 3}, Point{5, 3}, Point{0, 0}, Point{7, 0}};
    ASSERT_EQ(double(trap), 15);
}

TEST(trapezoid_area, test_02){
    Trapezoid<int> trap{Point{0, 13}, Point{3, 13}, Point{-2, 10}, Point{5, 10}};
    ASSERT_EQ(double(trap), 15);
}

TEST(rhombus_center, test_01){
    Rhombus<int> romb{Point{4, 3}, Point{7, 0}, Point{4, -3}, Point{1, 0}};
    ASSERT_EQ(romb.getCenter(), Point(4, 0));
}

TEST(rhombus_center, test_02){
    Rhombus<int> romb{Point{4, 4}, Point{8, 0}, Point{4, -4}, Point{0, 0}};
    ASSERT_EQ(romb.getCenter(), Point(4, 0));
}

TEST(rhombus_center, test_03){
    Rhombus<double> romb{Point<double>{-1.5, 100}, Point<double>{-24.1, 95}, Point<double>{-1.5, 90}, Point<double>{21.1, 95}};
    ASSERT_EQ(romb.getCenter(), Point<double>(-1.5, 95));
}

TEST(rhombus_area, test_01){
    Rhombus<int> romb{Point{4, 4}, Point{8, 0}, Point{4, -4}, Point{0, 0}};
    ASSERT_EQ(double(romb), 32);
}

TEST(rhombus_area, test_02){
    Rhombus<int> romb{Point{4, 3}, Point{7, 0}, Point{4, -3}, Point{1, 0}};
    ASSERT_EQ(double(romb), 18);
}

TEST(pentagon_center, test_01){
    Pentagon<double> pent{Point<double>{1, 0}, Point<double>{0.3090, 0.9511}, Point<double>{-0.8090, 0.5878}, Point<double>{-0.8090, -0.5878}, Point<double>{0.3090, -0.9511}};
    Point<double> cent = pent.getCenter();
    ASSERT_TRUE((fabs(cent.getX() - 1) < EPS) and (fabs(cent.getY() + 1) < EPS));
}

TEST(pentagon_area, test_01){
    Pentagon<double> pent{Point<double>{1, 0}, Point<double>{0.3090, 0.9511}, Point<double>{-0.8090, 0.5878}, Point<double>{-0.8090, -0.5878}, Point<double>{0.3090, -0.9511}};
    double s = double(pent);
    ASSERT_TRUE(s - 2.37784 < EPS);
}

TEST(array_get_total_area, test01) {
    Trapezoid<double> trap{Point<double>{0, 13}, Point<double>{3, 13}, Point<double>{-2, 10}, Point<double>{5, 10}};
    Rhombus<double> romb{Point<double>{4, 3}, Point<double>{7, 0}, Point<double>{4, -3}, Point<double>{1, 0}};
    Pentagon<double> pent{Point<double>{1, 0}, Point<double>{0.3090, 0.9511}, Point<double>{-0.8090, 0.5878}, Point<double>{-0.8090, -0.5878}, Point<double>{0.3090, -0.9511}};
    ListFigure<std::shared_ptr<Figure<double>>, double> l = {
        std::make_shared<Trapezoid<double>>(trap),
        std::make_shared<Rhombus<double>>(romb),
        std::make_shared<Pentagon<double>>(pent)
    };
    ASSERT_TRUE((double(l) - ((double) trap + (double) romb + (double) pent)) <= EPS);
}

TEST(array_get_total_area, test02) {
    Rhombus<int> romb1{Point{4, 3}, Point{7, 0}, Point{4, -3}, Point{1, 0}};
    Rhombus<int> romb2{Point{4, 3}, Point{7, 0}, Point{4, -3}, Point{1, 0}};
    Rhombus<int> romb3{Point{4, 4}, Point{8, 0}, Point{4, -4}, Point{0, 0}};
    ListFigure<std::shared_ptr<Figure<int>>, int> a = {
        std::make_shared<Rhombus<int>>(romb1),
        std::make_shared<Rhombus<int>>(romb2),
        std::make_shared<Rhombus<int>>(romb3)
    };
    ASSERT_TRUE((double(a) - ((double) romb1 + (double) romb2 + (double) romb3)) <= EPS);
}

TEST(array_remove, test01) {
    Trapezoid<double> trap{Point<double>{0, 13}, Point<double>{3, 13}, Point<double>{-2, 10}, Point<double>{5, 10}};
    Rhombus<double> romb{Point<double>{4, 3}, Point<double>{7, 0}, Point<double>{4, -3}, Point<double>{1, 0}};
    Pentagon<double> pent{Point<double>{1, 0}, Point<double>{0.3090, 0.9511}, Point<double>{-0.8090, 0.5878}, Point<double>{-0.8090, -0.5878}, Point<double>{0.3090, -0.9511}};
    ListFigure<std::shared_ptr<Figure<double>>, double> l = {
        std::make_shared<Trapezoid<double>>(trap),
        std::make_shared<Rhombus<double>>(romb),
        std::make_shared<Pentagon<double>>(pent)
    };
    l.deleteFigure(0);
    ASSERT_TRUE((double(l) - ((double) romb + (double) pent)) <= EPS);
}

TEST(array_remove, test02) {
    Trapezoid<double> trap{Point<double>{0, 13}, Point<double>{3, 13}, Point<double>{-2, 10}, Point<double>{5, 10}};
    Rhombus<double> romb{Point<double>{4, 3}, Point<double>{7, 0}, Point<double>{4, -3}, Point<double>{1, 0}};
    Pentagon<double> pent{Point<double>{1, 0}, Point<double>{0.3090, 0.9511}, Point<double>{-0.8090, 0.5878}, Point<double>{-0.8090, -0.5878}, Point<double>{0.3090, -0.9511}};
    ListFigure<std::shared_ptr<Figure<double>>, double> l = {
        std::make_shared<Trapezoid<double>>(trap),
        std::make_shared<Rhombus<double>>(romb),
        std::make_shared<Pentagon<double>>(pent)
    };
    l.deleteFigure(0);
    l.deleteFigure(0);
    ASSERT_TRUE((double(l) - (double) pent) <= EPS);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}