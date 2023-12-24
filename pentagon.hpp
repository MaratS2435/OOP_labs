#include "figure.hpp"
#include <iostream>
#include <memory>
template <class T>
class Pentagon: public Figure{
    public:
    Pentagon(Point<T> A, Point<T> B, Point<T> C, Point<T> D, Point<T> E) : A_(A), B_(B), C_(C), D_(D), E_(E) {}

    Point<double> center() const override {
        double centerX = (A_.x + B_.x + C_.x + D_.x + E_.x) / 5;
        double centerY = (A_.y + B_.y + C_.y + D_.y + E_.y) / 5;
        return Point<T>(centerX, centerY);
    }

    bool operator==(const Pentagon<T>& other) const {
        return (A_ == other.A_ && B_ == other.B_ && C_ == other.C_ && D_ == other.D_ && E_ == other.E_);
    }

    bool operator!=(const Pentagon<T>& other) const {
        return !(*this == other);
    }

    void PrintCoordinates(std::ostream& os) const override {
        os << "Coordinates of Pentagon: A(" << A_.x << "," << A_.y << "), B(" << B_.x << "," << B_.y << "), C(" << C_.x << "," << C_.y << "), D(" << D_.x << "," << D_.y << "), E(" << E_.x << "," << E_.y << ")\n";
    }

    explicit operator double() const noexcept override {
        double area = 0.0;
        area += areaOfTriangle(A_, B_, C_);
        area += areaOfTriangle(A_, C_, D_);
        area += areaOfTriangle(A_, D_, E_);
        return area;
    }

    // Вспомогательная функция для расчета площади треугольника по координатам вершин
    double areaOfTriangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) const {
        return 0.5 * std::abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)));
    }

    std::shared_ptr<Figure> clone() const override {
        return std::make_shared<Pentagon<T>>(A_, B_, C_, D_, E_);
    }

    void ReadCoordinates(std::istream& is) override {
        is >> A_.x >> A_.y >> B_.x >> B_.y >> C_.x >> C_.y >> D_.x >> D_.y >> E_.x >> E_.y;
    }


    private:
        Point<T> A_;
        Point<T> B_;
        Point<T> C_;
        Point<T> D_;
        Point<T> E_;
};