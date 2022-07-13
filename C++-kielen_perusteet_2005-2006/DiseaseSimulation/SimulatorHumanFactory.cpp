#include <iostream>
#include "SimulatorHumanFactory.h"
#include "Human.h"

void SimulatorHumanFactory::CreateHumans(Population& toPopulation, int N) const
{
    
    if (N < 1)
    {
        std::cout << "Number of humans can't be less than 1\n";
        return;
    }

    for (int k = 0; k < N; k++)
    {
        toPopulation.Add(Human());
    }

    std::cout << "Created " << toPopulation.Size() << " humans\n";
}
