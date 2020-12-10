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
    std::vector<std::pair<Gate, std::vector<int>>> gate_list;
    std::vector<std::pair<Gate, std::vector<int>>> physical_gate_list;
    int number_of_qubits;
    void add(Gate gate, int q0);
    void add(Gate gate, int q0, int q1);

public:
    Circuit() = default;
    Circuit(std::vector<int> qubit_list);
    Circuit(int number_of_qubits);

    std::vector<int> measure(std::vector<int> qubits_list);
    int measure(int qubit);
    void drawCircuit();
    void apply(Gate gate, std::vector<int> qubits_list);
    void clear();
    std::vector<int> measureAll();
    void printStateVector();
};

#endif
