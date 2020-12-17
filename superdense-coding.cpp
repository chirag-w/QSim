#include "circuit.h"

void superdense_coding(int a, int b){
    Circuit qc = Circuit(2);
    qc.apply(H(), 0);
    qc.apply(CX(), 0 ,1);
    if (a) qc.apply(Z(), 0);
    if (b) qc.apply(X(), 0);
    qc.apply(CX(), 0, 1);
    qc.apply(H(), 0);
    std::cout << "Bits received by Bob are: " << qc.measure(0) << qc.measure(1) << std::endl;
}

int main(){
    int a, b;
    std::cout << "Enter value of 1st bit" << std::endl;
    std::cin >> a;
    std::cout << "Enter value of 2nd bit" << std::endl;
    std::cin >> b;
    superdense_coding(a, b);
}
