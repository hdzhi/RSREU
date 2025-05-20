#include "Device.h"
#include <iostream>
#include <vector>
#include "Mechanism.h" // Include Mechanism to get its details vector

Device::Node::Node(Product *data) : data(data), next(nullptr) {}

Device::Device(const std::string &name) : name(name), head(nullptr) {}

Device::~Device()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
}

void Device::addProduct(Product *product)
{
    Node *newNode = new Node(product);
    if (!head)
    {
        head = newNode;
    }
    else
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void Device::removeProduct(int index)
{
    if (!head)
        return;

    if (index == 0)
    {
        Node *temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
        return;
    }

    Node *current = head;
    Node *prev = nullptr;
    int count = 0;

    while (current != nullptr && count != index)
    {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == nullptr)
        return;

    prev->next = current->next;
    delete current->data;
    delete current;
}

double Device::getTotalWeight() const
{
    double totalWeight = 0.0;
    Node *current = head;
    while (current != nullptr)
    {
        totalWeight += current->data->getWeight();
        current = current->next;
    }
    return totalWeight;
}

double Device::getTotalCost() const
{
    double totalCost = 0.0;
    Node *current = head;
    while (current != nullptr)
    {
        totalCost += current->data->getCost();
        current = current->next;
    }
    return totalCost;
}

double Device::getAverageDetailsPerDevice() const
{
    int totalDetails = 0;
    int productCount = 0;
    Node *current = head;

    while (current != nullptr)
    {
        // Check if the current product is a Mechanism
        Mechanism *mechanism = dynamic_cast<Mechanism *>(current->data);
        if (mechanism)
        {

            totalDetails += mechanism->details.size();
        }
        productCount++;
        current = current->next;
    }

    if (productCount > 0)
    {
        return static_cast<double>(totalDetails) / productCount;
    }
    else
    {
        return 0.0;
    }
}

void Device::printAllInfo() const
{
    std::cout << "Device: " << name << std::endl;
    Node *current = head;
    int i = 1;
    while (current != nullptr)
    {
        std::cout << "Item " << i << ": ";
        current->data->printInfo();
        current = current->next;
        i++;
    }
}

std::string Device::getName() const { return name; }

int Device::getTotalSensors() const
{
    int totalSensors = 0;
    Node *current = head;
    while (current != nullptr)
    {
        totalSensors += current->data->getSensorCount();
        current = current->next;
    }
    return totalSensors;
}

double Device::getTotalSensorCost() const
{
    double totalSensorCost = 0.0;
    Node *current = head;
    while (current != nullptr)
    {
        totalSensorCost += current->data->getSensorCost();
        current = current->next;
    }
    return totalSensorCost;
}