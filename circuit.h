#ifndef _CIRCUIT_H
#define _CIRCUIT_H_

#include "complex.h"
#include "matrix.h"
#include "gate.h"
#include "qubit.h"

#include <vector>

class Circuit {
    std::vector<Gate> gate_list; 
    Qubit qlist; 
     

    public: 
    Circuit(std::vector<int> qubits_list); 
    Circuit(int number_of_qubits); 

    void measure(); 
    void drawCircuit(); 
    void apply(Gate gate);  
    
}; 

