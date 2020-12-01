#ifndef PROBLEMINSTANCE_HPP
#define PROBLEMINSTANCE_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "RandomGenerator.hpp"
#include "Clock.hpp"
#include "Specimen.hpp"

class ProblemInstance
{
private:
    RandomGenerator randomGen;
    Clock clock;

public:
    int totalItemWeight = 0;
    int testsAmount;
    int realMax = 0;
    //parameters estabilished before the main testing phase
    double crossoverRate = 0.8;
    double elitismRate = 0.15;
    //parameters estabilished by testing
    double mutationRate = 0.5;
    int populationSize = 250;
    int generations = 200;

    //default data
    int knapsackSize = 60;
    int problemSize = 100;

    std::vector<int> weights, values, allFitness, fitnessHistory;
    std::vector<Specimen> population;
    std::vector<Specimen> parents;
    void initializeWeightsAndValues();
    void initializePopulation();
    void displayWeightsAndValues();
    int individualFitness(int index);
    void fitness();
    void select();
    void crossover();
    void smallMutate(double mutationRate);
    int maxFitness();
    int solveDynamic();
    int bestSpecimenIndex();
    int max(int a, int b);

    //unused functions which we used for testing and therefore left them for documentation purposes
    void initializePopulationWithZeroes();
    void uniformCrossover();
    void crossover2();
    void mutate();
};

#endif