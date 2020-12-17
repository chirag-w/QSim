/*
This header file provides functionality of all quantum circuits, using the Circuit class
A circuit can have at most 10 qubits. More details for this can be found in the architecture description

The following functions are supported:
    measure(std::vector<int> qubits_list) : returns measurement outcomes for all qubits in qubits_list as std::vector<int>
    measure(int qubit) : returns measurement outcome of qubit
    getNumQubits() : returns number of qubits in the circuit
    drawCircuit() : 
    apply(Gate gate, std::vector<int> qubits_list) : applies gate to the qubits in qubits_list. Currently, only 1 and 2 qubit gates are supported
    apply(Gate gate,int q0); : applies gate to qubit q0
    apply(Gate gate,int q0,int q1) : applies gate to qubits q0 and q1
    clear() : removes all gates from the circuit, and sets all qubits to |0>
    measureAll() : measures all qubits in the circuit and returns measurement outcomes as std::vector<int>
    printStateVector() :: prints the vector representing the current state of all qubits in the circuit

*/
#ifndef _CIRCUIT_H
#define _CIRCUIT_H_

#include "complex.h"
#include "matrix.h"
#include "gate.h"
#include "qubits.h"

#include <vector>

class Circuit
{
    Qubits qubits;
    std::vector<std::pair<Gate, std::vector<int>>> physical_gate_list;
    int number_of_qubits, number_of_physical_qubits;
    void add(Gate gate, int q0);
    void add(Gate gate, int q0, int q1);
    std::vector<int> swapTargets(int q0, int q1);
    bool inContact(int q0, int q1);
    void SWAP(int q0, int q1);

public:
    std::vector<std::pair<Gate, std::vector<int>>> gate_list;
    Circuit() = default;
    //Circuit(std::vector<int> qubit_list);
    Circuit(int number_of_qubits);

    std::vector<int> measure(std::vector<int> qubits_list);
    int measure(int qubit);
    int getNumQubits();
    void drawCircuit();
    void drawCircuit(std::string file_name);
    void apply(Gate gate, std::vector<int> qubits_list);
    void apply(Gate gate, int q0);
    void apply(Gate gate, int q0, int q1);
    void clear();
    std::vector<int> measureAll();
    void printStateVector();
    void drawPhysicalCircuit(std::string file_name);
    void drawPhysicalCircuit();
};

#endif
