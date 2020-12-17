#include "circuit.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

Circuit encode_message(int bit, int basis) {
	Circuit qc(1);
	if(basis == 0) {
	// Prepare qubit in Z-basis
        if (bit == 0);
        else {
            qc.apply(X(), 0);
    	}
	}
    else {
	// Prepare qubit in X-basis
        if (bit == 0){
            qc.apply(H(), 0);
    	}
        else {
            qc.apply(X(), 0);
            qc.apply(H(), 0);
    	}
	}
	return qc;
}

int measure_message(Circuit& message,int basis) {

    int measurements;
    if(basis == 0){
		// measuring in Z-basis
        measurements = message.measure(0);
    }
    else{
    	// measuring in X-basis
        message.apply(H(), 0);
        measurements = message.measure(0);
    }
    return measurements;
}

std::vector<int> remove_garbage(std::vector<int> a_bases, std::vector<int> b_bases, std::vector<int> bits) {
    std::vector<int> good_bits;
    for(int q=0;q<bits.size();q++){
        if(a_bases[q] == b_bases[q]){
            //If both used the same basis, push to list of 'good' bits
            good_bits.push_back(bits[q]);
    	}
	}
    return good_bits;
}

std::vector<int> sample_bits(std::vector<int> &bits, std::vector<int> selection) {
    std::vector<int> sample;
    for(int i=0;i<selection.size();i++){
        int index = selection[i]%bits.size();
        sample.push_back(bits[index]);
        bits.erase(bits.begin()+index);
	}
    return sample;
}

void apply_BB84(int n) {
	// Alice generates bits
	srand(time(0));
	std::vector<int> alice_bits;
	for(int i=0;i<n;i++){
		alice_bits.push_back(rand()%2);
	}

	// An array to tell us which qubits are encoded in which bases
	std::vector<int> alice_bases;
	for(int i=0;i<n;i++) {
		alice_bases.push_back(rand()%2);
	}
	std::vector<int> bob_bases,bob_results;
	for(int i=0;i<n;i++) {
		bob_bases.push_back(rand()%2);
	}

	for(int i = 0;i<n;i++){
		Circuit message = encode_message(alice_bits[i],alice_bases[i]);
		//std::cout<<"Encoded bit "<<i<<"\n";
		bob_results.push_back(measure_message(message,bob_bases[i]));
		//std::cout<<"Bob measured bit "<<i<<'\n';
	}
	std::vector<int> alice_key;
	alice_key = remove_garbage(alice_bases, bob_bases, alice_bits);
	std::vector<int> bob_key;
	bob_key = remove_garbage(alice_bases, bob_bases, bob_results);
	
	int sample_size = alice_key.size()/2;
	std::vector<int> bit_selection;
	
	for(int i=0;i<sample_size;i++) {
		bit_selection.push_back(rand()%n);
	}

	std::vector<int> bob_sample;
	bob_sample = sample_bits(bob_key, bit_selection);
	
	std::vector<int> alice_sample;
	alice_sample = sample_bits(alice_key, bit_selection);
	for(int i = 0;i<sample_size;i++){
		if(alice_sample[i]!=bob_sample[i]){
			std::cout<<"Protocol aborted\n";
			return;
		}
	}
	std::cout<<"Key of length "<<alice_key.size()<<" has been established\n";
}

int main(){
	apply_BB84(100);
}