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
public:
    RandomGenerator randomGen;
    Clock clock;
    int totalItemWeight=0;
    int testsAmount;
    int realMax = 0;
    //parameters estabilished before the main testing phase
    double crossoverRate=0.8;
    double elitismRate=0.15;
    //parameters estabilished by testing
    double mutationRate=0.5;
    int populationSize = 250;
    int generations=200;

    //default data
    int knapsackSize=60;
    int problemSize=100;
 
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
    void crossover2();
    void uniformCrossover();
    void mutate();
    void smallMutate(double mutationRate);
    void run(std::ostream & os = std::cout);
    void run2(std::ostream & os = std::cout);
    int maxFitness();
    int solveDynamic();
    int bestSpecimenIndex();
    int max(int a, int b);
    void initializePopulationWithZeroes();
    /*void testMutationRate();
    void fullTesting(std::ostream& os = std::cout);
    void fullTesting2(std::ostream& os = std::cout);

    void problematicTesting(std::ostream &os);

    void testMutationRateForOptimum(std::ostream& os = std::cout);

    void runTest(std::ostream &os = std::cout);

    void testPopulationSizeForOptimum(std::ostream &os);

    void testGenerationsForOptimum(std::ostream &os);

    void testFitnessByGeneraiton(std::ostream &os);

    void runOnce(std::ostream &os);

    void testKnapsackSize(std::ostream &os);

    void testFitnessByGenerationByMutation(std::ostream &os);

    void runOnceNoInit(std::ostream &os);*/


};

#endif