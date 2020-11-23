#include <iostream>
#include <random>
#include "RandomGenerator.hpp"
#include "Clock.hpp"
#include "ProblemInstance.hpp"
#include <fstream>

int main()
{
    ProblemInstance problem;
    //problem.run();
    //problem.testMutationRate();

    std::fstream out1;
    out1.open("run results.txt", std::ios::out|std::ios::trunc);
    if(out1.good()==false)
    {
        std::cout<<"Proba stworzenie pliku nie powiodla sie"<<std::endl;
    }
    std::fstream out2;
    out2.open("run2 results.txt", std::ios::out|std::ios::trunc);
    if(out2.good()==false)
    {
        std::cout<<"Proba stworzenie pliku nie powiodla sie"<<std::endl;
    }
   // problem.fullTesting(out1);
    problem.fullTesting2(out2);
    out1.close(); out2.close();
}