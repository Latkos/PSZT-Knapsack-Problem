#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>
#include <chrono>
class RandomGenerator
{
private:
    std::mt19937 engine;

public:
    RandomGenerator();
    int generateInt(int beginning, int end);
    double generateProbability();
    //int generateInt();
};

#endif