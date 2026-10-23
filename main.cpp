#include <iostream>
#include <clocale>
#include <windows.h>
#include "Incubator.hpp"
#include "Sensor.hpp"

int main() {
    // Настройка русского языка в консоли
    std::setlocale(LC_ALL, "Russian");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::cout << "=== СЦЕНАРИЙ 1: Проверка правил и работа оборудования ===\n";
    // Создаем два внешних датчика (Агрегация)
    Sensor* brokenSensor = new Sensor("Дешевый китайский датчик DHT11", 2.5); // Погрешность 2.5°C
    Sensor* precisionSensor = new Sensor("Высокоточный цифровой DS18B24", 0.1); // Погрешность 0.1°C

    // Создаем инкубатор (Лимит погрешности системы: 0.5°C)
    Incubator* myIncubator = new Incubator("Несушка-Автомат v4", 64, 0.5);
    myIncubator->powerOn();

    // 1. Проверка правила: датчик с погрешностью 2.5°C должен быть отклонен
    std::cout << "\nПопытка подключения первого датчика:\n";
    myIncubator->installSensor(brokenSensor);

    // 2. Корректное действие: точный датчик успешно подключается
    std::cout << "\nПопытка подключения второго датчика:\n";
    myIncubator->installSensor(precisionSensor);
    myIncubator->powerOn();

    // Уничтожаем инкубатор. Его внутренний блок управления сотрется (Композиция),
    // но датчик precisionSensor останется цел в памяти (Агрегация).
    std::cout << "\nДемонтаж инкубатора:\n";
    delete myIncubator; 
    std::cout << "\n";


    std::cout << "=== СЦЕНАРИЙ 2: Демонстрация Памяти и Времени Жизни ===\n";
    // А. Локальные объекты в статическом блоке памяти
    {
        std::cout << "--> Вход в локальный блок (Статическая память)\n";
        Incubator localIncubator("Бюджет-И-10", 10, 0.9);
        std::cout << "--> Выход из локального блока\n";
    }
    std::cout << "--> Локальный инкубатор и его блок управления автоматически уничтожены.\n\n";

    // Б. Разница времени жизни при агрегации
    Sensor* warehouseSensor = new Sensor("Запасной промышленный датчик", 0.2);
    {
        std::cout << "--> Вход во вложенный блок (Удаление целого)\n";
        Incubator* tempIncubator = new Incubator("Экспериментальный Т-100", 150, 0.3);
        tempIncubator->installSensor(warehouseSensor);

        std::cout << "--> Уничтожаем инкубатор (ЦЕЛОЕ)...\n";
        delete tempIncubator; 
    }
    // Проверяем, жив ли агрегированный датчик
    std::cout << "--> Проверка агрегированного объекта после удаления владельца:\n";
    std::cout << "Датчик на складе всё ещё существует в памяти: " << warehouseSensor->getType() << "\n\n";

    // Очищаем оставшуюся динамическую память
    delete warehouseSensor;
    delete precisionSensor;
    delete brokenSensor;

    return 0;
}
