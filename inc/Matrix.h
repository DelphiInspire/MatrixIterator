#pragma once
#include<string>
#include<vector>
#include<cmath>
#include"Exception.h"

class Matrix
{
public:
	Matrix();
	Matrix(float inNumber, size_t inRows, size_t inColumns);//constructor int 
	Matrix(float** inData, size_t inRows, size_t inColumns);// constructor int**
	Matrix(const char* inString);// constructor char
	Matrix(const Matrix& copy_matrix);//copy constructor
	Matrix(Matrix&& moving_matrix);//moving constructor
	std::string ToString();
    float getMinorDiagonalSum() const;
    float getMajorDiagonalSum() const;
    float getSumDiagonalsResult() const;

	Matrix& operator=(const Matrix& copy_matrix);

	Matrix& operator=(Matrix&& moving_matrix);

	Matrix& operator+=(const Matrix& rhsMatrix);
	friend Matrix operator+(Matrix lhsMatrix, const Matrix& rhsMatrix);
	
	Matrix& operator-=(const Matrix& rhsMatrix);
	friend Matrix operator-(Matrix lhsMatrix, const Matrix& rhsMatrix);

	Matrix operator*(const Matrix& rhsMatrix) const;
	Matrix operator*(const float rhsMember) const;
	Matrix operator*(const char* const inString) const;
	Matrix* operator*=(const Matrix& rhsMatrix);
	Matrix* operator*=(const float rhsMember);
	
	Matrix operator/(const Matrix& divideMatrix) const;
	Matrix operator/(const float divideMember) const;
	Matrix operator/(const char* const inString) const;
	Matrix* operator/=(const Matrix& divideMatrix);
	Matrix* operator/=(const float divideMember);

    bool operator==(const Matrix& comparisonMatrix) const;
	
	friend bool operator>(const Matrix& lhsMatrix, const Matrix& rhsMatrix) 
	{ 
		return lhsMatrix.getSum() > rhsMatrix.getSum(); 
	}

	friend bool operator<(const Matrix& lhsMatrix, const Matrix& rhsMatrix)
	{
		return lhsMatrix.getSum() < rhsMatrix.getSum();
	}

	friend bool operator>=(const Matrix& lhsMatrix, const Matrix& rhsMatrix)
	{
		return !(lhsMatrix.getSum() < rhsMatrix.getSum());
	}

	friend bool operator<=(const Matrix& lhsMatrix, const Matrix& rhsMatrix)
	{
		return !(lhsMatrix.getSum() > rhsMatrix.getSum());
	}
	~Matrix();
private:
	size_t rows; 
	size_t columns;
	float** storageData;
	
	void getMemory();
	void initData(float** input_data = nullptr);
	void initData(const std::vector<std::vector<float>>& input_data);
	void initData(const float inNumber);
	void clearMemory(float** data, const size_t rows);

	float searchDeterminant() const;
	Matrix transpose() const;
	Matrix getMinor(const size_t row, const size_t column) const;
	Matrix inverseMatrix() const;
	float getSum() const;


	std::vector<std::vector<float>> VerifyCharInput(const char* const inString) const;
protected:
	bool isAllowPlusMinus(const Matrix& rhsMatrix) const;
	bool isAllowMultiply(const Matrix& rhsMatrix) const;
	bool isAllowDivide(const Matrix& rhsMatrix) const;
	bool isAllowDeterminant() const;
	bool isPlusOverflow(const float firstMember, const float secondMember) const;
	bool isMinusOverflow(const float firstMember, const float secondMember) const;
};
