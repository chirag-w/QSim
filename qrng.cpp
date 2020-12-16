#include "circuit.h"

// Generates a random number of n bits
int generateRandomNumber(int bits){
    Circuit qc(1);
    int num = 0;
    for (int i=0 ; i<bits ; i++){
        qc.apply(H(), {0});
        num = 2*num + qc.measure(0);
    }
    return num;
}

int main(){
    std::cout << "Enter the number of bits" << std::endl;
    int n;
    std::cin >> n;
    int number = generateRandomNumber(n);
    std::cout << n << " bit number is: " << number << std::endl;
    return 0;
}
