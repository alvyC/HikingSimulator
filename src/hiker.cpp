#include "hiker.hpp"

Hiker::Hiker(const std::string& name, double speed) : name(name), speed(speed) {}

std::string Hiker::getName() const {
    return name;
}

double Hiker::getSpeed() const {
    return speed;
}
