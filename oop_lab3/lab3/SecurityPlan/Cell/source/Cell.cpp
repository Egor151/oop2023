#include <iostream>
#include <utility>
#include "Cell/Cell.h"
#include <memory>
class Violator;

Cell::Cell() : object_(nullptr), point_(-1,-1) {}

Cell::Cell(std::shared_ptr<Object> object, const Point &point) : object_(std::move(object)),
                                                       point_(point) {}

std::shared_ptr<Object> Cell::get_object() {
    return object_;
}

void Cell::set_object(std::shared_ptr<Object> object) {
    object_ = std::move(object);
}
void Cell::set_point(Point point) {
    point_ = point;
}
bool Cell::has_object() const {
    return object_ != nullptr;
}

std::string Cell::get_cell_type() const {
    return point_.get_string() + ": " + std::string{typeid(*this).name()};
}
std::pair<Point, std::string> Cell::get_info() const {

    return {point_, object_->get_cell_type()};
}
void Cell::add_object_if_absent(std::shared_ptr<Object> object) {
    if (!has_object()) {
        set_object(object);
    } else {
        throw std::invalid_argument("Object already exists");
    }
}
