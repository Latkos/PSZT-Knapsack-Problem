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
    int populationSize = 100;
    int knapsackSize = 35;
    std::vector<int> weights, values, allFitness;
    std::vector<Specimen> population;

public:
    void initialize();
    void todo();
    int individualFitness(int index);
    void fitness();
    void select();
    //crossover();
    void mutate();
    void run();
};

#endif