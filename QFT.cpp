#include "circuit.h"
using namespace std;

// apply Quantum Fourier Transform to the first n qubits in circuit qc
void QFT(Circuit &qc,int n){
    vector<double> lambda(n-1);
    lambda[n-2] = -M_PI/(1<<n-1);
    for(int i = n-3;i>=0;i--){
        lambda[i] = lambda[i+1]*2;
    }
    for(int i = n-1;i>=0;i--){
        qc.apply(H(),i);
        int count = 0;
        for(int j = i-1;j>=0;j--){
            qc.apply(Controlled(U(0,0,lambda[count++])),j,i);
        }
    }

    for(int i = 0;i<n/2;i++){
        qc.apply(CX(),i,n-i-1);
    }
}

int main(){
    std::cout<<"Enter n\n";
    int n;
    cin>>n;
    Circuit qc(n);
    //initialise in arbitrary state for testing
    for(int i = 0;i<n;i++)
        qc.apply(X(),i);
    //verify state
    qc.printStateVector();
    std::cout<<endl;
    //apply Quantum Fourier Transform to all n qubits in the circuit
    QFT(qc,n);
    //verify output of QFT
    qc.printStateVector();
}