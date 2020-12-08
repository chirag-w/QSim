#include "circuit.h"

#include <iostream> 


Circuit::Circuit(std::vector<int> qubits_list) {
    qlist = new Qubit(qubits_list);
}

Circuit::Circuit(int number_of_qubits) {
	vector<int> qubits_list (number_of_qubits);
	for(int i=0;i<number_of_qubits;i++)
	{
		qubits_list.push_back(i);
	}
	qlist = new Qubit(qubits_list);
}
