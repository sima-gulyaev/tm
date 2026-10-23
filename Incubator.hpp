#pragma once
#include <string>
#include "ControlUnit.hpp"

class Incubator {
private:
    std::string modelName;
    int eggCapacity;
    ControlUnit mainControl; // Композиция: блок управления — неотъемлемая часть инкубатора

public:
    Incubator(const std::string& modelName, int eggCapacity, double maxSystemError);
    ~Incubator();

    void installSensor(Sensor* sensor);
    void powerOn() const;
};
