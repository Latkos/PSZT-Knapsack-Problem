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
    double quality=0;
    ProblemInstance problem;

    Tester(ProblemInstance &givenProblem);

    void fullTesting(std::ostream &os = std::cout);

    void testMutationRateForOptimum(std::ostream &os = std::cout);

    void runTest(std::ostream &os = std::cout, bool d = false);

    void testPopulationSizeForOptimum(std::ostream &oss=std::cout);

    void testGenerationsForOptimum(std::ostream &oss=std::cout);

    void testFitnessByGeneration(std::ostream &oss=std::cout);

    void runOnce(std::ostream &oss=std::cout, bool d = false);

    void testKnapsackSize(std::ostream &oss=std::cout);

    void testFitnessByGenerationByMutation(std::ostream &oss=std::cout);

    void testPisinger(std::string fileName);

};

#endif