#include "ControlUnit.hpp"
#include <iostream>

ControlUnit::ControlUnit() : connectedSensor(nullptr), maxAllowedError(0.5) {}
ControlUnit::ControlUnit(double maxAllowedError) : connectedSensor(nullptr), maxAllowedError(maxAllowedError) {}

ControlUnit::~ControlUnit() {
    std::cout << "[Деструктор] Блок управления (лимит погрешности: " << maxAllowedError << "°C) демонтирован.\n";
    // Обратите внимание: мы НЕ удаляем connectedSensor, так как это агрегация!
}

void ControlUnit::connectSensor(Sensor* sensor) {
    if (!sensor) return;

    // Проверка правила: погрешность датчика не должна превышать лимит системы
    if (sensor->getErrorMargin() > maxAllowedError) {
        std::cout << "[Ошибка оборудования] Датчик \"" << sensor->getType() 
                  << "\" отклонен! Погрешность " << sensor->getErrorMargin() 
                  << "°C выше нормы (" << maxAllowedError << "°C).\n";
        return;
    }

    connectedSensor = sensor;
    std::cout << "[Оборудование] Датчик \"" << sensor->getType() << "\" успешно подключен к блоку управления.\n";
}

void ControlUnit::disconnectSensor() {
    connectedSensor = nullptr;
    std::cout << "[Оборудование] Датчик отключен от блока управления.\n";
}

void ControlUnit::checkSystemStatus() const {
    if (connectedSensor) {
        std::cout << "[Статус] Система стабильна. Активный датчик: " << connectedSensor->getType() 
                  << " (Погрешность: " << connectedSensor->getErrorMargin() << "°C).\n";
    } else {
        std::cout << "[Статус] КРИТИЧЕСКАЯ ОШИБКА: Датчик температуры отсутствует!\n";
    }
}

double ControlUnit::getMaxAllowedError() const { return maxAllowedError; }
