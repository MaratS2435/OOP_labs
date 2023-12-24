#include "figure.hpp"
#include <iostream>
#include <cmath>
#include <memory>
template <class T>
class Rhombus: public Figure{
    public:
    Rhombus(Point<T> A, Point<T> B, Point<T> C, Point<T> D) : A_(A), B_(B), C_(C), D_(D) {}

    Point<double> center() const override {
        double centerX = (A_.x + B_.x + C_.x + D_.x) / 4.0;
        double centerY = (A_.y + B_.y + C_.y + D_.y) / 4.0;
        return Point<T>(centerX, centerY);
    }

    void PrintCoordinates(std::ostream& os) const override{
        os << "Coordinates of Rhombus: A(" << A_.x << "," << A_.y << "), B(" << B_.x << "," << B_.y << "), C(" << C_.x << "," << C_.y << "), D(" << D_.x << "," << D_.y << ")\n";
    }

    explicit operator double() const noexcept override {
        double diagonal1 = std::sqrt((A_.x - C_.x) * (A_.x - C_.x) + (A_.y - C_.y) * (A_.y - C_.y));
        double diagonal2 = std::sqrt((B_.x - D_.x) * (B_.x - D_.x) + (B_.y - D_.y) * (B_.y - D_.y));
        return (diagonal1 * diagonal2) / 2.0;
    }

    bool operator==(const Rhombus<T>& other) const {
        return (A_ == other.A_ && B_ == other.B_ && C_ == other.C_ && D_ == other.D_);
    }
    bool operator!=(const Rhombus<T>& other) const {
        return !(*this == other);
    }

    std::shared_ptr<Figure> clone() const override {
        return std::make_shared<Rhombus<T>>(A_, B_, C_, D_);
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
