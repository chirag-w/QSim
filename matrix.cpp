#include "matrix.h"
#ifdef __AVX__
  #include <immintrin.h>
#else
  #warning AVX is not available. Code will not compile!
#endif

Matrix::Matrix(int rows, int columns) {
    this->rows = rows; 
    this->columns = columns; 
    this->matrix = std::vector<std::vector<Complex>>(rows, std::vector<Complex>(columns));
}

Matrix::Matrix(int rows, int columns,bool identity) {
    this->rows = rows; 
    this->columns = columns; 
    this->matrix = std::vector<std::vector<Complex>>(rows, std::vector<Complex>(columns));
    if(identity && rows==columns){
        for(int i = 0;i<rows;i++){
            matrix.at(i).at(i) = *(new Complex(1));
        }
    }
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
        int avx_cols = other.columns - (other.columns % 4);
        if(avx_cols > 0) { 
            double result_real[this->rows][avx_cols] = {};
            double result_imag[this->rows][avx_cols] = {}; 

            for(int i = 0; i < this->rows; i++) { 
                for(int k = 0; k < avx_cols/4; k++) {
                    __m256d Z_real = _mm256_set1_pd(0.0);
                    __m256d Z_imag = _mm256_set1_pd(0.0);
                    for(int j = 0; j < this->columns; j++) {
                        __m256d X_real = _mm256_set1_pd(this->matrix.at(i).at(j).real()); 
                        __m256d X_imag = _mm256_set1_pd(this->matrix.at(i).at(j).imag()); 
                        __m256d Y_real = _mm256_set_pd(other.matrix.at(j).at(4*k+3).real(), other.matrix.at(j).at(4*k+2).real(), other.matrix.at(j).at(4*k+1).real(), other.matrix.at(j).at(4*k).real()); 
                        __m256d Y_imag = _mm256_set_pd(other.matrix.at(j).at(4*k+3).imag(), other.matrix.at(j).at(4*k+2).imag(), other.matrix.at(j).at(4*k+1).imag(), other.matrix.at(j).at(4*k).imag()); 
                        Z_real = _mm256_add_pd(Z_real, _mm256_sub_pd(_mm256_mul_pd(X_real, Y_real), _mm256_mul_pd(X_imag, Y_imag)));
                        Z_imag = _mm256_add_pd(Z_imag, _mm256_add_pd(_mm256_mul_pd(X_real, Y_imag), _mm256_mul_pd(X_imag, Y_real))); 
                    }
                    _mm256_storeu_pd(&(result_real[i][4*k]), Z_real); 
                    _mm256_storeu_pd(&(result_imag[i][4*k]), Z_imag); 
                }
            } 

            for(int i = 0; i < this->rows; i++) {
                for(int j = 0; j < avx_cols; j++) {
                    result.matrix.at(i).at(j) = Complex(result_real[i][j], result_imag[i][j]); 
                }
            }
        }
        for(int i = 0; i < this->rows; i++) {
            for(int k = avx_cols; k < other.columns; k++) {
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
