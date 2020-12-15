#ifndef _CIRCUIT_H
#define _CIRCUIT_H_

#include "complex.h"
#include "matrix.h"
#include "gate.h"
#include "qubits.h"

class QuantumUser {
	std::string name;
	
	public :
	QuantumUser() = default;
	QuantumUser(std::string name);
	
	Qubits send(Qubits data, Qubits basis);
	Qubits receive(Qubits data, Qubits basis);
	
};

#endif
