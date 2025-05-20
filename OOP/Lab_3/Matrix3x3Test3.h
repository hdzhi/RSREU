#ifndef MATRIX3X3TEST_H
#define MATRIX3X3TEST_H

#include "Matrix3x33.h"

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
    void testObjectFunctionality();
    void testRandomMatrixGeneration();
    void testAssignmentOperator();

    bool compareMatrices(const Matrix3x3 &expected, const Matrix3x3 &actual) const;

    int testsPassed;
    int testsFailed;
};

#endif