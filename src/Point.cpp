#include "Point.h"

Point::Point(): x(0), y(0) {}

Point::Point(double a, double b): x(a), y(b) {}

Point::Point(const Point &other) {
    x = other.x;
    y = other.y;
}

Point::Point(Point &&other) {
    x = other.x;
    y = other.y;
}

bool Point::operator== (const Point &other) const {
    return (x == other.x && y == other.y);
}

Point Point::operator* (const double &m) const {
    Point res;
    res.x = x * m;
    res.y = y * m;
    return res;
}

Point Point::operator/ (const double &m) const {
    Point res;
    res.x = x / m;
    res.y = y / m;
    return res;
}

Point Point::operator+ (const Point &other) const{
    Point res;
    res.x = x + other.x;
    res.y = y + other.y;
    return res;
}

Point Point::operator- (const Point &other) const {
    Point res;
    res.x = x - other.x;
    res.y = y - other.y;
    return res;
}

Point Point::operator= (const Point &other) {
    x = other.x;
    y = other.y;
    return *this;
};

std::ostream& operator<< (std::ostream& os, const Point& p) {
    os << '(' << p.x << "; " << p.y << ')';
    return os;
}

std::istream& operator>> (std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

double sqrDistance(const Point &p1, const Point &p2) {
    double i, j;
    i = (p1.x - p2.x) * (p1.x - p2.x);
    j = (p1.y - p2.y) * (p1.y - p2.y);

    return i + j;
}

Point Vector(const Point &p1, const Point &p2) {
    Point res;
    res.x = p2.x - p1.x;
    res.y = p2.y - p1.y;
    
    return res;
}

double Scalar(const Point &p1, const Point &p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

double sqrModul(const Point &p) {
    return sqrDistance({0, 0}, p);
}
