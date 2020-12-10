#include "circuit.h"

#include <iostream>
#include <vector>
/*
Circuit::Circuit(std::vector<int> qubit_list)
{
	this->qubits = *(new Qubits(qubit_list));
	this->number_of_qubits = qubit_list.size();
}
*/
Circuit::Circuit(int number_of_qubits)
{
	number_of_physical_qubits = number_of_qubits;
	if(number_of_qubits>3)
		number_of_physical_qubits++;
	if(number_of_qubits>7)
		number_of_physical_qubits++;
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
	std::vector<int> qubits;
	for (int i = 0; i < number_of_qubits; i++)
	{
		qubits.push_back(i);
	}
	this->qubits = *(new Qubits(qubits));
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
	//physical_gate_list.push_back({gate,{q0,q1}});
	qubits.applyGate(Gate (number_of_qubits,m0.tensorProduct(M).tensorProduct(m4)));
}
bool Circuit::inContact(int q0,int q1){
switch(q0){
		case 0: return (q1 == 1 || q1 == 2 || q1 == 10);
		case 1: return (q1 == 0 || q1 == 2 || q1 == 3 || q1 == 4 || q1 == 10);
		case 2: return (q1 == 0 || q1 == 1 || q1 == 5 || q1 == 10 || q1 == 11);
		case 3: return (q1 == 1 || q1 == 4 || q1 == 10);
		case 4: return (q1 == 1 || q1 == 3 || q1 == 6 || q1 ==10 || q1 == 11);
		case 5: return (q1 == 2 || q1 == 7 || q1 == 8 || q1 == 10 || q1 == 11);
		case 6: return (q1 == 4 || q1 == 8 || q1 == 9 || q1 == 10 || q1 == 11);
		case 7: return (q1 == 5 || q1 == 8 || q1 == 11);
		case 8: return (q1 == 5 || q1 == 6 || q1 == 7 || q1 == 9 || q1 == 11);
		case 9: return (q1 == 6 || q1 == 8 || q1 == 11);
		default : return false;
	}
}
std::vector<int> Circuit::swapTargets(int q0,int q1){
	std::vector<int> swapTo;
	if(inContact(q0,q1));
	else if(inContact(q0,10)&&inContact(q1,10)){
		swapTo.push_back(10);
	}
	else if(inContact(q0,11)&&inContact(q1,11)){
		swapTo.push_back(11);
	}
	else if(inContact(q0,10)&&inContact(q1,11)){
		swapTo.push_back(10);
		swapTo.push_back(11);
	}
	else{
		swapTo.push_back(11);
		swapTo.push_back(10);
	}
	return swapTo;
}
void Circuit::SWAP(int q0,int q1){
	//std::cout<<"SWAPPED "<<q0<<" "<<q1<<'\n';
	physical_gate_list.push_back({CX(),{q0,q1}});
	physical_gate_list.push_back({CX(),{q1,q0}});
	physical_gate_list.push_back({CX(),{q0,q1}});
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
		int q0 = qubits_list[0],q1 = qubits_list[1];
		std::vector<int> swapTo = swapTargets(q0,q1);
		if(swapTo.size()==1){
			SWAP(q0,swapTo[0]);
			physical_gate_list.push_back({gate,{swapTo[0],q1}});
			/*
			std::cout<<"Applied \n";
			gate.printGate();
			std::cout<<"To "<<swapTo[0]<<' '<<q1<<'\n';
			*/
			SWAP(q0,swapTo[0]);
		}
		else if(swapTo.size()==2){
			SWAP(q0,swapTo[0]);
			SWAP(q1,swapTo[1]);
			physical_gate_list.push_back({gate,{swapTo[0],swapTo[1]}});
			/*
			std::cout<<"Applied \n";
			gate.printGate();
			std::cout<<"To "<<swapTo[0]<<' '<<swapTo[1]<<'\n';
			*/
			SWAP(q1,swapTo[1]);
			SWAP(q0,swapTo[0]);
		}
		else{
			physical_gate_list.push_back({gate,{q0,q1}});
			/*
			std::cout<<"Applied \n";
			gate.printGate();
			std::cout<<"To "<<q0<<' '<<q1<<'\n';
			*/
		}
		add(gate,q0,q1);
	}

}

void Circuit::printStateVector(){
	qubits.printState();
}