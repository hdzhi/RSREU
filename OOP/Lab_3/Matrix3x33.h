#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <random>
#include "Object3.h"

class Matrix3x3 : public Object
{
private:
    bool identity;
    float data[3][3];

    void isMatrixIdent();
    float getMinor(int i, int j) const;

public:
    Matrix3x3();
    Matrix3x3(const float tempArr[3][3]);
    Matrix3x3(const Matrix3x3 &other);

    bool isIdentity() const;

    float getElement(int row, int col) const;
    void setElement(int row, int col, float value);

    Matrix3x3 operator+(const Matrix3x3 &b);
    Matrix3x3 operator*(const Matrix3x3 &b);
    Matrix3x3 operator*(float b);

    Matrix3x3 transposeMatrix3x3();
    float detMatrix3x3();
    bool inverseMatrix3x3();

    void printMatrix3x3() const;

    static Matrix3x3 createRandomMatrix(float minVal, float maxVal);

    Matrix3x3 &operator=(const Matrix3x3 &other);
};

#endif