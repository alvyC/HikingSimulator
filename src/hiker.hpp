#ifndef HIKER_H
#define HIKER_H

#include <string>

class Hiker {
public:
    Hiker(const std::string& name, double speed);

    std::string getName() const;
    double getSpeed() const;

private:
    std::string name;
    double speed; // Speed in feet per minute
};

#endif // HIKER_H
