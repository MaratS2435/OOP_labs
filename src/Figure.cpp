#include "Figure.h"

Figure::Figure(): _size(0), Pts{nullptr}, tag('f') {}

Figure::Figure(int n, char t = 'f') {
    tag = t;
    _size = n;
    Pts = new Point [_size];
}


bool Figure::isThisFigure() {
    return true;
}

std::string Figure::name() const {
    return "Figure";
}

std::ostream& operator<< (std::ostream& os, const Figure& f) {
    for (int i = 0; i < f._size; ++i) {
        os << '(' << f.Pts[i].x << ';' << f.Pts[i].y << ") \n";
    }
    return os;
}

std::istream& operator>> (std::istream& is, Figure& f) {
    for (int i = 0; i < f._size; ++i) {
        is >> f.Pts[i].x >> f.Pts[i].y;
    }
    if (f.isThisFigure()) {
        return is;
    }
    throw std::invalid_argument("Incorrect figure");
}

Figure::~Figure() noexcept{
    delete [] Pts;
    _size = 0;
    Pts = nullptr;
}

Figure::operator double() const {
    return 0;
}

Point Figure::center() const{
    Point p(0, 0);
    for(int i = 0; i < _size; ++i) {
        p = p + Pts[i];
    }
    p = p / _size;
    return p;
}

bool Figure::operator== (const Figure &other) const {
    if (other.tag != tag || double(*this) != double(other)) return false;
    
    return true;
}

Figure& Figure::operator= (const Figure &other) {
    if (other.tag == tag) {
        delete[] Pts;
        _size = other._size;
        Pts = new Point [_size];
        for (int i = 0; i < _size; ++i) {
            Pts[i] = other.Pts[i];
        }
    } else {
        throw std::underflow_error("Different figures");
    }

    return *this;
}

Figure& Figure::operator= (Figure &&other) {
    if (tag != other.tag) {
        throw std::underflow_error("Different figures");
    }
    if (*this != other) {
        _size = other._size;
        delete [] Pts;
        Pts = other.Pts;
        other.Pts = nullptr;
    }
    
    return *this;
}

