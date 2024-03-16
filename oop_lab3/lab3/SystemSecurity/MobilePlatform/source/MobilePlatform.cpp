#include "MobilePlatform/MobilePlatform.h"

MobilePlatform::MobilePlatform(std::string name, Point point, size_t speed, size_t numberOfModules) : StationaryPlatform(std::move(name),
                                                                                    point, numberOfModules ), speed_(speed) {}

size_t MobilePlatform::getSpeed() const {
    return speed_;
}
const std::string &MobilePlatform::getName() const {
    return name_;
}
std::string MobilePlatform::get_cell_type() {
    return "MobilePlatform";
}
Point MobilePlatform::getPoint() const {
    return point_;
}
void MobilePlatform::moveTo(Plan &plan, size_t newX, size_t newY) {
    if (newX >= plan.get_rows() || newY >= plan.get_cols()) {
        throw std::out_of_range("New coordinates are out of bounds");
    }
    // Проверяем, свободна ли новая клетка
    if (plan.has_object(newX, newY)) {
        throw std::invalid_argument("The cell is already occupied.");
    }
    auto object = plan.get_object_at(point_.x, point_.y);
    // Удаляем объект из текущей позиции в плане
    plan.add_object(const_cast<Point &>(point_), nullptr);

    // Обновляем координаты
    point_.x = newX;
    point_.y = newY;

    // Добавляем объект в новую позицию в плане
    plan.get_cell(newX, newY).add_object_if_absent(object);
}
