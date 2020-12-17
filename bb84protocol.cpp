#include "qubits.h"
#include "circuit.h"
#include "gate.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


std::vector<Circuit*> encode_message(std::vector<int> bits, std::vector<int> bases) {
	std::vector<Circuit*> message;
	for(int i=0;i<bits.size();i++) {
		Circuit *qc = new Circuit(1);
		if(bases[i] == 0) {
		// Prepare qubit in Z-basis
            if (bits[i] == 0){
                continue;
			}
            else {
                qc->apply(X(), 0);
        	}
    	}
        else {
		// Prepare qubit in X-basis
            if (bits[i] == 0){
                qc->apply(H(), 0);
        	}
            else {
                qc->apply(X(), 0);
                qc->apply(H(), 0);
        	}
    	}
        //qc.barrier()
        message.push_back(qc);
	}
	return message;
}

std::vector<int> measure_message(std::vector<Circuit*> message, std::vector<int> bases) {

    
    std::vector<int> measurements;
    for(int q=0;q<bases.size();q++) {
        if(bases[q] == 0){
		// measuring in Z-basis
            message[q]->measure(0);
    	}
        if (bases[q] == 1 ){
        	// measuring in X-basis
            message[q]->apply(H(), 0);
            message[q]->measure(0);
    	}
        int measured_bit = message[q]->measureAll()[0];
        measurements.push_back(measured_bit);
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

std::vector<int> sample_bits(std::vector<int> bits, std::vector<int> selection) {
    std::vector<int> sample;
    for(int i=0;i<selection.size();i++){
        int index = selection[i]%bits.size();
        sample.push_back(bits[index]);
        bits.erase(bits.begin()+index);
	}
    return sample;
}

void apply_protocol() {
	
	int n = 100;

	// Alice generates bits
	std::vector<int> alice_bits;
	for(int i=0;i<n;i++){
		alice_bits.push_back(rand()%2);
	}

	// An array to tell us which qubits are encoded in which bases
	std::vector<int> alice_bases;
	for(int i=0;i<100;i++) {
		alice_bases.push_back(rand()%2);
	}
	std::vector<Circuit*> message;
	message = encode_message(alice_bits, alice_bases);
	
	std::vector<int> bob_bases;
	for(int i=0;i<100;i++) {
		bob_bases.push_back(rand()%2);
	}
	std::vector<int> bob_results;
	bob_results = measure_message(message, bob_bases);
	
	
	std::vector<int> alice_key;
	alice_key = remove_garbage(alice_bases, bob_bases, alice_bits);
	
	std::vector<int> bob_key;
	bob_key = remove_garbage(alice_bases, bob_bases, bob_results);
	
	int sample_size = 15;
	std::vector<int> bit_selection;
	
	for(int i=0;i<sample_size;i++) {
		bit_selection.push_back(rand()%n);
	}

	std::vector<int> bob_sample;
	bob_sample = sample_bits(bob_key, bit_selection);
	
	std::vector<int> alice_sample;
	alice_sample = sample_bits(alice_key, bit_selection);
	
}
