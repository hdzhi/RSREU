// Matrix3x3Test.cpp
#include "Matrix3x3_Test.h"
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

    // Test 1
    cout << "  Test 1: Adding two matrices" << endl;
    float arr1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float arr2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3x3 matrix1(arr1);
    Matrix3x3 matrix2(arr2);
    float expectedArr[3][3] = {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
    Matrix3x3 expected(expectedArr);
    Matrix3x3 actual = matrix1.additionMatrix3x3(matrix2);

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
    // Test 2
    cout << "  Test 2: Adding two matrices" << endl;
    float arr3[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float arr4[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3x3 matrix3(arr3);
    Matrix3x3 matrix4(arr4);
    float expectedArr2[3][3] = {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
    Matrix3x3 expected2(expectedArr2);
    Matrix3x3 actual2 = matrix3.additionMatrix3x3(matrix4);

    cout << "    Input Matrix 1:" << endl;
    matrix3.printMatrix3x3();
    cout << "    Input Matrix 2:" << endl;
    matrix4.printMatrix3x3();
    cout << "    Expected:" << endl;
    expected2.printMatrix3x3();
    cout << "    Actual:" << endl;
    actual2.printMatrix3x3();

    if (compareMatrices(expected2, actual2))
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

    // Test 1
    cout << "  Test 1: Multiplying two matrices" << endl;
    float arr1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float arr2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3x3 matrix1(arr1);
    Matrix3x3 matrix2(arr2);
    float expectedArr[3][3] = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    Matrix3x3 expected(expectedArr);
    Matrix3x3 actual = matrix1.multipleMatrix3x3(matrix2);

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

    // Test 2
    cout << "  Test 2: Multiplying two matrices" << endl;
    float arr3[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    float arr4[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 matrix3(arr3);
    Matrix3x3 matrix4(arr4);
    float expectedArr2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 expected2(expectedArr2);
    Matrix3x3 actual2 = matrix3.multipleMatrix3x3(matrix4);

    cout << "    Input Matrix 1:" << endl;
    matrix3.printMatrix3x3();
    cout << "    Input Matrix 2:" << endl;
    matrix4.printMatrix3x3();
    cout << "    Expected:" << endl;
    expected2.printMatrix3x3();
    cout << "    Actual:" << endl;
    actual2.printMatrix3x3();

    if (compareMatrices(expected2, actual2))
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

    // Test 1
    cout << "  Test 1: Multiplying by a scalar" << endl;
    float arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 matrix(arr);
    float scalar = 2.0f;
    float expectedArr[3][3] = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    Matrix3x3 expected(expectedArr);
    Matrix3x3 actual = matrix.scalarMatrix3x3(scalar);

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

    // Test 2
    cout << "  Test 2: Multiplying by a scalar" << endl;
    float arr2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 matrix2(arr2);
    float scalar2 = 0.0f;
    float expectedArr2[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    Matrix3x3 expected2(expectedArr2);
    Matrix3x3 actual2 = matrix2.scalarMatrix3x3(scalar2);

    cout << "    Input Matrix:" << endl;
    matrix2.printMatrix3x3();
    cout << "    Scalar: " << scalar2 << endl;
    cout << "    Expected:" << endl;
    expected2.printMatrix3x3();
    cout << "    Actual:" << endl;
    actual2.printMatrix3x3();

    if (compareMatrices(expected2, actual2))
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

    // Test 1
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
    // Test 2
    cout << "  Test 2: Transposing a matrix" << endl;
    float arr2[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 matrix2(arr2);
    float expectedArr2[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 expected2(expectedArr2);
    Matrix3x3 actual2 = matrix2.transposeMatrix3x3();

    cout << "    Input Matrix:" << endl;
    matrix2.printMatrix3x3();
    cout << "    Expected:" << endl;
    expected2.printMatrix3x3();
    cout << "    Actual:" << endl;
    actual2.printMatrix3x3();

    if (compareMatrices(expected2, actual2))
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

    // Test 1
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
    // Test 2
    cout << "  Test 2: Calculating determinant" << endl;
    float arr2[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Matrix3x3 matrix2(arr2);
    float expected2 = 1.0f;
    float actual2 = matrix2.detMatrix3x3();

    cout << "    Input Matrix:" << endl;
    matrix2.printMatrix3x3();
    cout << "    Expected: " << expected2 << endl;
    cout << "    Actual: " << actual2 << endl;

    if (abs(expected2 - actual2) < 1e-6)
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

    // Test 1
    cout << "  Test 1: Calculating inverse" << endl;
    float arr[3][3] = {{4, 7, 2}, {5, 2, 1}, {9, 6, 3}};
    Matrix3x3 matrix(arr);

    if (matrix.inverseMatrix3x3())
    {
        matrix.printMatrix3x3();
        testsPassed++;
    }
    else
    {
        testsFailed++;
    }
    cout << endl;

    // Test 2
    cout << "  Test 2: Calculating inverse" << endl;
    float arr2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 matrix2(arr2);

    if (matrix2.inverseMatrix3x3())
    {
        matrix2.printMatrix3x3();
        testsPassed++;
    }
    else
    {
        testsFailed++;
        cout << "    Result: Test Failed" << endl;
    }
    cout << endl;
}

void Matrix3x3Test::testIsMatrixIdent()
{
    cout << "testIsMatrixIdent:" << endl;

    // Test 1: Identity Matrix
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

    // Test 2: Non-Identity Matrix
    cout << "  Test 2: Testing if a non-identity matrix is recognized" << endl;
    float arr2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3x3 nonIdentity(arr2);
    bool expectedNonIdentity = false;
    bool actualNonIdentity = nonIdentity.isIdentity();

    cout << "    Input Matrix:" << endl;
    nonIdentity.printMatrix3x3();
    cout << "    Expected: " << expectedNonIdentity << endl;
    cout << "    Actual: " << actualNonIdentity << endl;

    if (actualNonIdentity == expectedNonIdentity)
    {
        cout << "    Result: Test Passed" << endl;
        testsPassed++;
    }
    else
    {
        cout << "    Result: Test Failed" << endl;
        testsFailed++;
    }

    // Test 3: Non-Identity Matrix
    cout << "  Test 3: Testing if a non-identity matrix is recognized" << endl;
    float arr3[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    Matrix3x3 nonIdentity2(arr3);
    bool expectedNonIdentity2 = false;
    bool actualNonIdentity2 = nonIdentity2.isIdentity();

    cout << "    Input Matrix:" << endl;
    nonIdentity2.printMatrix3x3();
    cout << "    Expected: " << expectedNonIdentity2 << endl;
    cout << "    Actual: " << actualNonIdentity2 << endl;

    if (actualNonIdentity2 == expectedNonIdentity2)
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