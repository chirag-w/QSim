#include "quantumuser.h"

#include <iostream>
#include <vector>

QuantumUser::QuantumUser(std::string name) {
	this->name = name;
}

Qubits QuantumUser::send(Qubits data, Qubits basis) {
	if(data.getNumQubits() != basis.getNumQubits()) {
		std::cout<<"Basis and data must be same length "<<std::endl;
		exit(0);
	}
	
	std::vector<int> qubits_list;
	std::vector<Complex> state;
	for(int i=0;i<data.getNumQubits();i++) {
		if(!basis.getQubitsList()[i]) {
			if(!data.getQubitsList()[i]) {
				state.push_back(Complex(0, 1));
			}
			else {
				state.push_back(Complex(1, 0));
			}
		}
		else {
			if(!data.getQubitsList()[i]) {
				state.push_back(Complex(0, 1));
			}
			else {
				state.push_back(Complex(1, 0));
			}
		}
		qubits_list.push_back(0);
	}
	Qubits sent = *(new Qubits(qubits_list, state));
	return sent;
}

Qubits QuantumUser::receive(Qubits data, Qubits basis) {
	if(data.getNumQubits() != basis.getNumQubits()) {
		std::cout<<"Basis and data must be same length "<<std::endl;
		exit(0);
	}
	
	std::vector<int> qubits_list;
	for(int i=0;i<data.getNumQubits();i++) {
		if(!basis.getQubitsList()[i]) {
			qubits_list.push_back(data.getQubitsList()[i].measure())
		}
		else {
			data.getQubitsList()[i].hadamard();
			qubits_list.push_back(data.getQubitsList()[i].measure());
		}
	}
	Qubits recieved = *(new Qubits(qubits_list));
	return recieved;
}

