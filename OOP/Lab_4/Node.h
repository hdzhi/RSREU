#ifndef NODE_H
#define NODE_H

#include "Mechanism.h"
#include "Product.h"
#include <vector>

class Node : public Product
{
private:
    std::string name;
    std::vector<Mechanism *> mechanisms;

public:
    Node(const std::string &name);
    ~Node();

    void addMechanism(Mechanism *mechanism);

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