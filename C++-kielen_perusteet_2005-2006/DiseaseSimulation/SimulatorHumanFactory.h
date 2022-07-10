#ifndef SIMULATOR_HUMAN_FACTORY_H
#define SIMULATOR_HUMAN_FACTORY_H

#include "Population.h"

class SimulatorHumanFactory
{
public:

    SimulatorHumanFactory() = default;
    void CreateHumans(Population& toPopulation, int N) const;

private:

};

#endif
