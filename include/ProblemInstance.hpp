#ifndef PROBLEMINSTANCE_HPP
#define PROBLEMINSTANCE_HPP

#include <vector>
#include <algorithm>
#include <random>
#include "RandomGenerator.hpp"
#include "Clock.hpp"
#include "Specimen.hpp"
class ProblemInstance
{
private:
    RandomGenerator randomGen;
    Clock clock;
    int totalItemWeight=0;
    int testsAmount;
    int realMax = 0;


    //MODIFY THOSE
    double elitismRate=0.15; //most probably DO NOT modify it, I found that 0.1 is too little and 0.2 too much, but you can try...
    double mutationRate=0.5;
    int populationSize = 250;
    int generations=200;

    //DATA
    int knapsackSize=60; //20
    int problemSize=150; //50
 
    std::vector<int> weights, values, allFitness, fitnessHistory, fitnessMax;
    std::vector<Specimen> population;
    std::vector<Specimen> parents;

public:
    void initializeWeightsAndValues();
    void initializePopulation();
    void display();
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
    int maxIndex();
    int solveDynamic();
    int max(int a, int b);
    void initializePopulationWithZeroes();
    void testMutationRate();
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
};

#endif