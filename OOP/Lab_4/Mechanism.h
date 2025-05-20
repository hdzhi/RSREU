#ifndef MECHANISM_H
#define MECHANISM_H

#include "Product.h"
#include "Detail.h"
#include "Sensor.h"
#include "Device.h"
#include <vector>

class Mechanism : public Product
{
    friend class Device;

private:
    std::string name;
    std::vector<Detail *> details;
    std::vector<Sensor *> sensors;
    double wearTime;

public:
    Mechanism(const std::string &name, double wearTime);
    ~Mechanism();

    void addDetail(Detail *detail);
    void addSensor(Sensor *sensor);

    std::string getName() const override;
    double getWeight() const override;
    double getCost() const override;
    double getWearTime() const;
    std::string getDescription() const override;

    int getSensorCount() const override;
    double getSensorCost() const override;

    void printInfo() const override;
};

#endif