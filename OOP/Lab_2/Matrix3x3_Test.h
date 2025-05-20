// Matrix3x3Test.h
#ifndef MATRIX3X3TEST_H
#define MATRIX3X3TEST_H

#include "Matrix_3x3.h"

class Matrix3x3Test
{
public:
    Matrix3x3Test();
    void runAllTests();

private:
    void testAdditionMatrix3x3();
    void testMultipleMatrix3x3();
    void testScalarMatrix3x3();
    void testTransposeMatrix3x3();
    void testDetMatrix3x3();
    void testInverseMatrix3x3();
    void testIsMatrixIdent();

    bool compareMatrices(const Matrix3x3 &expected, const Matrix3x3 &actual) const;

    int testsPassed;
    int testsFailed;
};

#endif