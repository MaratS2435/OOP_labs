#include "figure.hpp"
#include <iostream>
#include <cmath>
#include <memory>
template <class T>
class Trapezoid : public Figure {
public:
    Trapezoid(Point<T> A, Point<T> B, Point<T> C, Point<T> D) : A_(A), B_(B), C_(C), D_(D) {}

    bool operator==(const Trapezoid<T>& other) const {
        return (A_ == other.A_ && B_ == other.B_ && C_ == other.C_ && D_ == other.D_);
    }

    bool operator!=(const Trapezoid<T>& other) const {
        return !(*this == other);
    }

    Point<double> center() const override {
        double centerX = (A_.x + B_.x + C_.x + D_.x) / 4.0;
        double centerY = (A_.y + B_.y + C_.y + D_.y) / 4.0;
        return Point<T>(centerX, centerY);
    }

    void PrintCoordinates(std::ostream& os) const override {
        os << "Coordinates of Trapezoid: A(" << A_.x << "," << A_.y << "), B(" << B_.x << "," << B_.y << "), C(" << C_.x << "," << C_.y << "), D(" << D_.x << "," << D_.y << ")\n";
    }

    explicit operator double() const noexcept override {
        double base1 = std::sqrt((A_.x - B_.x) * (A_.x - B_.x) + (A_.y - B_.y) * (A_.y - B_.y));
        double base2 = std::sqrt((C_.x - D_.x) * (C_.x - D_.x) + (C_.y - D_.y) * (C_.y - D_.y));
        double height = std::abs(A_.y - C_.y);
        return (base1 + base2) * height / 2.0;
    }

    std::shared_ptr<Figure> clone() const override {
        return std::make_shared<Trapezoid<T>>(A_, B_, C_, D_);
    }

    void ReadCoordinates(std::istream& is) override {
        is >> A_.x >> A_.y >> B_.x >> B_.y >> C_.x >> C_.y >> D_.x >> D_.y;
    }

private:
    Point<T> A_;
    Point<T> B_;
    Point<T> C_;
    Point<T> D_;
};
