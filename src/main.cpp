#include <iostream>
#include <random>
#include "RandomGenerator.hpp"
#include "Clock.hpp"
#include "ProblemInstance.hpp"

int main()
{
    ProblemInstance problem;
    problem.initialize();
    problem.todo();

    /*RandomGenerator random;
    for (int a=0;a<10;a++)
        std::cout<<random.generateInt(1,20)<<" ";*/

    /* std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> bound_dist(1, 20);
     int result = bound_dist(engine);
    std::cout<<result;*/
}