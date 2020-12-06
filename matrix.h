/*
This header file provides functionality of matrices through class Matrix
An instance of class Matrix is a 2D matrix of Complex objects. 
The following functions are supported: 
  - dimensions() : returns {rows, columns} as std::pair<int, int>
  - setVal(int row, int column, Complex val) : sets Matrix[row][column] = val
  - getVal(int row, int column) : returns Matrix[row][column] of type Complex
  - dimensionsToString() : returns dimensions of Matrix object in {rows, columns} string format
  - transpose() : returns Matrix object that is transpose of the current Matrix object
  - tensorProduct(Matrix other): returns Matrix object that represents tensor product of Matrix this and Matrix other

The following operators are supported: 
  +, -, *, +=, -=, *= 

  Two unary operators are also supported: 
    ! : returns Matrix object that represents complex conjugate of Matrix this
    - : returns Matrix object that represents negative of Matrix this
*/

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include "complex.h"

class Matrix {
    int rows, columns;  
    std::vector<std::vector<Complex>> matrix; 

    public: 
    Matrix(int rows, int columns); 
    Matrix(const std::vector<std::vector<Complex>>& matrix);
    Matrix(const std::vector<Complex>& array); 

    std::pair<int, int> dimensions() const;
    void setVal(int row, int column, Complex val); 
    Complex getVal(int row, int column) const; 
    std::string dimensionsToString() const; 

    Matrix operator -(); 
    Matrix operator !(); 
    Matrix transpose(); 
  
  //TODO: convert parameters and functions to const after working on Complex class 

    Matrix operator + (Matrix other); 
    void operator += (Matrix other); 
    Matrix operator - (Matrix other); 
    void operator -= (Matrix other); 
    Matrix operator * (Matrix other); 
    void operator *= (Matrix other); 
    
    Matrix tensorProduct(Matrix other); 
}; 

#endif
