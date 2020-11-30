#include "RandomGenerator.hpp"
#include "Clock.hpp"
#include "ProblemInstance.hpp"
#include "Tester.hpp"
#include <iostream>
#include <random>
#include <fstream>

int main()
{
    Tester tester;
    //problem.run();
    //problem.testMutationRate();
    //problem.run();
    //    std::fstream mutation;
    //    mutation.open("Mutation test results.txt", std::ios::out|std::ios::trunc);
    //    if(mutation.good()==false)
    //    {
    //        std::cout<<"Proba stworzenie pliku nie powiodla sie"<<std::endl;
    //    }
    //    std::fstream popSize;
    //    popSize.open("population size test results.txt", std::ios::out|std::ios::trunc);
    //    if(popSize.good()==false)
    //    {
    //        std::cout<<"Proba stworzenie pliku nie powiodla sie"<<std::endl;
    //    }
    //    std::fstream generations;
    //    mutation.open("generation test results.txt", std::ios::out|std::ios::trunc);
    //    if(generations.good()==false)
    //    {
    //        std::cout<<"Proba stworzenie pliku nie powiodla sie"<<std::endl;
    //    }
    //    std::fstream fitnessAlig;
    //    fitnessAlig.open("Mutation test results.txt", std::ios::out|std::ios::trunc);
    //    if(fitnessAlig.good()==false)
    //    {
    //        std::cout<<"Proba stworzenie pliku nie powiodla sie"<<std::endl;
    //    }
    /* std::fstream knapsackTEst;
    knapsackTEst.open("knapsackTEst results.txt", std::ios::out|std::ios::trunc);
    if(knapsackTEst.good()==false)
    {
        std::cout<<"Proba stworzenie pliku nie powiodla sie"<<std::endl;
    }*/
    //problem.testMutationRateForOptimum(mutation);
    //problem.testPopulationSizeForOptimum(popSize);
    //problem.testGenerationsForOptimum(generations);
    //problem.testFitnessByGeneraiton(fitnessAlig);
    //problem.testKnapsackSize(std::cout);
    tester.testPisinger("dane1.txt");
    std::cout << "done" << std::endl;
}