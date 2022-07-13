#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <vector>
#include <random>

class Randomizer
{
public:
    static Randomizer* GetRandomizer();
    int RandomNumber(int min, int max);
    void SetWeights(const std::vector<double>& weights);
    int WeighedNumber();
    void RandomSample(const std::vector<int>& population, std::vector<int>& out, std::vector<int>::size_type size);

private:
    Randomizer();
    Randomizer(const Randomizer&) = delete;
    Randomizer(Randomizer&&) = delete;
    Randomizer& operator=(const Randomizer&) = delete;
    Randomizer& operator=(Randomizer&&) = delete;
    
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distrib;
    std::discrete_distribution<int> w_disc_distrib;
    std::discrete_distribution<int>::param_type wd_params;
};

#endif
