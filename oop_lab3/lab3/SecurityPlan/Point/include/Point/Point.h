#ifndef LAB3_POINT_H
#define LAB3_POINT_H
#include <cstddef>
#include <string>
class Point {
public:
    size_t x;
    size_t y;

    Point() = default;

    Point(size_t xCoord, size_t yCoord) : x(xCoord), y(yCoord) {}

    bool operator==(const Point &other) const {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(const Point &other) const {
        return !(*this == other);
    }

    [[nodiscard]] std::string get_string() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

#endif
