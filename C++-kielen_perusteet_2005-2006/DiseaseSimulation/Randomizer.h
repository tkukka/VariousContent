#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <vector>
#include <random>

class Randomizer
{
public:
    static Randomizer* GetRandomizer();
    int RandomNumber(int min, int max);
    int RandomCategory(const std::vector<double>& weights);
    
private:
    Randomizer();
    Randomizer(const Randomizer&) = delete;
    Randomizer(Randomizer&&) = delete;
    Randomizer& operator=(const Randomizer&) = delete;
    Randomizer& operator=(Randomizer&&) = delete;
    
    std::random_device rd;
    std::mt19937 gen;
};

#endif
