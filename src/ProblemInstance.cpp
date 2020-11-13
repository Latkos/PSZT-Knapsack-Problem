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
        Specimen newSpecimen(problemSize);
        newSpecimen.fill();
        population.push_back(newSpecimen);
    }
}

void ProblemInstance::todo()
{
    std::cout << "WEIGHTS" << std::endl;
    for (int a = 0; a < problemSize; a++)
        std::cout << weights[a] << " ";
    std::cout << "\nVALUES" << std::endl;
    for (int a = 0; a < problemSize; a++)
        std::cout << values[a] << " ";
    std::cout << "\nPOPULATION" << std::endl;
    for (int a = 0; a < populationSize; a++)
    {
        for (int b = 0; b < problemSize; b++)
        {
            std::cout << population[a].genes[b];
        }
        std::cout << std::endl;
    }
}

void ProblemInstance::fitness()
{
    allFitness.clear();
    for (int a = 0; a < populationSize; a++)
    {
        allFitness.push_back(individualFitness(a));
    }
}

int ProblemInstance::individualFitness(int index)
{
    int sumWeights = 0;
    int sumValues = 0;
    for (int c = 0; c < problemSize; c++)
    {
        sumWeights = sumWeights + weights[c] * population[index].genes[c];
        sumValues = sumValues + values[c] * population[index].genes[c];
    }
    if (sumWeights <= knapsackSize)
        return sumValues;
    return 0;
}

void ProblemInstance::select()
{
    std::vector<Specimen> tempPopulation;
    for (int a = 0; a < populationSize; a++)
    {
        int random1 = randomGen.generateInt(0, populationSize - 1);
        int random2 = randomGen.generateInt(0, populationSize - 1);
        if (individualFitness(random1) > individualFitness(random2))
            tempPopulation.push_back(population[random1]);
        else
            tempPopulation.push_back(population[random2]);
    }
    population.clear();
    population = tempPopulation;
}

void ProblemInstance::mutate()
{
    double mutationRate = 0.5;
    for (int a = 0; a < populationSize; a++)
    {
        double probability = randomGen.generateProbability();
        if (probability >= mutationRate)
        {
            int changedGene = randomGen.generateInt(0, problemSize - 1);
            if (population[a].genes[changedGene] == 1)
                population[a].genes[changedGene] = 0;
            else
                population[a].genes[changedGene] = 1;
        }
    }
}

void ProblemInstance::run()
{
    initialize();
    /*weights = {10, 12, 3, 4, 5, 6, 7, 8};
    values = {27, 34, 19, 40, 5, 200, 3, 10};
    for (int a = 0; a < populationSize; a++)
    {
        Specimen newSpecimen(problemSize);
        newSpecimen.fill();
        population.push_back(newSpecimen);
    }*/
    todo();
    for (int length = 0; length < 5000; length++)
    {
        //std::cout<<"TEST1"<<std::endl;
        fitness();
        //std::cout<<"TEST2"<<std::endl;
        select();
        //std::cout<<"TEST3"<<std::endl;
        mutate();
        //std::cout<<"TEST4"<<std::endl;
    }
    todo();
    int max = 0;
    for (int a = 0; a < populationSize; a++)
    {
        if(individualFitness(a)>max)
            max = individualFitness(a);
    }
    std::cout<<"MAX: "<<max<<std::endl;
}