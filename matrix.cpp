#include "matrix.h"

Matrix::Matrix(int rows, int columns) {
    this->rows = rows; 
    this->columns = columns; 
    this->matrix = std::vector<std::vector<Complex>>(rows, std::vector<Complex>(columns));
}

Matrix::Matrix(const std::vector<std::vector<Complex>>& matrix) {
    this->rows = (int)matrix.size(); 
    this->columns = (this->rows == 0 ? 0 : (int)(matrix.at(0).size()));
    this->matrix = matrix;  
}

Matrix::Matrix(const std::vector<Complex>& array) {
    this->rows = (int)array.size(); 
    this->columns = (this->rows == 0 ? 0 : 1); 
    this->matrix = std::vector<std::vector<Complex>>(this->rows, std::vector<Complex>(this->columns)); 
    for(int i = 0; i < rows; i++) {
        matrix.at(i).at(0) = array.at(i); 
    }
}

std::pair<int, int> Matrix::dimensions() const{
    return std::make_pair(this->rows, this->columns); 
}

void Matrix::setVal(int row, int column, Complex val) {
    this->matrix.at(row).at(column) = val; 
}

Complex Matrix::getVal(int row, int column) const{
    return this->matrix.at(row).at(column); 
}

std::string Matrix::dimensionsToString() const{
    return "{" + std::to_string(this->rows) + ", " + std::to_string(this->columns) + "}"; 
}

Matrix Matrix::operator -() {
    Matrix result = *(new Matrix(this->rows, this->columns)); 
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->columns; j++) {
            result.matrix.at(i).at(j) = -this->matrix.at(i).at(j); 
        }
    }

    return result; 
}

Matrix Matrix::operator !() {
    Matrix result = *(new Matrix(this->rows, this->columns)); 
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->columns; j++) {
            result.matrix.at(i).at(j) = !this->matrix.at(i).at(j); 
        }
    }
    
    return result; 
}

Matrix Matrix::transpose() {
    Matrix result = *(new Matrix(this->columns, this->rows)); 
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->columns; j++) {
            result.matrix.at(j).at(i) = this->matrix.at(i).at(j); 
        }
    }

    return result; 
}

Matrix Matrix::operator + (Matrix other) {
    try{
        if(this->dimensions() != other.dimensions()) {
            throw(1); 
        }

        Matrix result = *(new Matrix(this->rows, this->columns)); 
        for(int i = 0; i < this->rows; i++) {
            for(int j = 0; j < this->columns; j++) {
                result.matrix.at(i).at(j) = this->matrix.at(i).at(j) + other.matrix.at(i).at(j); 
            }
        }

        return result; 
    }
    catch (int code) {
        std::cerr << "Error: Cannot add Matrices of dimensions " + this->dimensionsToString() + " and " + other.dimensionsToString() << std::endl; 
        exit(code); 
    }
}

void Matrix::operator += (Matrix other) {
    *this = *this + other; 
}

Matrix Matrix::operator - (Matrix other) {
    try {
        if(this->dimensions() != other.dimensions()) {
            throw(1); 
        }

        Matrix result = *(new Matrix(this->rows, this->columns)); 
        for(int i = 0; i < this->rows; i++) {
            for(int j = 0; j < this->columns; j++) {
                result.matrix.at(i).at(j) = this->matrix.at(i).at(j) - other.matrix.at(i).at(j); 
            }
        }

        return result;
    }
    catch(int code) {
        std::cerr << "Error: Cannot subtract Matrices of dimensions " + this->dimensionsToString() + " and " + other.dimensionsToString() << std::endl; 
        exit(code); 
    }
}

void Matrix::operator -= (Matrix other) {
    *this = *this - other; 
}

Matrix Matrix::operator * (Matrix other) {
    try {
        if(this->dimensions().second != other.dimensions().first) {
            throw(1); 
        }
        Matrix result = *(new Matrix(this->rows, other.columns)); 
        for(int i = 0; i < this->rows; i++) {
            for(int k = 0; k < other.columns; k++) {
                for(int j = 0; j < this->columns; j++) {
                    result.matrix.at(i).at(k) += this->matrix.at(i).at(j) * other.matrix.at(j).at(k); 
                }
            }
        }

        return result; 
    }
    catch(int code) {
        std::cerr << "Cannot multiply Matrices of dimensions " + this->dimensionsToString() + " and " + other.dimensionsToString() << std::endl; 
        exit(code); 
    }
 
}

void Matrix::operator *= (Matrix other) {
    *this = *this * other; 
}

Matrix Matrix::tensorProduct(Matrix other) {
    int rows = this->rows * other.rows;
    int columns = this->columns * other.columns; 
    Matrix result = *(new Matrix(rows, columns)); 

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            result.matrix.at(i).at(j) = this->matrix.at(i/other.rows).at(j/other.columns) * other.matrix.at(i % other.rows).at(j % other.columns); 
        }
    }

    return result; 
}
