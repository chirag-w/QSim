#include "gate.h"

bool Gate::checkUnitary(int num_qubits, Matrix gate) {
    Matrix result = gate * !gate.transpose(); 
    int gate_size = (1 << num_qubits); 
    bool is_identity = true; 
    for(int i = 0; i < gate_size; i++) {
        for(int j = 0; j < gate_size; j++) {
            if(i == j) {
                if(result.getVal(i, j) != *(new Complex(1))) {
                    is_identity = false; 
                    break; 
                }
            } else {
                if(result.getVal(i, j) != *(new Complex(0))) {
                    is_identity = false; 
                    break; 
                }
            }
        }
    }
    
    /*
    std::cout<<is_identity<<'\n';
    for(int i = 0;i<gate_size;i++){
        for(int j = 0;j<gate_size;j++){
            std::cout<<result.getVal(i,j)<<' ';
        }
        std::cout<<'\n';
    }
    for(int i = 0;i<gate_size;i++){
        for(int j = 0;j<gate_size;j++){
            std::cout<<gate.getVal(i,j)<<' ';
        }
        std::cout<<'\n';
    }
    */
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
Gate H(){
    std::vector<std::vector<Complex>> matrix(2);
    matrix[0] = *(new std::vector<Complex>(2));
    matrix[1] = *(new std::vector<Complex>(2));
    double val1 = 1/sqrt(2);
    Complex v1(val1),v2(-val1);
    matrix[0][0] = matrix[0][1] = matrix[1][0] = v1;
    matrix[1][1] = v2;
    return Gate(1,matrix);
}

Gate X(){
    std::vector<std::vector<Complex>> matrix(2);
    matrix[0] = *(new std::vector<Complex>(2));
    matrix[1] = *(new std::vector<Complex>(2));
    Complex v1(1),v2(0);
    matrix[0][0] = matrix[1][1] = v2;
    matrix[0][1] = matrix[1][0] = v1;
    return Gate(1,matrix);
}

Gate Y(){
    std::vector<std::vector<Complex>> matrix(2);
    matrix[0] = *(new std::vector<Complex>(2));
    matrix[1] = *(new std::vector<Complex>(2));
    Complex v1(0,1),v2(0);
    matrix[0][0] = matrix[1][1] = v2;
    matrix[0][1] = -v1;
    matrix[1][0] = v1;
    return Gate(1,matrix);
}
Gate Z(){
    std::vector<std::vector<Complex>> matrix(2);
    matrix[0] = *(new std::vector<Complex>(2));
    matrix[1] = *(new std::vector<Complex>(2));
    Complex v1(1),v2(0);
    matrix[1][0] = matrix[0][1] =  v2;
    matrix[0][0] = v1;
    matrix[1][1] = -v1;
    return Gate(1,matrix);
}
Gate I(){
    std::vector<std::vector<Complex>> matrix(2,std::vector<Complex>(2));
    Complex v1(1);
    matrix[0][0] = matrix[1][1] = 1;
    return Gate(1,matrix);
}
Gate CX(){
    std::vector<std::vector<Complex>> matrix(4,std::vector<Complex>(4));
    Complex v1(1);
    matrix[0][0] = matrix[1][1] = matrix[2][3] = matrix[3][2] = v1;
    return Gate(2,matrix);
}

Gate U(double theta,double phi,double lambda){
    std::vector<std::vector<Complex>> matrix(2,std::vector<Complex>(2));
    Complex Cos(cos(theta/2)),Sin(sin(theta/2)),Phi(cos(phi),sin(phi)),Lambda(cos(lambda),sin(lambda));
    matrix[0][0] = Cos;
    matrix[0][1] = -Lambda *Sin;
    matrix[1][0] = Phi * Sin;
    matrix[1][1] = Phi * Lambda * Cos;
    return Gate(1,matrix); 

}
