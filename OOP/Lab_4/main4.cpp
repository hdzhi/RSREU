#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include "Detail.h"
#include "Sensor.h"
#include "Mechanism.h"
#include "Node.h"
#include "Device.h"

// Function to generate random products
Product *generateRandomProduct()
{
    static std::mt19937 generator(std::time(nullptr));
    std::uniform_int_distribution<int> distribution(0, 2); // 0 - Detail, 1 - Mechanism, 2 - Sensor
    int choice = distribution(generator);

    if (choice == 0)
    {
        // Generate a Detail
        std::uniform_real_distribution<double> weightDist(0.1, 5.0);
        std::uniform_real_distribution<double> costDist(10.0, 100.0);
        return new Detail("Random Detail", weightDist(generator), costDist(generator));
    }
    else if (choice == 1)
    {
        // Generate a Mechanism (add details and sensors later if needed)
        std::uniform_real_distribution<double> wearTimeDist(100.0, 1000.0);
        return new Mechanism("Random Mechanism", wearTimeDist(generator));
    }
    else
    {
        // Generate a Sensor
        std::uniform_real_distribution<double> costDist(50.0, 200.0);
        return new Sensor("Random Sensor", costDist(generator), "Temperature"); // Example characteristic
    }
}

int main()
{
    // Create an instance of the composite entity
    Device myDevice("My Awesome Device");

    Detail *detail1 = new Detail("Bolt", 0.1, 2.5);
    Detail *detail2 = new Detail("Nut", 0.05, 1.5);
    Sensor *sensor1 = new Sensor("Temperature Sensor", 50.0, "Temperature");

    Mechanism *mechanism1 = new Mechanism("Gearbox", 500.0);
    mechanism1->addDetail(detail1);
    mechanism1->addDetail(detail2);
    mechanism1->addSensor(sensor1);

    Node *node1 = new Node("Power Unit");
    node1->addMechanism(mechanism1);

    myDevice.addProduct(node1);

    // Randomly generate N objects and add them to the device
    int N = 3;
    for (int i = 0; i < N; ++i)
    {
        myDevice.addProduct(generateRandomProduct());
    }

    // Output information about the device
    myDevice.printAllInfo();

    // Calculate and output the total weight and cost of the entire device
    std::cout << "\nTotal weight of the device: " << myDevice.getTotalWeight() << " kg" << std::endl;
    std::cout << "Total cost of the device: " << myDevice.getTotalCost() << " $" << std::endl;

    // Calculate the average number of details per device
    std::cout << "Average number of details per mechanism: " << myDevice.getAverageDetailsPerDevice() << std::endl;

    // Total number of sensors and their total cost per node
    std::cout << "Total number of sensors in the device: " << myDevice.getTotalSensors() << std::endl;
    std::cout << "Total cost of sensors in the device: " << myDevice.getTotalSensorCost() << " $" << std::endl;

    // Removing object from the list
    std::cout << "\nRemoving object at index 1..." << std::endl;
    myDevice.removeProduct(1);

    // Output information again after removal
    myDevice.printAllInfo();

    return 0;
}