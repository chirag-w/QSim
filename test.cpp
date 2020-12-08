#include "circuit.h"
#include "qubits.h"
int main(){
    std::vector<int> qubit_list(1);
    Qubits qc(qubit_list);
    qc.printState();
    std::cout<<'\n';
    qc.applyGate(H());
    qc.printState();
    std::cout<<'\n';
    qc.applyGate(Z());
    qc.printState();
    qc.applyGate(Z());
    std::cout<<'\n';
    qc.printState();
}