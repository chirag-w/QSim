#include "circuit.h"
#include "qubits.h"
int main(){
    std::vector<int> qubit_list(1);
    Qubits qc(qubit_list);
    qc.printState();
    qc.applyGate(X());
    qc.applyGate(U(M_PI/2,0,0));
    qc.printState();
}