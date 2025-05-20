#include "Sensor.h"
#include <iostream>

Sensor::Sensor(const std::string &name, double cost, const std::string &characteristic) : name(name), cost(cost), characteristic(characteristic) {}

std::string Sensor::getName() const { return name; }
double Sensor::getWeight() const { return 0.0; }
double Sensor::getCost() const { return cost; }
std::string Sensor::getDescription() const { return "Sensor"; }

std::string Sensor::getCharacteristic() const { return characteristic; }

void Sensor::printInfo() const
{
    std::cout << "  Sensor: " << name << ", Characteristic: " << characteristic << ", Cost: " << cost << " $" << std::endl;
}