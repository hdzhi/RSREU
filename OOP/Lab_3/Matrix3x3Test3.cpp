#include "Matrix3x3Test3.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;

Matrix3x3Test::Matrix3x3Test() : testsPassed(0), testsFailed(0) {}

void Matrix3x3Test::runAllTests()
{
    testAdditionMatrix3x3();
    testMultipleMatrix3x3();
    testScalarMatrix3x3();
    testTransposeMatrix3x3();
    testDetMatrix3x3();
    testInverseMatrix3x3();
    testIsMatrixIdent();
    testObjectFunctionality();
    testRandomMatrixGeneration();
    testAssignmentOperator();

    cout << "-----------------------------------" << endl;
    cout << "Total Tests Passed: " << testsPassed << endl;
    cout << "Total Tests Failed: " << testsFailed << endl;
    cout << "-----------------------------------" << endl;
}

bool Matrix3x3Test::compareMatrices(const Matrix3x3 &expected, const Matrix3x3 &actual) const
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (abs(expected.getElement(i, j) - actual.getElement(i, j)) > 1e-6)
            {
                return false;
            }
        }
    }
    return true;
}

void Matrix3x3Test::testAdditionMatrix3x3()
{
    cout << "testAdditionMatrix3x3:" << endl;

    cout << "  Test 1: Adding two matrices" << endl;
    float arr1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float arr2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3x3 matrix1(arr1);
    Matrix3x3 matrix2(arr2);
    float expectedArr[3][3] = {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
    Matrix3x3 expected(expectedArr);
    Matrix3x3 actual = matrix1 + matrix2;

    cout << "    Input Matrix 1:" << endl;
    matrix1.printMatrix3x3();
    cout << "    Input Matrix 2:" << endl;
    matrix2.printMatrix3x3();
    cout << "    Expected:" << endl;
    expected.printMatrix3x3();
    cout << "    Actual:" << endl;
    actual.printMatrix3x3();

    if (compareMatrices(expected, actual))
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}

void Matrix3x3Test::testMultipleMatrix3x3()
{
    cout << "testMultipleMatrix3x3:" << endl;

    cout << "  Test 1: Multiplying two matrices" << endl;
    float arr1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float arr2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3x3 matrix1(arr1);
    Matrix3x3 matrix2(arr2);
    float expectedArr[3][3] = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    Matrix3x3 expected(expectedArr);
    Matrix3x3 actual = matrix1 * matrix2;

    cout << "    Input Matrix 1:" << endl;
    matrix1.printMatrix3x3();
    cout << "    Input Matrix 2:" << endl;
    matrix2.printMatrix3x3();
    cout << "    Expected:" << endl;
    expected.printMatrix3x3();
    cout << "    Actual:" << endl;
    actual.printMatrix3x3();

    if (compareMatrices(expected, actual))
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}

void Matrix3x3Test::testScalarMatrix3x3()
{
    cout << "testScalarMatrix3x3:" << endl;

    cout << "  Test 1: Multiplying by a scalar" << endl;
    float arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 matrix(arr);
    float scalar = 2.0f;
    float expectedArr[3][3] = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    Matrix3x3 expected(expectedArr);
    Matrix3x3 actual = matrix * scalar;

    cout << "    Input Matrix:" << endl;
    matrix.printMatrix3x3();
    cout << "    Scalar: " << scalar << endl;
    cout << "    Expected:" << endl;
    expected.printMatrix3x3();
    cout << "    Actual:" << endl;
    actual.printMatrix3x3();

    if (compareMatrices(expected, actual))
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}

void Matrix3x3Test::testTransposeMatrix3x3()
{
    cout << "testTransposeMatrix3x3:" << endl;

    cout << "  Test 1: Transposing a matrix" << endl;
    float arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 matrix(arr);
    float expectedArr[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    Matrix3x3 expected(expectedArr);
    Matrix3x3 actual = matrix.transposeMatrix3x3();

    cout << "    Input Matrix:" << endl;
    matrix.printMatrix3x3();
    cout << "    Expected:" << endl;
    expected.printMatrix3x3();
    cout << "    Actual:" << endl;
    actual.printMatrix3x3();

    if (compareMatrices(expected, actual))
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}

void Matrix3x3Test::testDetMatrix3x3()
{
    cout << "testDetMatrix3x3:" << endl;

    cout << "  Test 1: Calculating determinant" << endl;
    float arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 matrix(arr);
    float expected = 0.0f;
    float actual = matrix.detMatrix3x3();

    cout << "    Input Matrix:" << endl;
    matrix.printMatrix3x3();
    cout << "    Expected: " << expected << endl;
    cout << "    Actual: " << actual << endl;

    if (abs(expected - actual) < 1e-6)
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}

void Matrix3x3Test::testInverseMatrix3x3()
{
    cout << "testInverseMatrix3x3:" << endl;

    cout << "  Test 1: Calculating inverse" << endl;
    float arr[3][3] = {{4, 7, 2}, {5, 2, 1}, {9, 6, 3}};
    Matrix3x3 matrix(arr);

    cout << "    Input Matrix:" << endl;
    matrix.printMatrix3x3();

    bool invertible = matrix.inverseMatrix3x3();
    cout << "    Invertible: " << invertible << endl;
    if (invertible)
    {
        cout << "    Inverse Matrix:" << endl;
        matrix.printMatrix3x3();
        testsPassed++;
    }
    else
    {
        cout << "    Matrix is not invertible" << endl;
        testsFailed++;
    }

    cout << endl;
}

void Matrix3x3Test::testIsMatrixIdent()
{
    cout << "testIsMatrixIdent:" << endl;

    cout << "  Test 1: Testing if an identity matrix is recognized" << endl;
    float arr1[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 identity(arr1);
    bool expectedIdentity = true;
    bool actualIdentity = identity.isIdentity();

    cout << "    Input Matrix:" << endl;
    identity.printMatrix3x3();
    cout << "    Expected: " << expectedIdentity << endl;
    cout << "    Actual: " << actualIdentity << endl;

    if (actualIdentity == expectedIdentity)
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}

void Matrix3x3Test::testObjectFunctionality()
{
    cout << "testObjectFunctionality:" << endl;

    cout << "  Test 1: Checking object creation count" << endl;
    int initialCreated = Object::getTotalObjectsCreated();
    Matrix3x3 matrix1;
    Matrix3x3 matrix2;
    int expectedCreated = initialCreated + 2;
    int actualCreated = Object::getTotalObjectsCreated();

    cout << "    Initial Created: " << initialCreated << endl;
    cout << "    Expected Created: " << expectedCreated << endl;
    cout << "    Actual Created: " << actualCreated << endl;

    if (actualCreated == expectedCreated)
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}

void Matrix3x3Test::testRandomMatrixGeneration()
{
    cout << "testRandomMatrixGeneration:" << endl;

    cout << "  Test 1: Generating random matrix within a range" << endl;
    float minVal = -5.0f;
    float maxVal = 5.0f;
    Matrix3x3 randomMatrix = Matrix3x3::createRandomMatrix(minVal, maxVal);

    cout << "    Min Value: " << minVal << endl;
    cout << "    Max Value: " << maxVal << endl;
    cout << "    Random Matrix:" << endl;
    randomMatrix.printMatrix3x3();

    bool withinRange = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            float element = randomMatrix.getElement(i, j);
            if (element < minVal || element > maxVal)
            {
                withinRange = false;
                break;
            }
        }
        if (!withinRange)
            break;
    }

    cout << "    Elements within range: " << (withinRange ? "Yes" : "No") << endl;

    if (withinRange)
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}

void Matrix3x3Test::testAssignmentOperator()
{
    cout << "testAssignmentOperator:" << endl;

    cout << "  Test 1: Assigning one matrix to another" << endl;
    float arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 matrix1(arr);
    Matrix3x3 matrix2;

    cout << "    Matrix 1:" << endl;
    matrix1.printMatrix3x3();
    cout << "    Matrix 2 (before assignment):" << endl;
    matrix2.printMatrix3x3();

    matrix2 = matrix1;

    cout << "    Matrix 2 (after assignment):" << endl;
    matrix2.printMatrix3x3();

    if (compareMatrices(matrix1, matrix2))
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }
    cout << endl;
}