#include "qubits.h"

#include <iostream> 

bool Qubits::checkMod(Matrix state) {
    int state_size = (int)state.dimensions().first;
    Complex mod_sum = *(new Complex(0)); 
    for(int i = 0; i < state_size; i++) {
        mod_sum += pow(state.getVal(i, 0).mod(), 2); 
    } 
    return mod_sum == *(new Complex(1)); 
}

Qubits::Qubits(std::vector<int> qubits_list) {
    num_qubits = (int)qubits_list.size(); 
    int state_size = (1 << num_qubits); 
    state = *(new Matrix(state_size, 1));
    state.setVal(0, 0, *(new Complex(1)));  
    this->qubits_list = qubits_list; 
}

Qubits::Qubits(std::vector<int> qubits_list, Matrix state) {
    try{
        num_qubits = (int)qubits_list.size(); 
        int state_size = (1 << num_qubits); 
        if(state.dimensions() != std::make_pair(state_size, 1) || !checkMod(state)) {
            throw(1); 
        }

        this->qubits_list = qubits_list; 
        this->state = state; 
    }
    catch (int code) {
        std::cout << "Error: Invalid state Matrix" << std::endl; 
        exit(code); 
    }
}

Qubits::Qubits(std::vector<int> qubits_list, std::vector<Complex> state_vector) {
    try{
        num_qubits = (int)qubits_list.size(); 
        int state_size = (1 << num_qubits); 
        Matrix state = *(new Matrix(state_vector)); 

        if(state.dimensions() != std::make_pair(state_size, 1) || !checkMod(state)) {
            throw(1); 
        }

        this->qubits_list = qubits_list; 
        this->state = state; 
    }   
    catch (int code) {
        std::cout << "Error: Invalid state vector" << std::endl; 
        exit(code); 
    }
}

int Qubits::getNumQubits() {
    return this->num_qubits; 
}

std::vector<int> Qubits::getQubitsList() {
    return this->qubits_list; 
}

void Qubits::applyGate(Gate gate) {
    try {
        if(this->num_qubits != gate.num_qubits) {
            throw(1); 
        }

        this->state = gate.gate * this->state; 
    }
    catch (int code) {
        std::cout << "Error: Cannot apply specified gate to this state" << std::endl; 
        exit(code); 
    }
}

void Qubits::printState() {
    int state_size = (1 << num_qubits); 
    for(int i = 0; i < state_size; i++) {
        std::cout << state.getVal(i, 0) << "\n"; 
    }
}

