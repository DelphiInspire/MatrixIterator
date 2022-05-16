#include "Matrix.h"

Matrix::Matrix()
{
    rows = 0;
    columns = 0;
    storageData = nullptr;
}

Matrix::Matrix(float** inData, size_t inRows, size_t inColumns)
{
    columns = inColumns;
    rows = inRows;
    getMemory();
    initData(inData);
}

Matrix::Matrix(float inNumber, size_t inRows, size_t inColumns)
{
    columns = inColumns;
    rows = inRows;
    getMemory();
    initData(inNumber);
}

Matrix::Matrix(const char* inString)
{
    std::vector<std::vector<float>> catchInput(VerifyCharInput(inString));
    rows = catchInput.size();
    columns = catchInput[0].size();
    getMemory();
    initData(catchInput);
}

Matrix::Matrix(const Matrix& copy_matrix)
{
    rows = 0;
    columns = 0;
    storageData = nullptr;
    *this = copy_matrix;
}

Matrix::Matrix(Matrix&& moving_matrix)
{
    columns = moving_matrix.columns;
    moving_matrix.columns = 0;
    rows = moving_matrix.rows;
    moving_matrix.rows = 0;

    if (moving_matrix.storageData != nullptr)
    {
        storageData = moving_matrix.storageData;
        moving_matrix.storageData = nullptr;
    }
}

Matrix& Matrix::operator=(const Matrix& copy_matrix)
{
    if (&copy_matrix == this)
    {
        return *this;
    }
    else
    {
        if (copy_matrix.rows == 0)
        {
            throw MemoryAllocException();
        }
        clearMemory(storageData, rows);
        rows = copy_matrix.rows;
        columns = copy_matrix.columns;
        getMemory();

        for (size_t row = 0; row <= rows - 1; row++)
        {
            for (size_t colm = 0; colm <= columns - 1; colm++)
            {
                storageData[row][colm] = copy_matrix.storageData[row][colm];
            }
        }
        return *this;
    }
}

Matrix& Matrix::operator=(Matrix&& moving_matrix)
{
    if (&moving_matrix == this)
    {
        return *this;
    }
    else
    {
        rows = moving_matrix.rows;
        columns = moving_matrix.columns;
        moving_matrix.rows = 0;
        moving_matrix.columns = 0;
        if (moving_matrix.storageData != nullptr)
        {
            storageData = moving_matrix.storageData;
            moving_matrix.storageData = nullptr;
        }
        return *this;
    }
}

Matrix& Matrix::operator+=(const Matrix& rhsMatrix)
{
    if (!isAllowPlusMinus(rhsMatrix))
    {
        throw  PlusMinusException();
    }

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            if (isPlusOverflow(storageData[row][column], rhsMatrix.storageData[row][column]))
            {
                throw OverflowException();
            }
            storageData[row][column] += rhsMatrix.storageData[row][column];
        }
    }
    return *this;
}

Matrix operator+(Matrix lhs, const Matrix& rhs)
{
    lhs += rhs;
    return lhs;
}

Matrix& Matrix::operator-=(const Matrix& rhsMatrix)
{
    if (!isAllowPlusMinus(rhsMatrix))
    {
        throw PlusMinusException();
    }
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            if (isMinusOverflow(storageData[row][column], rhsMatrix.storageData[row][column]))
            {
                throw OverflowException();
            }
            storageData[row][column] -= rhsMatrix.storageData[row][column];
        }
    }
    return *this;
}

Matrix operator-(Matrix lhsMatrix, const Matrix& rhsMatrix)
{
    lhsMatrix -= rhsMatrix;
    return lhsMatrix;
}

Matrix Matrix::operator*(const Matrix& rhsMatrix) const
{
    if (!isAllowMultiply(rhsMatrix))
    {
        throw MultiplyException();
    }
    Matrix result(0.0, rows, columns);
    float multiplyMember{ 0.0 };
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            for (size_t insideCounter = 0; insideCounter < columns; insideCounter++)
            {
                multiplyMember += storageData[row][insideCounter] * rhsMatrix.storageData[insideCounter][column];
            }
            result.storageData[row][column] = multiplyMember;
            multiplyMember = 0;
        }
    }
    return result;

}

Matrix Matrix::operator*(const float rhsMember) const
{
    Matrix result(0.0, rows, columns);
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            result.storageData[row][column] = storageData[row][column] * rhsMember;
        }
    }
    return result;
}

Matrix Matrix::operator*(const char* const inString) const
{
    Matrix result(0.0, rows, columns);
    std::vector<std::vector<float>> catchInput{ VerifyCharInput(inString) };
    const float multiplyMember{ catchInput[0][0] };
    result = *this * multiplyMember;
    return result;
}

Matrix* Matrix::operator*=(const Matrix& rhsMatrix)
{
    *this = *this * rhsMatrix;
    return this;
}

Matrix* Matrix::operator*=(const float rhsMember)
{
    *this = *this * rhsMember;
    return this;
}

