#pragma once

#include <iostream>
#include <cmath>

class Point {
    public:
        double x;
        double y;

        Point();
        Point(double a, double b);
        Point(const Point& other);
        Point(Point&& other);

        

        friend std::ostream& operator<<(std::ostream& os, const Point& p);
        friend std::istream& operator>>(std::istream& is, const Point& p);

        bool operator==(const Point& other) const;
        Point operator= (const Point &other);
        Point operator* (const double &m) const;
        Point operator/ (const double &m) const;
        Point operator+ (const Point &other) const;
        Point operator- (const Point &other) const;
};

double sqrDistance(const Point &p1, const Point &p2);
Point Vector(const Point &p1, const Point &p2);
double Scalar(const Point &p1, const Point &p2);
double sqrModul(const Point &p);