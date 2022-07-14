#ifndef POPULATION_H
#define POPULATION_H

#include <string>
#include <vector>
#include "Human.h"
#include "Vaccine.h"

using Humans = std::vector<Human>;

class Population
{
public:
    Population() = default;
    void Prepare(int side);
    bool Administer(std::vector<Vaccine>& doses);
    void Add(const Human& aHuman);
    void DoSimulationStep();
    Humans::size_type Size() const;
    void AgeReport() const;
    void Report() const;
    void DumpPopulation() const;

private:
    void MoveCreatures();
    void MakeContacts();
    void EvaluateCreatureStates();

    Humans humans;
    std::string name;
};

#endif
