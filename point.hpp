template <typename T>
struct Point {
    T x;
    T y;

    Point(T x, T y) : x(x), y(y) {}

    bool operator==(const Point<T>& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point<T>& other) const {
        return !(*this == other);
    }
};