Matrix Matrix::operator/(const Matrix& divideMatrix) const
{

    if (!isAllowDivide(divideMatrix))
    {
        throw DivideException();
    }
    Matrix divider{ divideMatrix };
    return  *this * divider.inverseMatrix();
}

Matrix Matrix::operator/(const float divideMember) const
{
    Matrix result(0.0, rows, columns);
    if (divideMember == 0.0)
    {
        return result;
    }
    else
    {
        for (size_t row = 0; row < rows; row++)
        {
            for (size_t column = 0; column < columns; column++)
            {
                result.storageData[row][column] = storageData[row][column] / divideMember;
            }
        }
        return result;
    }
}

Matrix Matrix::operator/(const char* const inString) const
{
    Matrix result(0.0, rows, columns);
    std::vector<std::vector<float>> catchInput{ VerifyCharInput(inString) };
    const float multiplyMember{ catchInput[0][0] };
    result = *this / multiplyMember;
    return result;
}

Matrix* Matrix::operator/=(const Matrix& divideMatrix)
{
    Matrix divider{ divideMatrix };
    *this = *this / divider;
    return this;
}

Matrix* Matrix::operator/=(const float divideMember)
{
    *this = *this / divideMember;
    return this;
}

void Matrix::getMemory()
{
    storageData = new float* [rows];
    for (size_t row = 0; row < rows; row++)
    {
        storageData[row] = new float[columns];
    }

}

float Matrix::getSum() const
{
    float result{ 0.0 };
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            if (!isPlusOverflow(result, storageData[row][column]))
            {
                result += storageData[row][column];
            }
            else
            {
                return std::numeric_limits<float>::max();
            }
        }
    }
    return result;
}

void Matrix::initData(float** inData)
{
    if (inData != nullptr)
    {
        for (size_t row = 0; row < rows; row++)
        {
            for (size_t column = 0; column < columns; column++)
            {
                storageData[row][column] = inData[row][column];
            }
        }
    }
}

void Matrix::initData(const float inNumber)
{
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t colm = 0; colm < columns; colm++)
        {
            storageData[row][colm] = inNumber;
        }
    }
}

void Matrix::initData(const std::vector<std::vector<float>>& input_data)
{
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            storageData[row][column] = input_data[row][column];
        }
    }
}

std::string Matrix::ToString()
{
    unsigned int inner_counter{ 0 };
    std::string result;

    result.push_back('[');
    if (this != nullptr)
    {
        for (size_t row = 0; row < rows; row++)
        {
            for (size_t column = 0; column < columns; column++)
            {
                result.push_back(char(97 + inner_counter));
                if (column != columns - 1)
                {
                    result.push_back(',');
                }
                inner_counter++;
            }
            if (row != rows - 1)
            {
                result.push_back(';');
                result.push_back(char(9));
            }

        }
    }
    result.push_back(']');

    return result;
}

std::vector<std::vector<float>> Matrix::VerifyCharInput(const char* const inString) const
{
    size_t sizeString{ strlen(inString) }; //size of the input char*
    size_t rowCounter{ 1 };
    size_t columnCounter{ 1 };
    size_t columnCounter_previous{ 1 };// for check quantity equals in each row

    std::string bufferNumber;//collector of the char '0-9'

    std::vector<std::vector<float>> representation_char_to_FLT;// collector of the convering result for data init
    representation_char_to_FLT.resize(rowCounter);

    bool isStart_checking{ false }; //begin to check quantity of columns in each row
    bool isSingleNumber{ false };

    for (size_t counter = 0; counter < sizeString; counter++)
    {
        switch (inString[counter])
        {

            case '[':
            {
                break;
            }

            case ']':
            {
                if (isStart_checking)
                {
                    if (columnCounter != columnCounter_previous)
                    {
                        representation_char_to_FLT.clear();
                        representation_char_to_FLT.shrink_to_fit();
                        throw InputVerificationException();
                    }
                }
                representation_char_to_FLT[rowCounter - 1].push_back(std::stof(bufferNumber));
                bufferNumber.clear();
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                if (counter == 0)
                {
                    isSingleNumber = true;
                }
                bufferNumber.push_back(inString[counter]);
                break;
            }

            case ';':
            {
                columnCounter_previous = columnCounter;
                representation_char_to_FLT[rowCounter - 1].push_back(std::stof(bufferNumber));
                bufferNumber.clear();
                if (isStart_checking)
                {
                    if (columnCounter != columnCounter_previous)
                    {
                        representation_char_to_FLT.clear();
                        representation_char_to_FLT.shrink_to_fit();
                        return representation_char_to_FLT;
                    }
                }
                columnCounter = 1;
                rowCounter++;
                representation_char_to_FLT.resize(rowCounter);
                isStart_checking = true;
                break;
            }

            case ',':
            {
                representation_char_to_FLT[rowCounter - 1].push_back(std::stof(bufferNumber));
                bufferNumber.clear();

                columnCounter++;
                break;
            }
            default:
            {
                representation_char_to_FLT.clear();
                representation_char_to_FLT.shrink_to_fit();
                throw InputVerificationException();
            }
        }
    }
    if (isSingleNumber)
    {
        representation_char_to_FLT[rowCounter - 1].push_back(std::stof(bufferNumber));
    }

    if (*inString == 0)
    {
        throw InputVerificationException();
    }

    return representation_char_to_FLT;
}

