#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept> // For exception handling
#include <cmath>     // For pow()
#include <limits>    // For numeric_limits

using namespace std;

// Define a struct for a 3x3 matrix
struct Matrix3x3
{
    bool identity;
    double data[3][3]; // Use double for better precision
};

// Function to check if a matrix is an identity matrix
void isMatrixIdent(Matrix3x3 &matrix)
{ // Pass by reference
    matrix.identity = true;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if ((i == j && matrix.data[i][j] != 1.0) || (i != j && matrix.data[i][j] != 0.0))
            {
                matrix.identity = false;
                return; // Exit early once non-identity element found
            }
        }
    }
}

// Function to create a Matrix3x3 from a 2D array
Matrix3x3 createMatrix3x3(const double tempArr[3][3])
{
    Matrix3x3 matrix;
    matrix.identity = false;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            matrix.data[i][j] = tempArr[i][j];
        }
    }

    isMatrixIdent(matrix);
    return matrix;
}

// Function to input a Matrix3x3 from the user
Matrix3x3 inputMatrix3x3()
{
    double tempArr[3][3];

    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "Enter row " << i + 1 << ": ";
        for (int j = 0; j < 3; ++j)
        {
            cin >> tempArr[i][j];
            if (cin.fail())
            {
                cin.clear();                                         // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
                throw runtime_error("Invalid input.  Please enter numbers only.");
            }
        }
    }

    return createMatrix3x3(tempArr);
}

// Function to add two Matrix3x3 objects
Matrix3x3 additionMatrix3x3(const Matrix3x3 &a, const Matrix3x3 &b)
{ // Pass by const reference
    Matrix3x3 res;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            res.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }

    isMatrixIdent(res);
    return res;
}

// Function to multiply two Matrix3x3 objects
Matrix3x3 multipleMatrix3x3(const Matrix3x3 &a, const Matrix3x3 &b)
{ // Pass by const reference
    Matrix3x3 res;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            res.data[i][j] = a.data[i][0] * b.data[0][j] + a.data[i][1] * b.data[1][j] + a.data[i][2] * b.data[2][j];
        }
    }

    isMatrixIdent(res);
    return res;
}

// Function to multiply a Matrix3x3 by a scalar
void scalarMatrix3x3(Matrix3x3 &a, double b)
{ // Pass by reference
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            a.data[i][j] = a.data[i][j] * b;
        }
    }

    isMatrixIdent(a);
}

// Function to transpose a Matrix3x3
void transposeMatrix3x3(Matrix3x3 &a)
{ // Pass by reference
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i + 1; j < 3; ++j)
        { // Start j from i+1 to avoid double-swapping
            double temp = a.data[i][j];
            a.data[i][j] = a.data[j][i];
            a.data[j][i] = temp;
        }
    }

    isMatrixIdent(a);
}

// Function to calculate the determinant of a Matrix3x3
double detMatrix3x3(const Matrix3x3 &a)
{ // Pass by const reference
    return a.data[0][0] * (a.data[1][1] * a.data[2][2] - a.data[1][2] * a.data[2][1]) - a.data[0][1] * (a.data[1][0] * a.data[2][2] - a.data[1][2] * a.data[2][0]) + a.data[0][2] * (a.data[1][0] * a.data[2][1] - a.data[1][1] * a.data[2][0]);
}

// Function to get the minor of a Matrix3x3
double getMinor(const Matrix3x3 &matrix, int i, int j)
{ // Pass by const reference
    double submatrix[2][2];
    int row = 0, col = 0;

    for (int r = 0; r < 3; ++r)
    {
        if (r == i)
            continue;
        for (int c = 0; c < 3; ++c)
        {
            if (c == j)
                continue;
            submatrix[row][col] = matrix.data[r][c];
            ++col;
        }
        ++row;
        col = 0;
    }

    return pow(-1, i + j) * (submatrix[0][0] * submatrix[1][1] - submatrix[0][1] * submatrix[1][0]);
}

// Function to calculate the inverse of a Matrix3x3
bool inverseMatrix3x3(Matrix3x3 &a)
{ // Pass by reference
    double det = detMatrix3x3(a);
    if (abs(det) > numeric_limits<double>::epsilon())
    { // Use epsilon for floating-point comparison

        Matrix3x3 algebraicAddition;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                double minor = getMinor(a, i, j);
                algebraicAddition.data[i][j] = minor;
            }
        }

        transposeMatrix3x3(algebraicAddition);

        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                a.data[i][j] = algebraicAddition.data[i][j] / det;
            }
        }

        isMatrixIdent(a);
        return true;
    }
    else
    {
        return false;
    }
}

