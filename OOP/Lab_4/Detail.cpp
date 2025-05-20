#include "Detail.h"
#include <iostream>

Detail::Detail(const std::string &name, double weight, double cost) : name(name), weight(weight), cost(cost) {}

std::string Detail::getName() const { return name; }
double Detail::getWeight() const { return weight; }
double Detail::getCost() const { return cost; }
std::string Detail::getDescription() const { return "Detail"; }

void Detail::printInfo() const
{
    std::cout << "  Detail: " << name << ", Weight: " << weight << " kg, Cost: " << cost << " $\n";
}