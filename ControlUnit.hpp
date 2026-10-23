#pragma once
#include "Sensor.hpp"

class ControlUnit {
private:
    Sensor* connectedSensor; // Агрегация: указатель на внешний датчик
    double maxAllowedError;  // Максимально допустимая погрешность системы

public:
    ControlUnit();
    ControlUnit(double maxAllowedError);
    ~ControlUnit();

    void connectSensor(Sensor* sensor);
    void disconnectSensor();
    void checkSystemStatus() const;

    double getMaxAllowedError() const;
};
