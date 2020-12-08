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
    std::vector<Gate> gate_list;
    int number_of_qubits;

public:
    Circuit() = default;
    Circuit(std::vector<int> qubit_list);
    Circuit(int number_of_qubits);

    void measure();
    void drawCircuit();
    void apply(Gate gate);
    void clear();
    std::vector<int> measureAll();
};

#endif
