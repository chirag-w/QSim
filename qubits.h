/*
This header file provides functionality for representing the state of qubits using Qubits class. 

The following functions are supported: 
    - getNumQubits() - returns number of qubits represented by the object
    - getQubitsList() - returns std::vector<int> of indices of qubits represented by the oject
    - applyGate(Gate gate) - applies Gate to state Matrix of the object
    - printState() - prints current state of the qubits
*/

#ifndef _QUBITS_H_
#define _QUBITS_H_

#include "complex.h"
#include "matrix.h"
#include "gate.h"

#include <vector>

class Qubits {
    int num_qubits; 
    std::vector<int> qubits_list; 
    Matrix state; 

    bool checkMod(Matrix state); 

    public: 
    Qubits(std::vector<int> qubits_list); 
    Qubits(std::vector<int> qubits_list, Matrix state); 
    Qubits(std::vector<int> qubits_list, std::vector<Complex> state_vector); 

    int getNumQubits(); 
    std::vector<int> getQubitsList(); 
    void applyGate(Gate gate); 
    void printState(); 
    
}; 

#endif
