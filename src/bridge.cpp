#include "bridge.hpp"

Bridge::Bridge(int length) : 
	length(length)
	{}

int Bridge::getLength() const {
    return length;
}

const std::vector<Hiker>& Bridge::getHikers() const {
    return hikers;
}

void Bridge::addHiker(const Hiker& hiker) {
    hikers.push_back(hiker);
}

double Bridge::timeToCross(const Hiker& hiker1, const Hiker& hiker2) const {
    double slower_speed = std::min(hiker1.getSpeed(), hiker2.getSpeed());
    return length / slower_speed;
}
