#include "Incubator.hpp"
#include <iostream>

Incubator::Incubator(const std::string& modelName, int eggCapacity, double maxSystemError) 
    : modelName(modelName), eggCapacity(eggCapacity), mainControl(maxSystemError) {}

Incubator::~Incubator() {
    std::cout << "[Деструктор] Корпус инкубатора \"" << modelName << "\" полностью демонтирован.\n";
}

void Incubator::installSensor(Sensor* sensor) {
    mainControl.connectSensor(sensor);
}

void Incubator::powerOn() const {
    std::cout << "--- Запуск Системы Инкубации ---\n";
    std::cout << "Модель: " << modelName << ", Вместимость лотка: " << eggCapacity << " яиц.\n";
    mainControl.checkSystemStatus();
    std::cout << "--------------------------------\n";
}
