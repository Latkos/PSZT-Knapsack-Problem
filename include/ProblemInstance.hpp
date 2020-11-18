#ifndef PROBLEMINSTANCE_HPP
#define PROBLEMINSTANCE_HPP

#include <vector>
#include <algorithm>
#include "RandomGenerator.hpp"
#include "Clock.hpp"
#include "Specimen.hpp"
class ProblemInstance
{
private:
    RandomGenerator randomGen;
    Clock clock;
    int knapsackSize;
    int totalItemWeight=0;
    int testsAmount;
    int generations;
    int realMax = 0;
    int problemSize;
    double elitismRate=0.15;
    int populationSize = 300;
    double mutationRate=0.7;
   
 
    std::vector<int> weights, values, allFitness, fitnessHistory, fitnessMax;
    std::vector<Specimen> population;
    std::vector<Specimen> parents;

public:
    ProblemInstance(int knapsackCapacity);
    void initializeWeightsAndValues();
    void initializePopulation();
    void display();
    int individualFitness(int index);
    void fitness();
    void select();
    void crossover();
    void uniformCrossover();
    void mutate();
    void smallMutate(double mutationRate);
    void run();
    int maxIndex();
    int solveDynamic();
    int max(int a, int b);
    void initializePopulationWithZeroes();
};

#endif