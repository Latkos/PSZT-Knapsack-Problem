#include <iostream>
#include <random>
#include "ProblemInstance.hpp"

void ProblemInstance::initializeWeightsAndValues()
{
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
    population.clear();                                            //in case this function is called more than once
    double itemProbability = knapsackSize / (2 * totalItemWeight); //our own function ensuring the amount of items depends on how many items there are and how much knapsack can hold
    for (int a = 0; a < populationSize; a++)
    {
        Specimen newSpecimen(problemSize);
        newSpecimen.fill(itemProbability);
        population.push_back(newSpecimen);
    }
}

void ProblemInstance::displayWeightsAndValues()
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
        population[a].fitness = individualFitness(a);
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
        return sumValues;
    else
        return 0;
}

int ProblemInstance::maxFitness()
{
    int max = 0;
    for (int a = 0; a < populationSize; a++)
    {
        if (population[a].fitness > max)
            max = population[a].fitness;
    }
    return max;
}

bool compareFitness(Specimen a, Specimen b) //needed for std::sort
{
    return a.fitness > b.fitness;
}

void ProblemInstance::select() //tournament selection
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
        if (population[random1].fitness > population[random2].fitness) //pick two specimen for the tournament
            tempPopulation.push_back(population[random1]);
        else
            tempPopulation.push_back(population[random2]);
    }
    population.clear();
    population = tempPopulation;
}

void ProblemInstance::smallMutate(double mutationRate) //our version of mutation, flips one bit
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
void ProblemInstance::crossover() //the standard crossover we use
{
    std::shuffle(population.begin(), population.end(), std::default_random_engine(randomGen.seed));
    std::vector<Specimen> tempPopulation;
    for (int a = 0; a < populationSize; a++)
    {
        double probability = randomGen.generateProbability();
        if (probability > crossoverRate || a == populationSize - 1)
            tempPopulation.push_back(population[a]);
        else
        {
            Specimen child(problemSize);
            int point = randomGen.generateInt(0, problemSize - 1);
            for (int b = 0; b < point; b++)
            {
                child.genes.push_back(population[a].genes[b]);
            }
            for (int b = point; b < problemSize; b++)
            {
                child.genes.push_back(population[a + 1].genes[b]);
            }
            tempPopulation.push_back(child);
        }
    }
    population.clear();
    population = tempPopulation;
}

int ProblemInstance::max(int a, int b) //needed for dynamic programming
{
    return (a > b) ? a : b;
}

int ProblemInstance::solveDynamic() //dynamic programming solution
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

void ProblemInstance::displayBestSpecimen()
{
    for (int a = 0; a < populationSize; a++)
    {
        if (population[a].fitness == maxFitness())
        {
            std::cout << "\nNajlepszy osobnik:" << std::endl;
            std::vector<int> itemNumbers;
            for (int b = 0; b < problemSize; b++)
            {
                std::cout << population[a].genes[b];
                if (population[a].genes[b] == 1)
                {
                    itemNumbers.push_back(b);
                }
            }
            std::cout << "\n Czyli przedmioty do wziecia, liczac od 1 do "<<problemSize<<" to:";
            for (unsigned int b = 0; b < itemNumbers.size(); b++)
                std::cout << itemNumbers[b]+1<<" ";
            std::cout<<std::endl;
            return;
        }
    }
}

    void ProblemInstance::mutate() //not used in our current solution, left if someone potentially wants to see how it works
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

    void ProblemInstance::initializePopulationWithZeroes() //not used in our solution, left if someone potentially wants to see how it works
    {
        for (int a = 0; a < populationSize; a++)
        {
            for (int b = 0; b < problemSize; b++)
            {
                population[a].genes[b] = 0;
            }
        }
    }

    void ProblemInstance::uniformCrossover() //not used in our solution, left if someone potentially wants to see how it works
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

    void ProblemInstance::crossover2() //the crossover we abandoned, left if someone potentially wants to see how it works
    {
        std::vector<Specimen> tempPopulation;
        for (int a = 0; a < populationSize / 2; a++)
        {
            double probability = randomGen.generateProbability();
            if (probability > 0.8) //CrossoverRatio crossover ratio
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