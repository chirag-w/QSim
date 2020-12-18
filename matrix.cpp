#ifdef __AVX__ 
    #include <immintrin.h>
#endif
#include "matrix.h"
#include<thread>

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

        std::vector<std::vector<double>> A(this->rows, std::vector<double>(this->columns));
        std::vector<std::vector<double>> B(this->rows, std::vector<double>(this->columns));  
        std::vector<std::vector<double>> C_T(other.columns, std::vector<double>(other.rows));
        std::vector<std::vector<double>> D_T(other.columns, std::vector<double>(other.rows));

        std::vector<std::vector<double>> real_part(this->rows, std::vector<double>(other.columns));
        std::vector<std::vector<double>> imaginary_part(this->rows, std::vector<double>(other.columns));
        
        for(int i = 0; i < this->rows; i++) {
            for(int j = 0; j < this->columns; j++) {
                A[i][j] = this->matrix.at(i).at(j).real();
                B[i][j] = this->matrix.at(i).at(j).imag(); 
            }
        }

        for(int i = 0; i < other.rows; i++) {
            for(int j = 0; j < other.columns; j++) {
                C_T[j][i] = other.matrix.at(i).at(j).real();
                D_T[j][i] = other.matrix.at(i).at(j).imag(); 
            }
        }

        int THREADS = 4;
        int SIZE = this->rows;

    #ifdef __AVX__
        auto multiply = [this, other, C_T, D_T, A, B](int start, int end, std::vector<std::vector<double>> &real_part,  std::vector<std::vector<double>> &imaginary_part) {
            for(int i=start; i<end; i++) {
                for(int k = 0; k < other.columns; k++) {
                    int j = 0; 
                    for(; j+3 < this->columns; j += 4) {
                        __m256d A_avx = _mm256_set_pd(A[i][j+3], A[i][j+2], A[i][j+1], A[i][j]);
                        __m256d B_avx = _mm256_set_pd(B[i][j+3], B[i][j+2], B[i][j+1], B[i][j]); 
                        __m256d C_T_avx = _mm256_set_pd(C_T[k][j+3], C_T[k][j+2], C_T[k][j+1], C_T[k][j]);
                        __m256d D_T_avx = _mm256_set_pd(D_T[k][j+3], D_T[k][j+2], D_T[k][j+1], D_T[k][j]); 
                        
                        __m256d to_add_real = _mm256_sub_pd(_mm256_mul_pd(A_avx, C_T_avx), _mm256_mul_pd(B_avx, D_T_avx));
                        __m256d to_add_imag = _mm256_add_pd(_mm256_mul_pd(A_avx, D_T_avx), _mm256_mul_pd(B_avx, C_T_avx));

                        __m128d to_add_real_low  = _mm256_castpd256_pd128(to_add_real);
                        __m128d to_add_real_high = _mm256_extractf128_pd(to_add_real, 1); 
                        to_add_real_low  = _mm_add_pd(to_add_real_low, to_add_real_high);    
                        __m128d real_high64 = _mm_unpackhi_pd(to_add_real_low, to_add_real_low);
                        real_part[i][k] +=  _mm_cvtsd_f64(_mm_add_sd(to_add_real_low, real_high64));

                        __m128d to_add_imag_low  = _mm256_castpd256_pd128(to_add_imag);
                        __m128d to_add_imag_high = _mm256_extractf128_pd(to_add_imag, 1); 
                        to_add_imag_low  = _mm_add_pd(to_add_imag_low, to_add_imag_high);    
                        __m128d imag_high64 = _mm_unpackhi_pd(to_add_imag_low, to_add_imag_low);
                        imaginary_part[i][k] +=  _mm_cvtsd_f64(_mm_add_sd(to_add_imag_low, imag_high64));
                    }

                    for(; j < this->columns; j++) {
                        real_part[i][k] += A[i][j] * C_T[k][j] - B[i][j] * D_T[k][j];
                        imaginary_part[i][k] += A[i][j] * D_T[k][j] + B[i][j] * C_T[k][j]; 
                    }
                }
            }
        };

    #else
        auto multiply = [this, other, C_T, D_T, A, B](int start, int end, std::vector<std::vector<double>> &real_part,  std::vector<std::vector<double>> &imaginary_part) {
            for(int i=start; i<end; i++) {
                for(int k = 0; k < other.columns; k++) {
                    #pragma omp simd
                    for(int j = 0; j < this->columns; j++) {
                        real_part[i][k] += A[i][j] * C_T[k][j] - B[i][j] * D_T[k][j];
                        imaginary_part[i][k] += A[i][j] * D_T[k][j] + B[i][j] * C_T[k][j]; 

                    }
                }
            }
        };
        #endif

        std::thread threads[THREADS+1];
        for(int i=0; i<THREADS; ++i){
            threads[i] = std::thread(multiply, i*(SIZE/THREADS), (i+1)*(SIZE/THREADS), std::ref(real_part), std::ref(imaginary_part));
        }
        threads[THREADS] = std::thread(multiply, THREADS*(SIZE/THREADS), SIZE, std::ref(real_part), std::ref(imaginary_part));
        for(int i=0; i<=THREADS; i++) {
            threads[i].join();
        }

        Matrix result = *(new Matrix(this->rows, other.columns)); 
        for(int i = 0; i < this->rows; i++) {
            for(int j = 0; j < other.columns; j++) {
                result.matrix.at(i).at(j) = Complex(real_part[i][j], imaginary_part[i][j]); 
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