float Matrix::searchDeterminant() const
{
    if (isAllowDeterminant())
    {

        if (rows == 1)
        {
            return storageData[0][0];
        }
        else if (rows == 2)
        {
            return (storageData[0][0] * storageData[1][1] - storageData[0][1] * storageData[1][0]);
        }
        else
        {
            float determinant{ 0.0 };
            for (size_t column = 0; column < columns; column++)
            {

                Matrix* bufferMatrix = new Matrix(0.0, rows - 1, columns - 1);
                *bufferMatrix = getMinor(0, column);
                determinant += (powf(-1, 2 + column) * storageData[0][column] * bufferMatrix->searchDeterminant());
                delete bufferMatrix;
            }
            return determinant;
        }
    }
    else
    {
        return 0.0;
    }
}

Matrix Matrix::inverseMatrix() const
{
    float determinant{ 0 };

    determinant = searchDeterminant();
    Matrix result(0.0, rows, columns);
    if (determinant == 0)
    {
        return result;
    }

    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            result.storageData[row][column] = pow(-1, 2 + row + column) * getMinor(row, column).searchDeterminant();
        }
    }

    result = result.transpose();
    result *= (1 / determinant);
    return result;
}

Matrix Matrix::getMinor(const size_t row, const size_t column) const
{
    Matrix bufferMatrix(0.0, rows - 1, columns - 1);
    int rowCounter{ 0 };
    int columnCounter{ 0 };
    for (size_t innerRow = 0; innerRow < rows; innerRow++)
    {
        if (innerRow == row)
        {
            continue;
        }
        for (size_t innerColumn = 0; innerColumn < columns; innerColumn++)
        {
            if (innerColumn == column)
            {
                continue;
            }
            else
            {
                bufferMatrix.storageData[rowCounter][columnCounter] = storageData[innerRow][innerColumn];
                columnCounter++;
            }
        }
        columnCounter = 0;
        rowCounter++;
    }
    return bufferMatrix;
}

Matrix Matrix::transpose() const
{
    Matrix result(0.0, rows, columns);
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t column = 0; column < columns; column++)
        {
            result.storageData[column][row] = storageData[row][column];
        }
    }
    return result;
}

void Matrix::clearMemory(float** data, const size_t rows)
{
    if (rows != 0)
    {
        for (size_t row = 0; row < rows; row++)
        {
            delete[] data[row];
        }
        delete[] data;
    }
}

bool Matrix::isAllowPlusMinus(const Matrix& rhsMatrix) const
{
    if (rows != rhsMatrix.rows || columns != rhsMatrix.columns)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Matrix::isPlusOverflow(const float firstMember, const float secondMember) const
{
    if ((secondMember > 0 && firstMember > std::numeric_limits<float>::max()- secondMember) ||
        (secondMember < 0 && firstMember < - std::numeric_limits<float>::max() - secondMember))
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Matrix::isMinusOverflow(const float firstMember, const float secondMember) const
{
    if ((secondMember > 0 && firstMember <  - std::numeric_limits<float>::max() + secondMember) ||
        (secondMember < 0 && firstMember > std::numeric_limits<float>::max() + secondMember))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Matrix::isAllowMultiply(const Matrix& rhsMatrix) const
{
    if (columns != rhsMatrix.rows)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Matrix::isAllowDivide(const Matrix& rhsMatrix) const
{
    if(rhsMatrix.rows != rhsMatrix.columns || columns != rhsMatrix.rows)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Matrix::isAllowDeterminant() const
{
    if (rows != columns)
    {
        return false;
    }
    else
    {
        return true;
    }
}

float Matrix::getMajorDiagonalSum() const
{
    if(rows != columns)
    {
        throw SquareFormVerification();
    }

    float result{0.0};
    for (size_t row = 0, column = 0; row < rows; ++row, ++column)
    {
        result += storageData[row][column];
    }
    return result;
}

float Matrix::getMinorDiagonalSum() const
{
    if(rows != columns)
    {
        throw SquareFormVerification();
    }

    float result{0.0};
    for (size_t row = 0, column = columns - 1; row < rows; ++row, --column)
    {
        result += storageData[row][column];
    }
    return result;
}

float Matrix::getSumDiagonalsResult() const
{
    return getMajorDiagonalSum() + getMinorDiagonalSum();
}

Matrix::~Matrix()
{
    clearMemory(storageData, rows);
    storageData = nullptr;
}
//
// Created by Serhii Zaika on 10.05.2022.
//

