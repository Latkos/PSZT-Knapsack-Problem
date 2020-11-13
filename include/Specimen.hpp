#ifndef SPECIMEN_HPP
#define SPECIMEN_HPP

#include "RandomGenerator.hpp"

#include <vector>

class Specimen
{
private:
    int size;
    static RandomGenerator randomGen;

public:
    std::vector<int> genes;
    Specimen(int uSize);
    void fill();
    int fitness();
};

#endif