#include "circuit.h"

#include <iostream> 
#include <vector>

Circuit::Circuit(std::vector<int> qubitlist) {
    this->qlist = *(new Qubits(qubitlist));
}

Circuit::Circuit(int number_of_qubits) {
	std::vector<int> qlist;
	for(int i=0;i<number_of_qubits;i++)
	{
		qlist.push_back(i);
	}
	this->qlist = *(new Qubits(qlist));
}

void Circuit::clear() {
    this->gate_list.clear();
}
