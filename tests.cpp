#include <gtest/gtest.h>
#include "trapezoid.hpp"  // Подключаем заголовочный файл с классом Trapezoid
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "array.hpp"

TEST(TrapezoidTest, AreaCalculation) {
    // Создаем объект Трапеции
    Point<double> A(0.0, 0.0);
    Point<double> B(4.0, 0.0);
    Point<double> C(0.0, 3.0);
    Point<double> D(6.0, 3.0);
    std::shared_ptr<Trapezoid<double>> trapezoid = std::make_shared<Trapezoid<double>>(A, B, C, D);

    // Проверяем правильность расчета площади
    ASSERT_DOUBLE_EQ(15.0, trapezoid->operator double());
}

TEST(TrapezoidTest, CenterCalculation) {
    // Создаем объект Трапеции
    Point<double> A(0.0, 0.0);
    Point<double> B(4.0, 0.0);
    Point<double> C(0.0, 3.0);
    Point<double> D(6.0, 3.0);
    std::shared_ptr<Trapezoid<double>> trapezoid = std::make_shared<Trapezoid<double>>(A, B, C, D);

    // Проверяем правильность расчета геометрического центра
    ASSERT_EQ(Point<double>(2.5, 1.5), trapezoid->center());
}

TEST(TrapezoidTest, TotalAreaCalculation) {
    // Создаем массив фигур и добавляем Трапецию
    Array<Figure> figuresArray(1);
    Point<double> A(0.0, 0.0);
    Point<double> B(4.0, 0.0);
    Point<double> C(0.0, 3.0);
    Point<double> D(6.0, 3.0);
    std::shared_ptr<Trapezoid<double>> trapezoid = std::make_shared<Trapezoid<double>>(A, B, C, D);
    figuresArray.add(trapezoid, 0);

    // Проверяем правильность расчета общей площади
    ASSERT_DOUBLE_EQ(15.0, figuresArray.totalArea());
}

TEST(RhombusTest, AreaCalculation) {
    // Создаем объект Ромба
    Point<double> A(2.0, 5.0);
    Point<double> B(6.0, 5.0);
    Point<double> C(4.0, 9.0);
    Point<double> D(0.0, 9.0);
    std::shared_ptr<Rhombus<double>> rhombus = std::make_shared<Rhombus<double>>(A, B, C, D);

    // Проверяем правильность расчета площади
    ASSERT_NEAR(16.1245, rhombus->operator double(), 10e-5);
}

TEST(RhombusTest, CenterCalculation) {
    // Создаем объект Ромба
    Point<double> A(2.0, 5.0);
    Point<double> B(6.0, 5.0);
    Point<double> C(4.0, 9.0);
    Point<double> D(0.0, 9.0);
    std::shared_ptr<Rhombus<double>> rhombus = std::make_shared<Rhombus<double>>(A, B, C, D);

    // Проверяем правильность расчета геометрического центра
    ASSERT_EQ(Point<double>(3.0, 7.0), rhombus->center());
}

TEST(PentagonTest, AreaCalculation) {
    // Создаем объект 5-угольника
    Point<double> A(8.0, 0.0);
    Point<double> B(12.0, 2.0);
    Point<double> C(10.0, 6.0);
    Point<double> D(6.0, 6.0);
    Point<double> E(4.0, 2.0);
    std::shared_ptr<Pentagon<double>> pentagon = std::make_shared<Pentagon<double>>(A, B, C, D, E);

    // Проверяем правильность расчета площади
    ASSERT_DOUBLE_EQ(32.0, pentagon->operator double());
}

TEST(PentagonTest, CenterCalculation) {
    // Создаем объект 5-угольника
    Point<double> A(8.0, 0.0);
    Point<double> B(12.0, 2.0);
    Point<double> C(10.0, 6.0);
    Point<double> D(6.0, 6.0);
    Point<double> E(4.0, 2.0);
    std::shared_ptr<Pentagon<double>> pentagon = std::make_shared<Pentagon<double>>(A, B, C, D, E);

    // Проверяем правильность расчета геометрического центра
    ASSERT_EQ(Point<double>(8.0, 3.2), pentagon->center());
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

