#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

class Product
{
public:
    virtual ~Product() {}
    virtual std::string getName() const = 0;
    virtual double getWeight() const = 0;
    virtual double getCost() const = 0;
    virtual std::string getDescription() const = 0;
    virtual int getSensorCount() const { return 0; }
    virtual double getSensorCost() const { return 0.0; }
    virtual void printInfo() const = 0;
};

#endif