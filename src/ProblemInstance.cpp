#include <iostream>
#include <random>
#include "ProblemInstance.hpp"

ProblemInstance::ProblemInstance(int knapsackCapacity)
{
    knapsackSize = knapsackCapacity;
}

void ProblemInstance::initializeWeightsAndValues()
{
    problemSize = randomGen.generateInt(150, 150);
    for (int a = 0; a < problemSize; a++)
    {
        int random;
        random = randomGen.generateInt(1, 15);
        totalItemWeight = totalItemWeight + random;
        weights.push_back(random);
        random = randomGen.generateInt(10, 750);
        values.push_back(random);
    }
}

void ProblemInstance::initializePopulation()
{
    population.clear();
    double itemProbability = knapsackSize / (2 * totalItemWeight);
    for (int a = 0; a < populationSize; a++)
    {
        Specimen newSpecimen(problemSize);
        newSpecimen.fill(itemProbability);
        population.push_back(newSpecimen);
    }
}

void ProblemInstance::display()
{
    std::cout << "WEIGHTS" << std::endl;
    for (int a = 0; a < problemSize; a++)
        std::cout << weights[a] << " ";
    std::cout << "\nVALUES" << std::endl;
    for (int a = 0; a < problemSize; a++)
        std::cout << values[a] << " ";
}

void ProblemInstance::fitness()
{
    for (int a = 0; a < populationSize; a++)
    {
        population[a].fitness = individualFitness(a);
    }
    fitnessMax.push_back(population[maxIndex()].fitness);
}

int ProblemInstance::maxIndex()
{
    int max = 0;
    for (int a = 0; a < populationSize; a++)
    {
        if (population[a].fitness > population[max].fitness)
            max = a;
    }
    return max;
}

int ProblemInstance::individualFitness(int index)
{
    int sumWeights = 0;
    int sumValues = 0;
    for (int c = 0; c < problemSize; c++)
    {
        sumWeights = sumWeights + weights[c] * population[index].genes[c];
        sumValues = sumValues + values[c] * population[index].genes[c];
    }
    if (sumWeights <= knapsackSize)
    {
        if (sumValues > realMax)
            realMax = sumValues;
        return sumValues;
    }
    else
    {
        //int result = sumValues - (sumWeights - knapsackSize) * 380*2;
        int result = 0;
        return result;
    }
}

bool compareFitness(Specimen a, Specimen b)
{
    return a.fitness > b.fitness;
}

void ProblemInstance::select()
{
    std::vector<Specimen> tempPopulation;
    std::sort(population.begin(), population.end(), compareFitness);
    int eliteNumber = populationSize * elitismRate;
    for (int a = 0; a < eliteNumber; a++)
    {
        tempPopulation.push_back(population[a]);
    }
    for (int a = 0; a < populationSize - eliteNumber; a++)
    {
        int random1 = randomGen.generateInt(0, populationSize - 1);
        int random2 = randomGen.generateInt(0, populationSize - 1);
        if (population[random1].fitness > population[random2].fitness)
            tempPopulation.push_back(population[random1]);
        else
            tempPopulation.push_back(population[random2]);
    }
    population.clear();
    population = tempPopulation;
}

