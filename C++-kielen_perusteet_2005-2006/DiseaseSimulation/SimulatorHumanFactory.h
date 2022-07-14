#ifndef SIMULATOR_HUMAN_FACTORY_H
#define SIMULATOR_HUMAN_FACTORY_H

class Population;

class SimulatorHumanFactory
{
public:

    SimulatorHumanFactory() = default;
    void CreateHumans(Population& toPopulation, int N) const;

private:

};

#endif
