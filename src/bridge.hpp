#ifndef BRIDGE_H
#define BRIDGE_H

#include <vector>
#include <string>

#include "hiker.hpp"

class Bridge {
public:
    Bridge(int length);

    int getLength() const;
    const std::vector<Hiker>& getHikers() const;
    void addHiker(const Hiker& hiker);
    double timeToCross(const Hiker& hiker1, const Hiker& hiker2) const;

private:
    int length; // in feet
    std::vector<Hiker> hikers;
};

#endif // BRIDGE_H
