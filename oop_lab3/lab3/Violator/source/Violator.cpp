#include "Violator/Violator.h"

Violator::Violator(std::string name, size_t hp,const Point point) : name_(std::move(name)),
                                                                                   hp_(hp),
                                                                                   point_(const_cast<Point &>(point)) {}

const std::string &Violator::getName() const {
    return name_;
}
std::string Violator::get_cell_type() {
    return "Violator";
}

size_t Violator::getHp() const {
    return hp_;
}

void Violator::setHp(size_t hp) {
    hp_ = hp;
}


Point Violator::getPoint() const {
    return point_;
}

void Violator::setPoint(Point point) {
    point_ = point;
}

void Violator::moveViolator(Plan &plan, Point &newPoint) {

    size_t newX = newPoint.x;
    size_t newY = newPoint.y;
    if (newX >= plan.get_rows() || newY >= plan.get_cols()) {
        throw std::out_of_range("New coordinates are out of bounds");
    }
    if (plan.has_object(newX, newY)) {
        return;
    }
    auto object = plan.get_object_at(point_.x, point_.y);
    plan.deleteObject(const_cast<Point &>(point_));

    point_.x = newX;
    point_.y = newY;
    plan.get_cell(newX, newY).add_object_if_absent(object);
}
