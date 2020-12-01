#include "Tester.hpp"
#include <iostream>

Tester::Tester(ProblemInstance &givenProblem)
{
    problem = givenProblem;
}


void Tester::runTest(std::ostream &os, bool d)
{
    //display();
    Clock clock;
    double time = 0;
    int bestSolution = 0;
    int sumReal = 0;

    for (int times = 0; times < 50; times++)
    {
        if (!d)
            problem.initializeWeightsAndValues();
        problem.initializePopulation();

        if (times == 0)
        {
            clock.start();
            bestSolution = problem.solveDynamic();
            clock.end();
        }
        clock.start();
        int a = 0;
        while (a < problem.generations)
        {
            problem.fitness();
            problem.select();
            problem.crossover();
            problem.smallMutate(problem.mutationRate);
            a++;
        }
        clock.end();
        time = time + clock.elapsedTime();
        problem.fitness();
        int max = problem.maxFitness();
        sumReal = sumReal + max;
    }
    sumReal = sumReal / 50;
    double quality = (double)sumReal / (double)bestSolution;
    os << problem.mutationRate << "\t" << problem.populationSize << "\t" << problem.generations << "\t" << problem.problemSize << "\t" << problem.knapsackSize << "\t" << quality << "\t" << time / 50 << std::endl;
}

void Tester::runOnce(std::ostream &os, bool d)
{
    //display();
    Clock clock;
    int bestSolution = 0;
    if (!d)
        problem.initializeWeightsAndValues();
    problem.initializePopulation();
    problem.fitnessHistory.clear();
    clock.start();
    int a = 0;
    while (a < problem.generations)
    {
        problem.fitness();
        problem.select();
        problem.crossover();
        problem.smallMutate(problem.mutationRate);
        a++;
        problem.fitnessHistory.push_back(problem.maxFitness());
    }
    clock.end();
    time = time + clock.elapsedTime();
    problem.fitness();
    int max = problem.maxFitness();
    bestSolution = problem.solveDynamic();
    quality = quality + max / double(bestSolution);
    os << "Znaleziono rozwiazanie: " << max << " w czasie: " << time << std::endl;
    os << "Jakosc tego rozwiazania w porownaniu do optymalnego to" << quality << std::endl;
}

void Tester::testMutationRateForOptimum(std::ostream &os)
{
    os << "Mutation rate"
       << "\t"
       << "population size"
       << "\t"
       << "generations"
       << "\t"
       << "problemSize"
       << "\t"
       << "quality"
       << "\t"
       << "time" << std::endl;

    for (double n = 0.1; n < 1; n += 0.1)
    {
        problem.mutationRate = n;
        runTest(os);
    }
}
void Tester::testPopulationSizeForOptimum(std::ostream &os)
{
    os << "Mutation rate"
       << "\t"
       << "population size"
       << "\t"
       << "generations"
       << "\t"
       << "problemSize"
       << "\t"
       << "quality"
       << "\t"
       << "time" << std::endl;

    for (double n = 50; n <= 500; n += 50)
    {
        problem.populationSize = n;
        runTest(os);
    }
}

void Tester::testGenerationsForOptimum(std::ostream &os)
{
    os << "Mutation rate"
       << "\t"
       << "population size"
       << "\t"
       << "generations"
       << "\t"
       << "problemSize"
       << "\t"
       << "quality"
       << "\t"
       << "time" << std::endl;

    for (double n = 100; n <= 1200; n += 50)
    {
        problem.generations = n;
        runTest(os);
    }
}

void Tester::testFitnessByGeneration(std::ostream &os)
{
    os << "Fitness:"
       << "\t"
       << "generation:" << std::endl;
    runOnce(os);
    for (unsigned int i = 0; i < problem.fitnessHistory.size(); ++i)
    {
        os << problem.fitnessHistory[i] << "\t" << i << std::endl;
    }
}

void Tester::fullTesting(std::ostream &os)
{
    os << "Mutation rate"
       << "\t"
       << "population size"
       << "\t"
       << "generations"
       << "\t"
       << "problemSize"
       << "\t"
       << "quality"
       << "\t"
       << "time" << std::endl;
    for (double n = 0.1; n < 1; n += 0.2)
    {
        problem.mutationRate = n;
        for (int i = 50; i < 550; i += 100)
        {
            problem.populationSize = i;
            for (int j = 200; j < 1200; j += 200)
            {
                problem.generations = j;
                for (int k = 50; k <= 150; k += 50)
                {
                    problem.problemSize = k;
                    runTest(os);
                }
            }
        }
    }
}

void Tester::testKnapsackSize(std::ostream &os)
{
    os << "Mutation rate"
       << "\t"
       << "population size"
       << "\t"
       << "generations"
       << "\t"
       << "problemSize"
       << "\t"
       << "KnapsackSize"
       << "\t"
       << "quality"
       << "\t"
       << "time" << std::endl;
    for (int i = 60; i < 600; i += 10)
    {
        problem.knapsackSize = i;
        runTest(os);
    }
}


void Tester::testFitnessByGenerationByMutation(std::ostream &os)
{
    problem.initializeWeightsAndValues();
    os << "MutationRate:"
       << "\t"
       << "fitness:"
       << "\t"
       << "generation:" << std::endl;
    for (double i = 0.1; i <= 1; i += 0.1)
    {
        problem.mutationRate = i;
        runOnce(os,1);

    }
}

void Tester::testPisinger(std::string fileName)
{
    std::fstream test1;
    test1.open(fileName);
    if (test1.good() == false)
    {
        std::cout << "Proba stworzenia pliku nie powiodla sie" << std::endl;
    }
    //there are 100 instances of 100 items, value first, weight second
    int tempValue = 0;
    int tempWeight = 0;
    double avgTime = 0;
    double avgQuality = 0;
    for (int a = 0; a < 100; a++)
    {
        std::cout << a << std::endl;
        problem.values.clear();
        problem.weights.clear();
        for (int b = 0; b < 100; b++)
        {
            test1 >> tempValue >> tempWeight;
            problem.values.push_back(tempValue);
            problem.weights.push_back(tempWeight);
            problem.totalItemWeight = problem.totalItemWeight + tempWeight;
        }
        //we have initialised the weights and values, we need to run the algorithm now
        //problem.displayWeightsAndValues();
        problem.knapsackSize = 0.05 * problem.totalItemWeight;
        runTest(std::cout,1);
        problem.totalItemWeight = 0;
    }
    avgTime = time / 100;
    avgQuality = quality / 100;
    std::cout << "Sredni czas: " << avgTime << " \n Srednia jakosc: " << avgQuality << std::endl;
    test1.close();
}
