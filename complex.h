/*
This header file provides functionality of complex numbers through class Complex

The following functions are supported:
    1. real() : returns real part of the complex number
    2. imag() : returns imaginary part of the complex number
    3. mod() : returns modulus of the complex number
    4. arg() : returns argument of the complex number (in radians)
    5. argInDegrees() : returns argumnt of the complex number (in degrees)

The following operators are supported (both with other complex numbers and real constants):
    +, -, *, /, +=, -=, *=, /=, <<, >> (output/input)

    Two unary operators are also supported:
    ! (returns conjugate of the complex number)
    - (unary minus, returns negative of a complex number)
*/

#ifndef _COMPLEX_NUMBERS_H_
#define _COMPLEX_NUMBERS_H_

#include<iostream>
#include<cmath>
#include<string>

class Complex{
    double realPart, imaginaryPart;
    public:

    Complex();
    Complex(double real);
    Complex(double real, double imaginary);

    void setReal(double real);
    void setImag(double imag);

    Complex operator + (Complex other);
    void operator += (Complex other);
    Complex operator + (double other);
    void operator += (double other);
    friend Complex operator + (double a, Complex C);

    Complex operator - (Complex other);
    void operator -= (Complex other);
    Complex operator - (double other);
    void operator -= (double other);
    friend Complex operator - (double a, Complex C);

    Complex operator * (Complex other);
    void operator *= (Complex other);
    Complex operator * (double other);
    void operator *= (double other);
    friend Complex operator * (double a, Complex C);

    Complex operator / (Complex other);
    void operator /= (Complex other);
    Complex operator / (double other);
    void operator /= (double other);
    friend Complex operator / (double a, Complex C);

    Complex operator -();
    Complex operator !();

    double real();
    double imag();

    double mod();
    double arg();
    double argInDegrees();

    friend std::ostream& operator << (std::ostream &output, Complex C);

    static double stringToDouble(std::string toConvert);
    friend std::istream& operator >> (std::istream &input, Complex C);
};

#endif
