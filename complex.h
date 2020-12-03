/*
This header file provides functionality of complex numbers through class Complex

The following functions are supported:
    1. real() : returns real part of the complex number
    2. imag() : returns imaginary part of the complex number
    3. mod() : returns modulus of the complex number
    4. arg() : returns argument of the complex number (in radians)
    5. argInDegrees : returns argumnt of the complex number (in degrees)

The following operators are supported:
    +, -, *, /, +=, -=, *=, /=

    Two unary operators are also supported:
    ! (returns conjugate of the complex number)
    - (unary minus, returns negative of a complex number)
*/

#ifndef _COMPLEX_NUMBERS_H_
#define _COMPLEX_NUMBERS_H_

#include<iostream>
#include<cmath>

class Complex
{
    double realPart, imaginaryPart;
    public:

    Complex()
    {
        realPart = imaginaryPart = 0.0;
    }
    Complex(double real, double imaginary)
    {
        realPart = real;
        imaginaryPart = imaginary;
    }

    Complex operator + (Complex &other)
    {
        return Complex(realPart + other.realPart, imaginaryPart + other.imaginaryPart);
    }
    void operator += (Complex &other)
    {
        *this = *this + other;
    }

    Complex operator - (Complex &other)
    {
        return Complex(realPart - other.realPart, imaginaryPart - other.imaginaryPart);
    }
    void operator -= (Complex &other)
    {
        *this = *this - other;
    }

    Complex operator * (Complex &other)
    {
        return Complex(realPart*other.realPart - imaginaryPart*other.imaginaryPart,
                       realPart*other.imaginaryPart + imaginaryPart*other.realPart);
    }
    void operator *= (Complex &other)
    {
        *this = *this * other;
    }

    Complex operator / (Complex &other)
    {
        Complex conjugate = !other;
        conjugate *= *this;
        double modSquare = other.mod() * other.mod();
        conjugate.realPart /= modSquare;
        conjugate.imaginaryPart /= modSquare;
        return conjugate;
    }
    void operator /= (Complex &other)
    {
        *this = *this / other;
    }

    Complex operator -()
    {
        return Complex(-realPart, -imaginaryPart);
    }
    Complex operator !()
    {
        return Complex(realPart, -imaginaryPart);
    }

    double real()
    {
        return realPart;
    }
    double imag()
    {
        return imaginaryPart;
    }

    double mod()
    {
        return sqrt(realPart*realPart + imaginaryPart*imaginaryPart);
    }

    double arg()
    {
        if(realPart == 0.0)
        {
            if(imaginaryPart == 0.0)
                return 0.0;
            else
                return imaginaryPart/fabs(imaginaryPart) * M_PI/2.0;
        }
        if(imaginaryPart == 0.0)
        {
            return 0 + (realPart<0 ? M_PI : 0);
        }
        double adjust = 0.0;
        if(realPart < 0)
        {
            if(imaginaryPart < 0)
            {
                adjust = -M_PI;
            }
            else
            {
                adjust = M_PI;
            }
        }
        return atan(imaginaryPart/realPart) + adjust;
    }
    double argInDegrees()
    {
        return (this->arg())*(180.0/M_PI);
    }
};

#endif
