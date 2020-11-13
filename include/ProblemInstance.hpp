#ifndef PROBLEMINSTANCE_HPP
#define PROBLEMINSTANCE_HPP

#include <vector>
#include "RandomGenerator.hpp"
#include "Clock.hpp"
#include "Specimen.hpp"
class ProblemInstance{
    private:
    RandomGenerator randomGen;
    Clock clock;
    int problemSize;
    int populationSize=8;
    std::vector<int> weights, values;
    std::vector<Specimen> population;
    public:
    void initialize();
    void todo();
    void measureOverallFitness();
    int fitness();
    void select();
    //crossover();
    void mutate();
};

#endif