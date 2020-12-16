#include "circuit.h"
#include<chrono>
using namespace std::chrono;

int main()
{
    Circuit qc(10);

    auto start = high_resolution_clock::now();
    std::cout << "Starting clock" << std::endl; 

    qc.apply(H(), {0});

    std::cout << "Clock stopped" << std::endl; 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout<<"Gate application time: "<< duration.count() << " miliseconds" << std::endl;

    qc.apply(H(), {1});
    qc.apply(H(), {2});
    qc.apply(H(), {3});
    //qc.printStateVector();
    // measurement test
    std::cout<<"Starting measurement" << std::endl;
    start = high_resolution_clock::now();
    std::vector<int> outcomes = qc.measureAll();
    std::cout<<"Measurement outcome:" << std::endl;
    for (int a:outcomes)
    {
        std::cout << a;
    }
    std::cout<< std::endl;
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    std::cout<<"Measurement time: "<<duration.count()<< std::endl;
    std::cout<<"After measurement" << std::endl;
    qc.printStateVector();
}
