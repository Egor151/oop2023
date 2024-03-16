#include <iostream>
#include <utility>
#include "Plan/Plan.h"

Plan::Plan() = default;

Plan::Plan(size_t rows, size_t cols) : matrix_(rows, std::vector<Cell>(cols, Cell())), entrance_(0,cols-1), exit_(rows-1, 0) {
    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < cols; j++) {
            matrix_[i][j].set_point(Point(i, j));
        }
    }
}

size_t Plan::get_rows() const {
    return matrix_.size();
}

[[nodiscard]] size_t Plan::get_cols() const {
    if (matrix_.empty()) {
        return 0;
    }
    return matrix_[0].size();
}

//void Plan::set_object(Point  &point, std::string &type) {
//    std::shared_ptr<Object> object;
//
//}

std::string Plan::get_cell_type(size_t x, size_t y) const {
    return matrix_[x][y].get_cell_type();
}
std::pair<Point, std::string> Plan::get_cell_t(size_t x, size_t y) const {
    return matrix_[x][y].get_info();
}
void Plan::add_object(const Point &point, std::shared_ptr<Object> object) {
    size_t x = point.x;
    size_t y = point.y;

    if (x >= 0 && x < get_rows() && y >= 0 && y < get_cols()) {
        matrix_[x][y].add_object_if_absent((object));
    } else {
        throw std::invalid_argument("Object already exists");
    }
}

Cell &Plan::get_cell(size_t x, size_t y) {
    return matrix_[x][y];
}

bool Plan::has_object(size_t x, size_t y) const {
    return matrix_[x][y].has_object();
}
void Plan::deleteObject(Point &point) {
    if(matrix_[point.x][point.y].has_object()) {
        matrix_[point.x][point.y].set_object(nullptr);
    }
}

std::shared_ptr<Object>  Plan::get_object_at(size_t x, size_t y) {
    if (x >= get_rows() || y >= get_cols()) {
        throw std::out_of_range("Coordinates are out of bounds");
    }
    return matrix_[x][y].get_object();
}

void Plan::set_entrance(const Point &entrance) {
    entrance_ = entrance;
}

Point Plan::get_entrance() const {
    return entrance_;
}

void Plan::set_exit(const Point &exit) {
    exit_ = exit;
}

Point Plan::get_exit() const {
    return exit_;
}
