#include "Node.h"
#include <iostream>

Node::Node(const std::string &name) : name(name) {}

Node::~Node()
{
    for (Mechanism *mechanism : mechanisms)
    {
        delete mechanism;
    }
}

void Node::addMechanism(Mechanism *mechanism) { mechanisms.push_back(mechanism); }

std::string Node::getName() const { return name; }

double Node::getWeight() const
{
    double totalWeight = 0.0;
    for (Mechanism *mechanism : mechanisms)
    {
        totalWeight += mechanism->getWeight();
    }
    // Коэффициент сложности транспортировки
    if (totalWeight > 50)
    {
        return totalWeight * 1.2;
    }
    else if (totalWeight > 20)
    {
        return totalWeight * 1.1;
    }
    return totalWeight;
}

double Node::getCost() const
{
    double totalCost = 0.0;
    for (Mechanism *mechanism : mechanisms)
    {
        totalCost += mechanism->getCost();
    }
    return totalCost;
}

double Node::getWearTime() const
{
    double totalWearTime = 0.0;
    for (Mechanism *mechanism : mechanisms)
    {
        totalWearTime += mechanism->getWearTime();
    }
    return totalWearTime;
}

std::string Node::getDescription() const { return "Node"; }

int Node::getSensorCount() const
{
    int totalSensorCount = 0;
    for (Mechanism *mechanism : mechanisms)
    {
        totalSensorCount += mechanism->getSensorCount();
    }
    return totalSensorCount;
}

double Node::getSensorCost() const
{
    double totalSensorCost = 0.0;
    for (Mechanism *mechanism : mechanisms)
    {
        totalSensorCost += mechanism->getSensorCost();
    }
    return totalSensorCost;
}

void Node::printInfo() const
{
    std::cout << "Node: " << name << ", Weight: " << getWeight() << " kg, Cost: " << getCost() << " $" << std::endl;
    std::cout << "  Mechanisms:" << std::endl;
    for (Mechanism *mechanism : mechanisms)
    {
        mechanism->printInfo();
    }
}