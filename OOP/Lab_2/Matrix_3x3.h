// Matrix3x3.h
#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

class Matrix3x3
{
private:
    bool identity;
    float data[3][3];

    void isMatrixIdent();
    float getMinor(int i, int j) const;

public:
    Matrix3x3(); // Default constructor
    Matrix3x3(const float tempArr[3][3]);
    Matrix3x3(const Matrix3x3 &other); // Copy constructor

    bool isIdentity() const;

    float getElement(int row, int col) const;
    void setElement(int row, int col, float value);

    Matrix3x3 additionMatrix3x3(const Matrix3x3 &b) const;
    Matrix3x3 multipleMatrix3x3(const Matrix3x3 &b) const;
    Matrix3x3 scalarMatrix3x3(float b) const;
    Matrix3x3 transposeMatrix3x3() const;
    float detMatrix3x3() const;
    bool inverseMatrix3x3();

    void printMatrix3x3() const;
};

#endif