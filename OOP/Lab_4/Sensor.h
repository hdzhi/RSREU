#ifndef SENSOR_H
#define SENSOR_H

#include "Product.h"
#include <string>

class Sensor : public Product
{
private:
    std::string name;
    double cost;
    std::string characteristic;

public:
    Sensor(const std::string &name, double cost, const std::string &characteristic);

    std::string getName() const override;
    double getWeight() const override;
    double getCost() const override;
    std::string getDescription() const override;

    std::string getCharacteristic() const;
    void printInfo() const override;
};

#endif