void ProblemInstance::mutate()
{
    for (int a = 0; a < populationSize; a++)
    {
        double probability = randomGen.generateProbability();
        if (probability < mutationRate)
        {
            for (int b = 0; b < problemSize; b++)
            {
                probability = randomGen.generateProbability();
                if (probability < 0.1)
                {
                    if (population[a].genes[b] == 1)
                        population[a].genes[b] = 0;
                    else
                        population[a].genes[b] = 1;
                }
            }
        }
    }
}
void ProblemInstance::smallMutate(double mutationRate)
{
    for (int a = 0; a < populationSize; a++)
    {
        double probability = randomGen.generateProbability();
        if (probability < mutationRate)
        {
            int randomGene = randomGen.generateInt(0, problemSize - 1);
            if (population[a].genes[randomGene] == 0)
                population[a].genes[randomGene] = 1;
            else
                population[a].genes[randomGene] = 0;
        }
    }
}
void ProblemInstance::crossover()
{
    std::vector<Specimen> tempPopulation;
    for (int a = 0; a < populationSize / 2; a++)
    {
        double probability = randomGen.generateProbability();
        if (probability > 0.8)
        {
            tempPopulation.push_back(population[a]);
            tempPopulation.push_back(population[a + 1]);
        }
        else
        {
            Specimen child1(problemSize), child2(problemSize);
            int point = randomGen.generateInt(0, problemSize - 1);
            //int point=populationSize/2;
            for (int b = 0; b < point; b++)
            {
                child1.genes.push_back(population[a].genes[b]);
                child2.genes.push_back(population[a + 1].genes[b]);
            }
            for (int b = point; b < problemSize; b++)
            {
                child1.genes.push_back(population[a + 1].genes[b]);
                child2.genes.push_back(population[a].genes[b]);
            }
            tempPopulation.push_back(child1);
            tempPopulation.push_back(child2);
        }
    }
    population.clear();
    population = tempPopulation;
}
void ProblemInstance::uniformCrossover()
{
    std::vector<Specimen> tempPopulation;
    for (int a = 0; a < populationSize; a = a + 2)
    {
        if (a == populationSize - 1 && populationSize % 2 == 1)
        {
            tempPopulation.push_back(population[a]);
            break;
        }
        double probability = randomGen.generateProbability();
        if (probability > 0.4)
        {
            tempPopulation.push_back(population[a]);
            tempPopulation.push_back(population[a + 1]);
        }
        else
        {
            Specimen child1(problemSize), child2(problemSize);
            for (int b = 0; b < problemSize; b++)
            {
                int bitDecider = randomGen.generateInt(0, 1);
                if (bitDecider == 0)
                    child1.genes.push_back(population[a].genes[b]);
                else
                    child1.genes.push_back(population[a + 1].genes[b]);
            }
            for (int b = 0; b < problemSize; b++)
            {
                int bitDecider = randomGen.generateInt(0, 1);
                if (bitDecider == 0)
                    child2.genes.push_back(population[a].genes[b]);
                else
                    child2.genes.push_back(population[a + 1].genes[b]);
            }
            tempPopulation.push_back(child1);
            tempPopulation.push_back(child2);
        }
    }
}
int ProblemInstance::max(int a, int b)
{
    return (a > b) ? a : b;
}

int ProblemInstance::solveDynamic()
{
    int i, w;
    int xwidth = problemSize + 1;
    int ywidth = knapsackSize + 1;
    int *KArray = (int *)new int[xwidth * ywidth];
    for (i = 0; i <= problemSize; i++)
    {
        for (w = 0; w <= knapsackSize; w++)
        {
            if (i == 0 || w == 0)
                KArray[w * xwidth + i] = 0;
            else if (weights[i - 1] <= w)
                KArray[w * xwidth + i] = max(values[i - 1] + KArray[(w - weights[i - 1]) * xwidth + i - 1], KArray[w * xwidth + i - 1]);
            else
                KArray[w * xwidth + i] = KArray[w * xwidth + i - 1];
        }
    }

    return KArray[knapsackSize * xwidth + problemSize];
}

void ProblemInstance::initializePopulationWithZeroes()
{
    for (int a = 0; a < populationSize; a++)
    {
        for (int b = 0; b < problemSize; b++)
        {
            population[a].genes[b] = 0;
        }
    }
}

void ProblemInstance::run()
{
    initializeWeightsAndValues();
    //display();
    Clock clock;
    double time = 0;
    int bestSolution = 0;
    int sumReal = 0;
    for (int times = 0; times < 10; times++)
    {
        initializePopulation();
        //initializePopulationWithZeroes();
        if (times == 0)
        {
            clock.start();
            bestSolution = solveDynamic();
            clock.end();
            std::cout << "\nNAJLEPSZA: " << bestSolution << " " << clock.elapsedTime() << std::endl;
        }
        clock.start();
        int a = 0;
        while (a < 250 || population[maxIndex()].fitness == 0)
        {
            fitness();
            select();
            crossover();
            smallMutate(mutationRate);
            a++;
        }
        clock.end();
        fitnessMax.clear();
        time = time + clock.elapsedTime();
        std::cout << clock.elapsedTime() << std::endl;
        fitness();
        int max = population[maxIndex()].fitness;
        std::cout << "BEST AT THE END: " << max << std::endl;
        std::cout << "Real max found was " << realMax << std::endl;
        ;
        std::cout << "******" << std::endl;
        sumReal = sumReal + max;
    }
    sumReal = sumReal / 10;
    double deviation = (double)sumReal / (double)bestSolution;
    std::cout << "Srednie odchylenie: " << deviation << std::endl;
    std::cout << "Sredni czas: " << time / 10 << std::endl;
}