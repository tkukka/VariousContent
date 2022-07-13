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
    const std::uniform_int_distribution<int>::param_type params(min, max);

    return distrib(gen, params);
}

void Randomizer::SetWeights(const std::vector<double>& weights)
{
    const std::discrete_distribution<int>::param_type params(weights.cbegin(), weights.cend());
    wd_params = params;
}

int Randomizer::WeighedNumber()
{
     return w_disc_distrib(gen, wd_params);
}

void Randomizer::RandomSample(const std::vector<int>& population, std::vector<int>& out, std::vector<int>::size_type size)
{
    std::sample(population.cbegin(), population.cend(), std::back_inserter(out), size, gen);
}
