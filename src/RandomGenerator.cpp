#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator()
{
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        engine = std::mt19937(seed);
}

int RandomGenerator::generateInt(int beginning, int end)
{
        std::uniform_int_distribution<int> bound_dist(beginning, end);
        int result = bound_dist(engine);
        return result;
}

double RandomGenerator::generateProbability()
{
        std::uniform_real_distribution<double> real_dist(0, 1);
        double result = real_dist(engine);
        return result;
}