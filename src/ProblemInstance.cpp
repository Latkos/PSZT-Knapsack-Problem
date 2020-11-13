#include <iostream>
#include <random>
#include "ProblemInstance.hpp"

void ProblemInstance::initialize()
{
    problemSize = randomGen.generateInt(10, 15);
    for (int a = 0; a < problemSize; a++)
    {
        int random;
        random = randomGen.generateInt(1, 15);
        weights.push_back(random);
        random = randomGen.generateInt(10, 750);
        values.push_back(random);
    }
    for (int a = 0; a < populationSize; a++)
    {
        Specimen newSpecimen(problemSize+a);
        newSpecimen.fill();
        population.push_back(newSpecimen);
    }
}

void ProblemInstance::todo()
{
    std::cout << "WEIGHTS" << std::endl;
    for (int a = 0; a < problemSize; a++)
        std::cout << weights[a]<<" ";
    std::cout << "\nVALUES" << std::endl;
    for (int a = 0; a < problemSize; a++)
        std::cout << values[a]<<" ";
    std::cout << "\nPOPULATION\n" << std::endl;
    for (int a = 0; a < populationSize; a++){
        for (int b = 0; b < problemSize; b++){
            std::cout<<population[a].genes[b];
        }
        std::cout<<std::endl;
    }
}

