#include <utility>
#include <thread>
#include <random>
#include "Armament/Armament.h"

Armament::Armament(std::string name, size_t time, size_t radius, size_t energy, bool energySupply)
        : name_(std::move(name)), time_(time), radius_(radius), energy_(energy), energySupply_(energySupply) {}

[[nodiscard]]const std::string &Armament::getName() const {
    return name_;
}

bool Armament::isEnergySupply() const {
    return energySupply_;
}

size_t Armament::getTime() const {
    return time_;
}

size_t Armament::getRadius() const {
    return radius_;
}

size_t Armament::getEnergy() const {
    return energy_;
}

void Armament::setName(const std::string &name) {
    name_ = name;
}

void Armament::setTime(size_t time) {
    time_ = time;
}

void Armament::setRadius(size_t radius) {
    radius_ = radius;
}

void Armament::setEnergy(size_t energy) {
    energy_ = energy;
}

[[nodiscard]] std::string Armament::getType() const {
    return "Armament";
}

auto Armament::neutralizeTheIntruder(Plan &plan, size_t platformX, size_t platformY,
                                     Violator &violator) -> std::pair<size_t, size_t> {
    if (!energySupply_) {
        throw std::invalid_argument("Module isn`t included");
    }

    size_t armamentRemainingEnergy;
    if (abs((int)platformX - (int)violator.getPoint().x) <= radius_ && abs((int)platformY - (int)violator.getPoint().y) <= radius_ ){
        armamentRemainingEnergy = getEnergy();
        std::uniform_int_distribution<int> distribution(0, 99);
        if (distribution(randomEngine) <= 80) {
            size_t damage = 20;
            violator.setHp(violator.getHp() >= damage ? violator.getHp() - damage : 0);
            if(getEnergy() - 10 >= 0 ) {
                armamentRemainingEnergy = getEnergy() - 10;
            }
        }
    }

    return {violator.getHp(), armamentRemainingEnergy};
}

void Armament::turnOn() {
    energySupply_ = true;
}

void Armament::turnOff() {
    energySupply_ = false;
}

Armament::~Armament() = default;