#include <utility>

#include "StationaryPlatform/StationaryPlatform.h"

StationaryPlatform::StationaryPlatform(std::string name, const Point &point, size_t numberOfModules)
        : name_(std::move(name)),
          point_(const_cast<Point &>(point)),
          numberOfModules_(numberOfModules),
          modules_(0) {}

const std::string &StationaryPlatform::getName() const {
    return name_;
}
std::string StationaryPlatform::get_cell_type() {
    return "StationaryPlatform";
}

size_t StationaryPlatform::getNumberOfModules() const {
    return numberOfModules_;
}

void StationaryPlatform::setNumberOfModules(size_t numberOfModules) {
    numberOfModules_ = numberOfModules;
}
[[nodiscard]] Point StationaryPlatform::getPoint() {
    return  point_;
};

void StationaryPlatform::installModule(std::shared_ptr<Module> module) {
    if (modules_.size() >= numberOfModules_) {
        throw std::invalid_argument("Index is out of range");
    }
    modules_.push_back(std::move(module));
}

void StationaryPlatform::removeModule(size_t index) {
    if (index >= numberOfModules_) {
        throw std::out_of_range("Index is out of range");
    }
    modules_.erase(modules_.begin() + index);
}

StationaryPlatform::~StationaryPlatform() {
}

const std::vector<std::shared_ptr<Module>>  StationaryPlatform::getModules() const  {
    return modules_;
}

