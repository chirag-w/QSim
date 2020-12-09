#include "circuit.h"
int main(){
    Circuit qc(2);
    std::cout<<"Original state:\n";
    qc.printStateVector();
    qc.apply(H(),{0});
    //std::cout<<"Applied Hadamard"<<std::endl;
    //qc.printStateVector();
    qc.apply(CX(),{0,1});
    std::cout<<"(Hopefully)EPR Pair:\n";
    qc.printStateVector();
}