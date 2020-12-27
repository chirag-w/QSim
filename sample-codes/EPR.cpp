#include "circuit.h"

void EPR(Circuit &qc,int q0,int q1){
    qc.apply(H(),q0);
    qc.apply(CX(),q0,q1);
}

int main(){
    Circuit qc(2);
    EPR(qc,0,1);
}