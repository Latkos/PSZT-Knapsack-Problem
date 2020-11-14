#ifndef PROBLEMINSTANCE_HPP
#define PROBLEMINSTANCE_HPP

#include <vector>
#include "RandomGenerator.hpp"
#include "Clock.hpp"
#include "Specimen.hpp"
class ProblemInstance
{
private:
    RandomGenerator randomGen;
    Clock clock;
    int problemSize;
    int populationSize = 1000;
    int knapsackSize;
    std::vector<int> weights, values, allFitness, fitnessHistory,fitnessMax;
    std::vector<Specimen> population;
    std::vector<Specimen> parents;

public:
    ProblemInstance(int knapsackCapacity);
    void initialize();
    void display();
    int individualFitness(int index);
    void fitness();
    void select();
    void crossover();
    void mutate();
    void run();
    int maxIndex();
};

#endif