#include <iostream>
#include <random>
#include "ProblemInstance.hpp"

ProblemInstance::ProblemInstance(int knapsackCapacity)
{
    knapsackSize = knapsackCapacity;
}


void ProblemInstance::initialize()
{
    problemSize = randomGen.generateInt(500, 500);
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

void ProblemInstance::display()
{
    /*std::cout << "WEIGHTS" << std::endl;
    for (int a = 0; a < problemSize; a++)
        std::cout << weights[a] << " ";
    std::cout << "\nVALUES" << std::endl;
    for (int a = 0; a < problemSize; a++)
        std::cout << values[a] << " ";
    std::cout << "\nPOPULATION" << std::endl;*/
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
    double averageFitness = 0;
    for (int a = 0; a < populationSize; a++)
    {
        averageFitness = averageFitness + allFitness[a];
    }
    averageFitness = averageFitness / populationSize;
    fitnessHistory.push_back(averageFitness);
    fitnessMax.push_back(allFitness[maxIndex()]);
}

int ProblemInstance::maxIndex()
{
    int max = 0;
    for (int a = 0; a < populationSize; a++)
    {
        if (allFitness[a] > allFitness[max])
            max = a;
    }
    return max;
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
    double mutationRate = 0.8;
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

void ProblemInstance::crossover()
{
    std::vector<Specimen> tempPopulation;
    for (int a = 0; a < populationSize/2; a++)
    {
        double probability = randomGen.generateProbability();
        if (probability > 0.8)
        {
            tempPopulation.push_back(population[a]);
            tempPopulation.push_back(population[a + 1]);
        }
        else
        {
            Specimen child1(problemSize), child2(problemSize);
            int point = problemSize/2; //albo int point =randGen.generateInt(0,problemSize-1)
            for (int b = 0; b < point; b++)
            {
                child1.genes.push_back(population[a].genes[b]);
                child2.genes.push_back(population[a + 1].genes[b]);
            }
            for (int b = point; b < problemSize; b++)
            {
                child1.genes.push_back(population[a + 1].genes[b]);
                child2.genes.push_back(population[a].genes[b]);
            }
            tempPopulation.push_back(child1);
            tempPopulation.push_back(child2);
        }
    }
    population.clear();
    population = tempPopulation;
}

void ProblemInstance::run()
{
    initialize();
    //display();
    // std::vector<Specimen> initialPopulation=population; tutaj zostawiamy dla liczenia tego samego problemu wiecej razy
    for (int length = 0; length < 5000; length++)
    {
        std::cout<<length<<std::endl;
        fitness();
        select();
        //crossover();
        mutate();
    }
//display();
    int max = 0;
    for (int a = 0; a < populationSize; a++)
    {
        if(individualFitness(a)>max)
            max = individualFitness(a);
    }
    std::cout<<"MAX: "<<max<<std::endl;
}