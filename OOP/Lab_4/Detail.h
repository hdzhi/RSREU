#ifndef DETAIL_H
#define DETAIL_H

#include "Product.h"

class Detail : public Product
{
private:
    std::string name;
    double weight;
    double cost;

public:
    Detail(const std::string &name, double weight, double cost);

    std::string getName() const override;
    double getWeight() const override;
    double getCost() const override;
    std::string getDescription() const override;
    void printInfo() const override;
};

#endif