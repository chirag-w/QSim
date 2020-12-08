#ifndef _CIRCUIT_H
#define _CIRCUIT_H_

#include "complex.h"
#include "matrix.h"
#include "gate.h"
#include "qubits.h"

#include <vector>

class Circuit { 
    Qubits qlist;
	std::vector<Gate> gate_list; 
     

    public: 
    Circuit() = default;
    Circuit(std::vector<int> qubitlist); 
    Circuit(int number_of_qubits); 

    void measure(); 
    void drawCircuit(); 
    void apply(Gate gate);  
    void clear();
    void measureAll();
}; 

#endif
