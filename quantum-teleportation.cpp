#include "circuit.h"

void quantum_teleportation(Circuit &qc){
    qc.apply(CX(), 0, 1);
    qc.apply(H(), 0);
    qc.measure(0);
    qc.measure(1);
    qc.apply(Controlled(X()), 1, 2);
    qc.apply(Controlled(Z()), 0, 2);
}

int main(){
    Circuit qc = Circuit(3);
    std::cout << "Let the qubit to be communicated to Bob is |1>" << std::endl;
    //preparing initial state
    qc.apply(X(), 0);
    //preparing EPR pair
    qc.apply(H(), 1); 
    qc.apply(CX(), 1, 2);
    //teleporting state of qubit 0 to qubit 2
    quantum_teleportation(qc);
    std::cout << "Measurement of state received: " << qc.measure(2) << std::endl;
    return 0;
}
