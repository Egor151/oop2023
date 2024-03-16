#include <utility>

#include "Xray/Xray.h"

Xray::Xray(std::string name, size_t radius) : name_(std::move(name)), radius_(radius), isTurnedOn(false) {}

std::string Xray::getName() const {
    return name_;
}

size_t Xray::getRadius() const {
    return radius_;
}

[[nodiscard]] std::string Xray::getType() const {
    return "Xray";
}

std::vector<std::pair<Point, std::string>> Xray::getInfo(Plan &plan, size_t platformX, size_t platformY) {
    std::vector<std::pair<Point, std::string>> ans;
    if (!isTurnedOn) {
        throw std::invalid_argument("Module is not included");
    }
    for (size_t x = platformX - radius_;
         x <= platformX + radius_ && x < plan.get_rows(); ++x) {
        for (size_t y = platformY - radius_;
             y <= platformY + radius_ && y < plan.get_cols(); ++y) {
            ans.emplace_back(plan.get_cell_t(x, y));
        }
    }

    return ans;

}

void Xray::turnOn() {
    isTurnedOn = true;
}

void Xray::turnOff() {
    isTurnedOn = false;
}

bool Xray::isTurnedOn1() const {
    return isTurnedOn;
}

Xray::~Xray() = default;