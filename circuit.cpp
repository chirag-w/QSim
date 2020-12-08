#include "circuit.h"

#include <iostream>
#include <vector>

Circuit::Circuit(std::vector<int> qubit_list)
{
	this->qubits = *(new Qubits(qubit_list));
	this->number_of_qubits = qubit_list.size();
}

Circuit::Circuit(int number_of_qubits)
{
	std::vector<int> qubits;
	for (int i = 0; i < number_of_qubits; i++)
	{
		qubits.push_back(i);
	}
	this->qubits = *(new Qubits(qubits));
	this->number_of_qubits = number_of_qubits;
}

void Circuit::clear()
{
	this->gate_list.clear();
}
