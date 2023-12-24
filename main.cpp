#include <iostream>
#include "trapezoid.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "array.hpp"

int main() {
    Array<Figure> figuresArray(3); // Создаем массив для хранения фигур

    // Создаем и добавляем Трапецию
    Point<double> A(0.0, 0.0);
    Point<double> B(4.0, 0.0);
    Point<double> C(0.0, 3.0);
    Point<double> D(6.0, 3.0);
    std::shared_ptr<Trapezoid<double>> trapezoid = std::make_shared<Trapezoid<double>>(A, B, C, D);
    figuresArray.add(trapezoid, 0);

    // Создаем и добавляем Ромб
    Point<double> E(2.0, 5.0);
    Point<double> F(6.0, 5.0);
    Point<double> G(4.0, 9.0);
    Point<double> H(0.0, 9.0);
    std::shared_ptr<Rhombus<double>> rhombus = std::make_shared<Rhombus<double>>(E, F, G, H);
    figuresArray.add(rhombus, 1);

    // Создаем и добавляем 5-угольник
    Point<double> I(8.0, 0.0);
    Point<double> J(12.0, 2.0);
    Point<double> K(10.0, 6.0);
    Point<double> L(6.0, 6.0);
    Point<double> M(4.0, 2.0);
    std::shared_ptr<Pentagon<double>> pentagon = std::make_shared<Pentagon<double>>(I, J, K, L, M);
    figuresArray.add(pentagon, 2);

    // Операции с фигурами
    for (size_t i = 0; i < figuresArray.size(); ++i) {
        std::shared_ptr<Figure> figure = figuresArray.get(i);
        if (figure) {
            Point<double> center = figure->center();
            std::cout << *figure;
            std::cout << "Center: (" << center.x << ", " << center.y << ")\n";
            std::cout << "Area: " << figure->operator double() << "\n";
        }
    }

    std::cout << "Total Area: " << figuresArray.totalArea() << "\n";

    return 0;
}
