#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "Randomizer.h"

Randomizer::Randomizer() : rd(), gen(rd())
{

}

Randomizer* Randomizer::GetRandomizer()
{
    static std::unique_ptr<Randomizer> rnd;

    if (!rnd)
    {
        rnd.reset(new Randomizer);
        std::cout << "Created Randomizer\n";
    }

    return rnd.get();
}

int Randomizer::RandomNumber(int min, int max)
{
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}

int Randomizer::RandomCategory(const std::vector<double>& weights)
{
     std::discrete_distribution<int> dist(weights.cbegin(), weights.cend());
     return dist(gen);
}

void Randomizer::RandomSample(const std::vector<int>& population, std::vector<int>& out, std::vector<int>::size_type size)
{
    std::sample(population.cbegin(), population.cend(), std::back_inserter(out), size, gen);
}
