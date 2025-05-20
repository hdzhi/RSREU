// Matrix3x3.cpp
#include "Matrix_3x3.h"

Matrix3x3::Matrix3x3() : identity(false)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            data[i][j] = 0.0f;
        }
    }
}

Matrix3x3::Matrix3x3(const float tempArr[3][3]) : identity(false)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            data[i][j] = tempArr[i][j];
        }
    }
    isMatrixIdent();
}

Matrix3x3::Matrix3x3(const Matrix3x3 &other) : identity(other.identity)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

bool Matrix3x3::isIdentity() const
{
    return identity;
}

float Matrix3x3::getElement(int row, int col) const
{
    if (row < 0 || row >= 3 || col < 0 || col >= 3)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return data[row][col];
}

void Matrix3x3::setElement(int row, int col, float value)
{
    if (row < 0 || row >= 3 || col < 0 || col >= 3)
    {
        throw std::out_of_range("Index out of bounds");
    }
    data[row][col] = value;
}

void Matrix3x3::isMatrixIdent()
{
    identity = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if ((i == j && data[i][j] != 1) || (i != j && data[i][j] != 0))
            {
                identity = false;
                return;
            }
        }
    }
}

Matrix3x3 Matrix3x3::additionMatrix3x3(const Matrix3x3 &b) const
{
    Matrix3x3 res;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            res.data[i][j] = data[i][j] + b.data[i][j];
        }
    }
    res.isMatrixIdent();
    return res;
}

Matrix3x3 Matrix3x3::multipleMatrix3x3(const Matrix3x3 &b) const
{
    Matrix3x3 res;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            res.data[i][j] = data[i][0] * b.data[0][j] + data[i][1] * b.data[1][j] + data[i][2] * b.data[2][j];
        }
    }
    res.isMatrixIdent();
    return res;
}

Matrix3x3 Matrix3x3::scalarMatrix3x3(float b) const
{
    Matrix3x3 res(*this); // Create a copy
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            res.data[i][j] = data[i][j] * b;
        }
    }
    res.isMatrixIdent();
    return res;
}

Matrix3x3 Matrix3x3::transposeMatrix3x3() const
{
    Matrix3x3 res(*this); // Create a copy
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i; j < 3; ++j)
        {
            float temp = res.data[i][j];
            res.data[i][j] = res.data[j][i];
            res.data[j][i] = temp;
        }
    }
    res.isMatrixIdent();
    return res;
}

float Matrix3x3::detMatrix3x3() const
{
    return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
           data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
           data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
}

float Matrix3x3::getMinor(int i, int j) const
{
    float submatrix[2][2];
    int row = 0, col = 0;

    for (int r = 0; r < 3; r++)
    {
        if (r == i)
            continue;
        for (int c = 0; c < 3; c++)
        {
            if (c == j)
                continue;
            submatrix[row][col] = data[r][c];
            col++;
        }
        row++;
        col = 0;
    }

    return pow(-1, i + j) * (submatrix[0][0] * submatrix[1][1] - submatrix[0][1] * submatrix[1][0]);
}

bool Matrix3x3::inverseMatrix3x3()
{
    float det = detMatrix3x3();
    if (det != 0)
    {

        Matrix3x3 algebraicAddition;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                float minor = getMinor(i, j);
                algebraicAddition.data[i][j] = minor;
            }
        }

        Matrix3x3 transposedAlgebraicAddition = algebraicAddition.transposeMatrix3x3();

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                data[i][j] = transposedAlgebraicAddition.data[i][j] / det;
            }
        }

        isMatrixIdent();

        return true;
    }
    else
    {
        return false;
    }
}

void Matrix3x3::printMatrix3x3() const
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << std::fixed << std::setprecision(2) << std::setw(12) << data[i][j];
        }
        std::cout << std::endl;
    }

    if (identity)
    {
        std::cout << "Unit matrix" << std::endl
                  << std::endl;
    }
    else
    {
        std::cout << "Not unit matrix" << std::endl
                  << std::endl;
    }
}