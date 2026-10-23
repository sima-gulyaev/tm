#pragma once
#include <string>

class Sensor {
private:
    std::string type;
    double errorMargin; // Погрешность датчика в градусах

public:
    Sensor(const std::string& type, double errorMargin);
    ~Sensor();

    std::string getType() const;
    double getErrorMargin() const;
};
