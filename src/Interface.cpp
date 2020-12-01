#include "Interface.hpp"

Interface::Interface(ProblemInstance &givenProblem)
{
    problem = givenProblem;
}

void Interface::askUserToChoose()
{
    std::cout << "Program pozwala na rozwiazanie problemu plecakowego algorytmem ewolucyjnym" << std::endl;
    std::cout << "Dla demonstracji program dziala w dwoch trybach-pojedyncza instancja i testowy" << std::endl;
    std::cout << "Dla pojedynczej instancji (prosimy wybrac 1) problem wygeneruje instancje o podanych parametrach" << std::endl;
    std::cout << "Dla testu mozna bedzie zreplikowac wyniki doswiadczen poprzez wybor odpowiedniego testu" << std::endl;
    std::cout << "Prosimy wybrac 1 dla pojedynczego problemu lub 2 dla testowania" << std::endl;
    std::cout << "*********************************************************" << std::endl;
    int number = 0;
    while (true)
    {
        std::cin >> number;
        if (number == 1)
        {
            handleOneRun();
            break;
        }
        else if (number == 2)
        {
            handleTesting();
            break;
        }
        else
            std::cout << "Prosimy wybrac 1 lub 2" << std::endl;
    }
}

void Interface::handleOneRun()
{
    std::cout << "Problem wygeneruje podana ilosc przedmiotow o wadze od 1 do 15, srednio 8"<<std::endl;
    std::cout << "Ilosc przedmiotow (najlepiej dziala w badanym przedziale od 50 do 150)" << std::endl;
    std::cin >> problem.problemSize;
    std::cout << "Rozmiar plecaka (im mniejszy tym trudniejszy problem, np. dla 150 przedmiotow sumarycznie waza okolo 1200, czyli 600 to latwy problem, 60 to trudny problem" << std::endl;
    std::cin >> problem.knapsackSize;
    Tester tester(problem);
    std::cout << "**********************************" << std::endl;
    tester.runOnce();
}

void Interface::handleTesting()
{
    Tester tester(problem);
    std::cout << "Ktory z zawartych testow przeprowadzonych w dokumentacji zreplikowac?" << std::endl;
    std::cout << "1. Pelne testowanie (BYLY TO BARDZO DLUGIE, WIELOGODZINNE TESTY MAJACE NA CELU DOBRANIE PARAMETROW)" << std::endl;
    std::cout << "2. Wplyw rozmiaru populacji" << std::endl;
    std::cout << "3. Wplyw ilosci generacji" << std::endl;
    std::cout << "4. Wplyw prawdopodobienstwa mutacji" << std::endl;
    std::cout << "5. Wplyw czynnika S (stosunku pojemnosci plecaka do sumarycznej wagi przedmiotow) na czas wykonania i jakosc algorytmu" << std::endl;
    std::cout << "6. Analiza danych skorelowanych i nieskorelowanych" << std::endl;
    std::cout << "7. Przykladowy przebieg wzrostu fitness'u dla kolejnych pokolen" << std::endl;
    std::cout << "8. Przykladowy wplyw czynnika mutacji na przebieg wzrostu fitness'u dla kolejnych pokolen" << std::endl;
    int number = 0;
    std::cin >> number;
    switch (number)
    {
    case 1:
        tester.fullTesting();
        break;

    case 2:
        tester.testPopulationSizeForOptimum();
        break;

    case 3:
        tester.testGenerationsForOptimum();
        break;

    case 4:
        tester.testMutationRateForOptimum();
        break;

    case 5:
        tester.testKnapsackSize();
        break;

    case 6:
        tester.testPisinger("dane1.txt");
        tester.testPisinger("dane2.txt");
        tester.testPisinger("dane3.txt");
        break;

    case 7:
        tester.testFitnessByGeneration();
        break;

    case 8:
        tester.testFitnessByGenerationByMutation();
        break;

    default:
        std::cout << "Wybrano inna opcje niz liczba od 1 do 6, program zakonczy dzialanie" << std::endl;
    }
}