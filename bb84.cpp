#include "qubits.h"
#include "quantumuser.h"

#include <vector>
#include <iostream>

Qubits generate_random_bits(int N) {
	std::vector<int> aux;
	for(int i=0;i<N;i++)
	{
		aux.push_back(rand()%2);
	}
	Qubits q = *(new Qubits(aux));
	return q;
}

bool QKD(int N, bool eve_present=false) {
	Qubits alice_basis = generate_random_bits(N);
	Qubits alice_bits = generate_random_bits(N);
	QuantumUser *alice = new QuantumUser("Alice");
	Qubits alice_qubits = alice->send(alice_bits,alice_basis);
	if(eve_present){
		Qubits eve_basis = generate_random_bits(N);
		QuantumUser *eve = new QuantumUser("Eve");
		Qubits eve_bits = eve->receive(alice_qubits,eve_basis);
		alice_qubits = eve->send(eve_bits,eve_basis);
	}
	Qubits bob_basis = generate_random_bits(N);
	QuantumUser *bob = new QuantumUser("Bob");
	Qubits bob_bits = bob->receive(alice_qubits,bob_basis);
	std::vector<int> alice_key;
	std::vector<int> bob_key; 
	bool key;
	int length;
	for(int i=0;i<N;i++) {
		if (alice_basis.getQubitsList()[i] == bob_basis.getQubitsList()[i]) {
			alice_key.push_back(alice_bits.getQubitsList()[i]);
			bob_key.push_back(bob_bits.getQubitsList()[i]);
		}
	}
	if (alice_key != bob_key) {
		key = false;
		length = 0;
		std::cout<<"Encription key mismatch, eve is present."<<std::endl;
	}
	else {
		key = true;
		length = bob_key.size();
		std::cout<<"Successfully exchanged key!"<<std::endl;
		std::cout<<"Key Length: "<<length<<std::endl;
	}
	return key;
}
