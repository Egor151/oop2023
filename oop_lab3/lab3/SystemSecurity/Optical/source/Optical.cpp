#include <utility>
#include <cmath>

#include "Optical/Optical.h"

Optical::Optical(std::string name, size_t radius) : name_(std::move(name)), radius_(radius), isTurnedOn(false) {}

std::string Optical::getName() const {
    return name_;
}

size_t Optical::getRadius() const {
    return radius_;
}

[[nodiscard]] std::string Optical::getType() const {
    return "Optical";
}

std::vector<std::pair<Point, std::string>> Optical::getInfo(Plan &plan, size_t platformX, size_t platformY) {
    std::vector<std::pair<Point, std::string>> ans;
    if (!isTurnedOn) {
        throw std::invalid_argument("Module isn`t included");
    }
    std::vector<std::vector<size_t>> cells;
    for (size_t x = platformX - radius_;
         x <= platformX + radius_ && x < plan.get_rows(); ++x) {
        cells.emplace_back();
        for (size_t y = platformY - radius_;
             y <= platformY + radius_ && y < plan.get_cols(); ++y) {
            cells.back().emplace_back(1);
        }
    }
    for (size_t x = platformX - radius_;
         x <= platformX + radius_ && x < plan.get_rows(); ++x) {
        for (size_t y = platformY - radius_;
             y <= platformY + radius_ && y < plan.get_cols(); ++y) {
            if (plan.get_cell_type(x, y) == "object") {
                ban_cells(x, y, cells);
            }
        }
    }
    for (size_t x = platformX - radius_;
         x <= platformX + radius_ && x < plan.get_rows(); ++x) {
        for (size_t y = platformY - radius_;
             y <= platformY + radius_ && y < plan.get_cols(); ++y) {
            if (cells[x][y] == 1) {
                ans.emplace_back(plan.get_cell_t(x, y));
            }
        }
    }
    return ans;
}

void Optical::ban_cells(size_t x, size_t y, std::vector<std::vector<size_t>> &cells) {
    auto size = static_cast<size_t>(cells.size());
    size_t x_adder = 0;
    size_t y_adder = 0;

    if (y > size / 2) y_adder = 1;
    if (y == size / 2) y_adder = 0;
    if (y < size / 2) y_adder = -1;
    if (x > size / 2) x_adder = 1;
    if (x == size / 2) x_adder = 0;
    if (x < size / 2) x_adder = -1;

    while (x < size && y < size) {
        cells[x][y] = 0;
        x += x_adder;
        y += y_adder;
    }
}

void Optical::turnOn() {
    isTurnedOn = true;
}

void Optical::turnOff() {
    isTurnedOn = false;

}

bool Optical::isTurnedOn1() const {
    return isTurnedOn;
}

Optical::~Optical() = default;