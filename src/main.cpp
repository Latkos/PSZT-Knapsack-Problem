#include "ProblemInstance.hpp"
#include "Tester.hpp"
#include "Interface.hpp"
#include <iostream>
#include <random>
#include <fstream>

int main()
{
    ProblemInstance problem;
    Interface interface(problem);
    interface.askUserToChoose();
    std::cout << "done" << std::endl;
}