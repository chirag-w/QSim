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
	this->physical_gate_list.clear();
}

void Circuit::add(Gate gate,int q0){
	Matrix m2 = gate.getMatrix();	
	int num1 = q0;
	int num2 = number_of_qubits - q0-1;
	Matrix m1(1<<num1,1<<num1,true),m3(1<<num2,1<<num2,true);
	Matrix m = m1.tensorProduct(m2).tensorProduct(m3);
	physical_gate_list.push_back({gate,{q0}});
	qubits.applyGate(Gate(number_of_qubits,m));
}

void Circuit::add(Gate gate,int q0,int q1){
	/*
	std::cout<<q0<<' '<<q1<<'\n';
	gate.printGate();
	*/
	Matrix m0,m1[4],m2,m3[4],m4,m = gate.getMatrix();
	Complex one(1);
	if(q1<q0){
		std::swap(q0,q1);
		for(int i = 0;i<4;i++){
			Complex c = m.getVal(i,1);
			m.setVal(i,1,m.getVal(i,2));
			m.setVal(i,2,c);
		}
	}
	int num1 = q0;
	int num2 = q1-q0-1;
	int num3 = number_of_qubits - q1-1;
	m0 = *(new Matrix(1<<num1,1<<num1,true));
	m2 = *(new Matrix(1<<num2,1<<num2,true));
	m4 = *(new Matrix(1<<num3,1<<num3,true));
	for(int i = 0;i<4;i++){
		m1[i] = *(new Matrix(2,2));
		m1[i].setVal(i/2,i%2,one);
	}
	for(int i = 0;i<4;i++){
		m3[i] = *(new Matrix(2,2));
		for(int j = 0;j<4;j++){
			m3[i].setVal(j/2,j%2,m.getVal(2*(i/2)+(j/2),2*(i%2)+(j%2)));
		}
	}
	Matrix M = m1[0].tensorProduct(m2).tensorProduct(m3[0]);
	for(int i =1;i<4;i++){
		M += m1[i].tensorProduct(m2).tensorProduct(m3[i]);
	}
	physical_gate_list.push_back({gate,{q0,q1}});
	qubits.applyGate(Gate (number_of_qubits,m0.tensorProduct(M).tensorProduct(m4)));
}

void Circuit::apply(Gate gate,std::vector<int> qubits_list){
	if(qubits_list.size()!=gate.getNumQubits()){
		std::cerr<<"Gate not compatible with qubit list\n";
		return;
	}
	gate_list.push_back({gate,qubits_list});
	if(qubits_list.size()==1){
		add(gate,qubits_list[0]);
	}
	else {
		add(gate,qubits_list[0],qubits_list[1]);
	}
}

void Circuit::printStateVector(){
	qubits.printState();
}