#include "Obstacles/Obstacles.h"

Obstacles::Obstacles(std::string name) : name_(std::move(name)) {}

std::string Obstacles::get_cell_type() {
    return "Obstacles";
}

const std::string & Obstacles::getName() const {
    return name_;
}