// Function to print a Matrix3x3
void printMatrix3x3(const Matrix3x3 &matrix)
{ // Pass by const reference
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << fixed << setprecision(2) << setw(12) << matrix.data[i][j];
        }
        cout << endl;
    }

    if (matrix.identity)
    {
        cout << "Unit matrix" << endl
             << endl;
    }
    else
    {
        cout << "Not unit matrix" << endl
             << endl;
    }
}

int main()
{
    int cmd;
    Matrix3x3 matrix1, matrix2;

    cout << "Commands:" << endl
         << "1. Add Matrix" << endl
         << "2. Mul Matrix" << endl
         << "3. Scalar Matrix" << endl
         << "4. Transpose Matrix" << endl
         << "5. Det Matrix" << endl
         << "6. Inverse Matrix" << endl
         << "7. Print Matrix" << endl
         << "8. Exit" << endl
         << endl;

    do
    {
        cout << "Enter command: ";
        cin >> cmd;

        // Input validation for the command
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 8." << endl
                 << endl;
            continue; // Skip the rest of the loop and ask for input again
        }

        switch (cmd)
        {
        case 1:
        {
            try
            {
                matrix1 = inputMatrix3x3();
                matrix2 = inputMatrix3x3();
                Matrix3x3 res = additionMatrix3x3(matrix1, matrix2); // Pass by value is fine for small struct
                printMatrix3x3(res);
            }
            catch (const runtime_error &error)
            {
                cout << "Error: " << error.what() << endl
                     << endl;
            }
            break;
        }
        case 2:
        {
            try
            {
                matrix1 = inputMatrix3x3();
                matrix2 = inputMatrix3x3();
                Matrix3x3 res = multipleMatrix3x3(matrix1, matrix2);
                printMatrix3x3(res);
            }
            catch (const runtime_error &error)
            {
                cout << "Error: " << error.what() << endl
                     << endl;
            }
            break;
        }
        case 3:
        {
            try
            {
                matrix1 = inputMatrix3x3();

                double sc;
                cout << "Enter scalar: ";
                cin >> sc;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw runtime_error("Invalid input. Please enter a number.");
                }

                scalarMatrix3x3(matrix1, sc);
                printMatrix3x3(matrix1);
            }
            catch (const runtime_error &error)
            {
                cout << "Error: " << error.what() << endl
                     << endl;
            }
            break;
        }
        case 4:
        {
            try
            {
                matrix1 = inputMatrix3x3();
                transposeMatrix3x3(matrix1);
                printMatrix3x3(matrix1);
            }
            catch (const runtime_error &error)
            {
                cout << "Error: " << error.what() << endl
                     << endl;
            }
            break;
        }
        case 5:
        {
            try
            {
                matrix1 = inputMatrix3x3();
                double det = detMatrix3x3(matrix1);
                cout << "Determinant = " << det << endl
                     << endl;
            }
            catch (const runtime_error &error)
            {
                cout << "Error: " << error.what() << endl
                     << endl;
            }
            break;
        }
        case 6:
        {
            try
            {
                matrix1 = inputMatrix3x3();
                if (inverseMatrix3x3(matrix1))
                {
                    cout << "Inverse matrix:" << endl;
                    printMatrix3x3(matrix1);
                }
                else
                {
                    cout << "Determinant = 0! Cannot invert the matrix." << endl
                         << endl;
                }
            }
            catch (const runtime_error &error)
            {
                cout << "Error: " << error.what() << endl
                     << endl;
            }
            break;
        }
        case 7:
        {
            try
            {
                matrix1 = inputMatrix3x3();
                cout << "Matrix:" << endl;
                printMatrix3x3(matrix1);
            }
            catch (const runtime_error &error)
            {
                cout << "Error: " << error.what() << endl
                     << endl;
            }
            break;
        }
        case 8:
        {
            cout << "Exiting..." << endl;
            return 0;
        }
        default:
        {
            cout << "Error! Wrong command. Please enter a number between 1 and 8." << endl
                 << endl;
            break;
        }
        }

    } while (true);

    system("pause");
    return 0;
}