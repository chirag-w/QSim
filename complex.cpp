#include "complex.h"
#define eps 1e-14


Complex::Complex(){
    realPart = imaginaryPart = 0.0;
}
Complex::Complex(double real){
    realPart = real;
    imaginaryPart = 0.0;
}
Complex::Complex(double real, double imaginary){
    realPart = real;
    imaginaryPart = imaginary;
}

void Complex::setReal(double real){
    realPart = real;
}
void Complex::setImag(double imag){
    imaginaryPart = imag;
}

bool Complex::operator == (Complex other){
    return (fabs(other.realPart-realPart)<eps && fabs(other.imaginaryPart-imaginaryPart)<eps);
}
bool Complex::operator != (Complex other){
    return !(*this == other);
}


Complex Complex::operator + (Complex other){
    return Complex(realPart + other.realPart, imaginaryPart + other.imaginaryPart);
}
void Complex::operator += (Complex other){
    *this = *this + other;
}
Complex Complex::operator + (double other){
    return Complex(realPart + other, imaginaryPart);
}
void Complex::operator += (double other){
    realPart += other;
}
Complex operator + (double a, Complex C){
    return C+a;
}
    


Complex Complex::operator - (Complex other){
    return Complex(realPart - other.realPart, imaginaryPart - other.imaginaryPart);
}
void Complex::operator -= (Complex other){
    *this = *this - other;
}
Complex Complex::operator - (double other){
    return Complex(realPart - other, imaginaryPart);
}
void Complex::operator -= (double other){
    realPart -= other;
}
Complex operator - (double a, Complex C){
    return -(C-a);
}

Complex Complex::operator * (Complex other){
    return Complex(realPart*other.realPart - imaginaryPart*other.imaginaryPart,
                   realPart*other.imaginaryPart + imaginaryPart*other.realPart);
}
void Complex::operator *= (Complex other){
    *this = *this * other;
}
Complex Complex::operator * (double other){
    return Complex(realPart*other, imaginaryPart*other);
}
void Complex::operator *= (double other){
    realPart *= other;
    imaginaryPart *= other;
}
Complex operator * (double a, Complex C){
    return C*a;
}


Complex Complex::operator / (Complex other){
    Complex conjugate = !other;
    conjugate *= *this;
    double modSquare = other.mod() * other.mod();
    conjugate.realPart /= modSquare;
    conjugate.imaginaryPart /= modSquare;
    return conjugate;
}
void Complex::operator /= (Complex other){
    *this = *this / other;
}
Complex Complex::operator / (double other){
    return Complex(realPart/other, imaginaryPart/other);
}
void Complex::operator /= (double other){
    realPart /= other;
    imaginaryPart /= other;
}
Complex operator / (double a, Complex C){
    return Complex(a)/C;
}

    

Complex Complex::operator -(){
    return Complex(-realPart, -imaginaryPart);
}
Complex Complex::operator !(){
    return Complex(realPart, -imaginaryPart);
}

double Complex::real(){
    return realPart;
}
double Complex::imag(){
    return imaginaryPart;
}

double Complex::mod(){
    return sqrt(realPart*realPart + imaginaryPart*imaginaryPart);
}

double Complex::arg(){
    if(realPart == 0.0){
        if(imaginaryPart == 0.0)
            return 0.0;
        else
            return imaginaryPart/fabs(imaginaryPart) * M_PI/2.0;
    }
    if(imaginaryPart == 0.0)
        return 0 + (realPart<0 ? M_PI : 0);
    double adjust = 0.0;
    if(realPart < 0){
        if(imaginaryPart < 0){
            adjust = -M_PI;
        }
        else{
            adjust = M_PI;
        }
    }
    return atan(imaginaryPart/realPart) + adjust;
}
double Complex::argInDegrees(){
    return (this->arg())*(180.0/M_PI);
}

std::ostream& operator << (std::ostream &output, Complex C){
    output << C.real() << (C.imag()>=0 ? " + " : " - " ) << fabs(C.imag()) << "i";
    return output;
}


static double stringToDouble(std::string toConvert){
    int invert = (toConvert[0] == '-'? -1: 1);
    bool something = false;
    bool before = true;
    double answer = 0.0;
    double mul = 0.1;
    for(int i=0; i<toConvert.length(); i++){
        if(toConvert[i] == '.') {
            before = false;
            continue;
        }
        else if(toConvert[i] == '-' || toConvert[i] == '+' || toConvert[i] == 'i'){
            continue;
        }
        else if(before){
            something = true;
            answer *= 10.0;
            answer += (double)(toConvert[i]-'0');
        }
        else{
            something = true;
            answer += (double)(toConvert[i]-'0')*mul;
            mul/=10;
        }
    }
    if(!something) answer = 1.0;
    return answer*invert;
}

std::istream& operator >> (std::istream &input, Complex &C){   
    std::string numberAsString;
    getline(input, numberAsString);
    std::string noSpacesNumber = "";
    char lastNonSpace = '?';
    for(int i=0; i<numberAsString.length(); i++) {
        char c = numberAsString[i];
        if(c!='.' && c!='+' && c!='-' && c!=' ' && (c<'0' || c>'9') && c!='i') 
            return input;
        if(c != ' ') {
            noSpacesNumber += c;
            lastNonSpace = c;
        }
        else{
            if(lastNonSpace == '+' || lastNonSpace == '?' || lastNonSpace == 'i' || lastNonSpace == '-') 
                continue;
            while(numberAsString[i]==' ' && i<numberAsString.length()) 
                ++i;
            if(i == numberAsString.length() || numberAsString[i]=='+' || numberAsString[i]=='-'){
                --i; 
                continue;
            }
            else 
                return input;
        }
    }
    bool sign = true;
    bool good = true;
    int times = 0;
    int appeared = -1;
    for(int i=((noSpacesNumber[0]=='-'||noSpacesNumber[0]=='+')?1:0); i<noSpacesNumber.length(); i++)
    {
        if(noSpacesNumber[i] == '.' && ((times>0 && appeared==-1) || (times>1)))
            return input;
        else if(noSpacesNumber[i]=='.' && (i==0 || noSpacesNumber[i-1]>'9' || noSpacesNumber[i-1]<'0' || i==noSpacesNumber.size()-1 || noSpacesNumber[i+1]>'9' || noSpacesNumber[i+1]<'0'))
            return input;
        else if(noSpacesNumber[i]=='.')
            ++times;
        if((noSpacesNumber[i]=='+' || noSpacesNumber[i]=='-') && appeared!=-1) 
            return input;
        else if(noSpacesNumber[i] == '+') {
            sign = true;
            appeared = i;
            times = 1;
        } 
        else if(noSpacesNumber[i] == '-'){
            sign = false;
            appeared = i;
            times = 1;
        }
    }
    if(noSpacesNumber.back()!='i'){
        C.setImag(0.0);
        C.setReal( stringToDouble(noSpacesNumber));
    }
    else if(appeared==-1){
        C.setImag(stringToDouble(noSpacesNumber));
        C.setReal(0.0);
    }
    else{
        C.setReal(stringToDouble(noSpacesNumber.substr(0, appeared)));
        C.setImag(stringToDouble(noSpacesNumber.substr(appeared)));
    }   
    return input;
}
