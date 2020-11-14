#include "Specimen.hpp"

RandomGenerator Specimen::randomGen;

Specimen::Specimen(int uSize)
{
    size = uSize;
}

void Specimen::fill()
{
    for (int a = 0; a < size; a++)
    {
        int newGene = rand()%2;
        genes.push_back(newGene);
    }
}