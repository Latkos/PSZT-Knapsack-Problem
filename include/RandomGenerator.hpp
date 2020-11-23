#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>
#include <chrono>
class RandomGenerator
{
    public:
    std::mt19937 engine;
    unsigned seed;
    RandomGenerator();
    int generateInt(int beginning, int end);
    double generateProbability();
    //int generateInt();
};

#endif