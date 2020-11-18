#ifndef SPECIMEN_HPP
#define SPECIMEN_HPP

#include "RandomGenerator.hpp"

#include <vector>
#include <algorithm>
class Specimen
{
private:
    int size;
    static RandomGenerator randomGen;

public:
    std::vector<int> genes;
    int fitness;
    Specimen(int uSize);
    void fill(double itemProbability);
};

#endif