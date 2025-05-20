#ifndef DEVICE_H
#define DEVICE_H

#include "Product.h"
// #include "Node.h"

class Device
{
private:
    std::string name;
    struct Node
    {
        Product *data;
        Node *next;

        Node(Product *data);
    };
    Node *head;

public:
    Device(const std::string &name);
    ~Device();

    void addProduct(Product *product);
    void removeProduct(int index);

    double getTotalWeight() const;
    double getTotalCost() const;
    double getAverageDetailsPerDevice() const;
    void printAllInfo() const;
    std::string getName() const;
    int getTotalSensors() const;
    double getTotalSensorCost() const;
};

#endif