#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <iostream>
#include <string>
#include "ProblemInstance.hpp"
#include "Tester.hpp"

class Interface
{
private:
    void handleOneRun();
    void handleTesting();
    ProblemInstance problem;

public:
    Interface(ProblemInstance &givenProblem);
    void askUserToChoose();
};

#endif