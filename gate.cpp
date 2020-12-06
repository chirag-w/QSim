#include "gate.h"

bool Gate::checkUnitary(int num_qubits, Matrix gate) {
    Matrix result = gate * gate.transpose(); 
    int gate_size = (1 << num_qubits); 
    bool is_identity = true; 
    for(int i = 0; i < gate_size; i++) {
        for(int j = 0; j < gate_size; j++) {
            if(i == j) {
                if(gate.getVal(i, j) != *(new Complex(1))) {
                    is_identity = false; 
                    break; 
                }
            } else {
                if(gate.getVal(i, j) != *(new Complex(0))) {
                    is_identity = false; 
                    break; 
                }
            }
        }
    }

    return is_identity; 
}

Gate::Gate(int num_qubits) {
    this->num_qubits = num_qubits; 
    int gate_size = (1 << num_qubits); 
    this->gate = *(new Matrix(gate_size, gate_size)); 
    for(int i = 0; i < gate_size; i++) {
        gate.setVal(i, i, *(new Complex(1))); 
    }
}

Gate::Gate(int num_qubits, Matrix gate) {
    try {
        if((gate.dimensions() != std::make_pair(1 << num_qubits, 1 << num_qubits)) || !(checkUnitary(num_qubits, gate))) {
            throw(1); 
        }

        this->num_qubits = num_qubits; 
        this->gate = gate; 
    } 
    catch (int code) {
        std::cerr << "Error: Invalid Matrix for type Gate" << std::endl; 
        exit(code); 
    }
}

Gate::Gate(int num_qubits, std::vector<std::vector<Complex>> gate_matrix) {
    try {
        Matrix gate = *(new Matrix(gate_matrix)); 
        if((gate.dimensions() != std::make_pair(1 << num_qubits, 1 << num_qubits)) || !(checkUnitary(num_qubits, gate))) {
            throw(1); 
        }

        this->num_qubits = num_qubits; 
        this->gate = gate; 
    } 
    catch (int code) {
        std::cerr << "Error: Invalid Matrix for type Gate" << std::endl; 
        exit(code); 
    }
}

int Gate::getNumQubits() {
    return this->num_qubits; 
}

void Gate::printGate() {
    int gate_size = (1 << this->num_qubits); 
    for(int i = 0; i < gate_size; i++) {
        for(int j = 0; j < gate_size; j++) {
            std::cout << this->gate.getVal(i, j) << " "; 
        }
        std::cout << "\n"; 
    }
}
