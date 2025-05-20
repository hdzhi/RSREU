// Object.cpp
#include "Object3.h"
#include <cstdlib>
#include <cstring>

int Object::totalObjectsCreated = 0;
int Object::totalObjectsActive = 0;

Object::Object() : operations(nullptr), opCount(0), opCapacity(0)
{
    totalObjectsCreated++;
    totalObjectsActive++;
}

Object::Object(const Object &other) : operations(nullptr), opCount(0), opCapacity(0)
{
    totalObjectsCreated++;
    totalObjectsActive++;

    // Copy operations array
    if (other.opCount > 0)
    {
        opCapacity = other.opCapacity;
        operations = new char[opCapacity];
        std::memcpy(operations, other.operations, other.opCount * sizeof(char));
        opCount = other.opCount;
    }
}

Object::~Object()
{
    delete[] operations;
    totalObjectsActive--;
}

void Object::printTotalInfo()
{
    std::cout << "Total Objects Created: " << totalObjectsCreated << std::endl;
    std::cout << "Total Objects Active: " << totalObjectsActive << std::endl;
}

void Object::addOp(char op)
{
    if (opCount == opCapacity)
    {
        opCapacity = (opCapacity == 0) ? 1 : opCapacity * 2;
        char *newOperations = new char[opCapacity];
        if (operations != nullptr)
        {
            std::memcpy(newOperations, operations, opCount * sizeof(char));
        }

        delete[] operations;
        operations = newOperations;
    }
    operations[opCount++] = op;
}

void Object::clearOp()
{
    delete[] operations;
    operations = nullptr;
    opCount = 0;
    opCapacity = 0;
}

void Object::printOp() const
{
    std::cout << "Operations: ";
    for (int i = 0; i < opCount; ++i)
    {
        std::cout << operations[i] << " ";
    }
    std::cout << std::endl;
}

Object &Object::operator=(const Object &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] operations;
    operations = nullptr;
    opCount = 0;
    opCapacity = 0;

    if (other.opCount > 0)
    {
        opCapacity = other.opCapacity;
        operations = new char[opCapacity];
        std::memcpy(operations, other.operations, other.opCount * sizeof(char));
        opCount = other.opCount;
    }

    return *this;
}

int Object::getTotalObjectsCreated()
{
    return totalObjectsCreated;
}

int Object::getTotalObjectsActive()
{
    return totalObjectsActive;
}