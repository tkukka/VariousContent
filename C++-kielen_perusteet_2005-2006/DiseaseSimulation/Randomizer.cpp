#include <memory>
#include <iostream>
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
