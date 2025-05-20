#include "Mechanism.h"
#include <iostream>

Mechanism::Mechanism(const std::string &name, double wearTime) : name(name), wearTime(wearTime) {}

Mechanism::~Mechanism()
{
    for (Detail *detail : details)
    {
        delete detail;
    }
    for (Sensor *sensor : sensors)
    {
        delete sensor;
    }
}

void Mechanism::addDetail(Detail *detail) { details.push_back(detail); }
void Mechanism::addSensor(Sensor *sensor) { sensors.push_back(sensor); }

std::string Mechanism::getName() const { return name; };

double Mechanism::getWeight() const
{
    double totalWeight = 0.0;
    for (Detail *detail : details)
    {
        totalWeight += detail->getWeight();
    }
    return totalWeight;
};

double Mechanism::getCost() const
{
    double totalCost = 0.0;
    for (Detail *detail : details)
    {
        totalCost += detail->getCost();
    }
    for (Sensor *sensor : sensors)
    {
        totalCost += sensor->getCost();
    }
    return totalCost;
};

double Mechanism::getWearTime() const { return wearTime; }
std::string Mechanism::getDescription() const { return "Mechanism"; }

int Mechanism::getSensorCount() const { return sensors.size(); }

double Mechanism::getSensorCost() const
{
    double totalSensorCost = 0.0;
    for (Sensor *sensor : sensors)
    {
        totalSensorCost += sensor->getCost();
    }
    return totalSensorCost;
}

void Mechanism::printInfo() const
{
    std::cout << "Mechanism: " << name << ", Wear Time: " << wearTime << ", Weight: " << getWeight() << " kg, Cost: " << getCost() << " $" << std::endl;
    std::cout << "  Details:" << std::endl;
    for (Detail *detail : details)
    {
        detail->printInfo();
    }
    std::cout << "  Sensors:" << std::endl;
    for (Sensor *sensor : sensors)
    {
        sensor->printInfo();
    }
}