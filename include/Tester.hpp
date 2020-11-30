#ifndef TESTER_HPP
#define TESTER_HPP
#include <ostream>
#include <fstream>
#include <iostream>
#include <string>
#include "ProblemInstance.hpp"

class Tester
{
public:
    double time=0;
    double deviation=0;
    ProblemInstance problem;

    void run(std::ostream &os = std::cout);

    void fullTesting(std::ostream &os = std::cout);

    void problematicTesting(std::ostream &os);

    void testMutationRateForOptimum(std::ostream &os = std::cout);

    void runTest(std::ostream &os = std::cout);

    void testPopulationSizeForOptimum(std::ostream &os);

    void testGenerationsForOptimum(std::ostream &os);

    void testFitnessByGeneration(std::ostream &os);

    void runOnce(std::ostream &os);

    void testKnapsackSize(std::ostream &os);

    void testFitnessByGenerationByMutation(std::ostream &os);

    void runOnceNoInit(std::ostream &os);

    void testPisinger(std::string fileName);

};

#endif