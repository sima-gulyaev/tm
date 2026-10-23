#include "Sensor.hpp"
#include <iostream>

Sensor::Sensor(const std::string& type, double errorMargin) 
    : type(type), errorMargin(errorMargin) {}

Sensor::~Sensor() {
    std::cout << "[Деструктор] Датчик \"" << type << "\" отключен от питания и утилизирован.\n";
}

std::string Sensor::getType() const { return type; }
double Sensor::getErrorMargin() const { return errorMargin; }
