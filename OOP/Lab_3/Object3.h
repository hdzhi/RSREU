
#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

class Object
{
private:
    static int totalObjectsCreated;
    static int totalObjectsActive;
    char *operations;
    int opCount;
    int opCapacity;

protected:
    Object();
    Object(const Object &other);
    virtual ~Object(); // Virtual destructor for proper inheritance

public:
    static void printTotalInfo();

    void addOp(char op);
    void clearOp();
    void printOp() const;

    Object &operator=(const Object &other); // Assignment operator

    static int getTotalObjectsCreated();
    static int getTotalObjectsActive();
};

#endif