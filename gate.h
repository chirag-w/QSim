/*
This header file provides functionality of quantum Gates respresented as type Matrices. 

The following functions are supported: 
    - getNumQubits : returns type int of number of qubits 
    - printGate() : prints the current gate configuration
*/ 

#ifndef _GATE_H_
#define _GATE_H_

#include "matrix.h" 

class Gate {
    Matrix gate; 
    int num_qubits; 

    friend class Qubits; 
    
    bool checkUnitary(int num_qubits, Matrix gate); 

    public: 
    Gate() = default;
    Gate(int num_qubits); 
    Gate(int num_qubits, Matrix gate);  
    Gate(int num_qubits, std::vector<std::vector<Complex>> gate); 

    int getNumQubits(); 
    void printGate(); 
}; 

Gate H();
Gate X();
Gate Y();
Gate Z();
#endif
