#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>

class RandomGenerator{
std::random_device device;
std::mt19937 engine;
RandomGenerator();
int generateRandomInt(int beginning, int end);
};


#endif