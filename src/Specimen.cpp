#include "Specimen.hpp"

RandomGenerator Specimen::randomGen;

Specimen::Specimen(int uSize)
{
    size = uSize;
    fitness=0;
}

void Specimen::fill(double itemProbability)
{
    for (int a = 0; a < size; a++)
    {
        double probability=randomGen.generateProbability();
        if (probability<itemProbability){
            genes.push_back(1);
        }
        genes.push_back(0);
    }
}
