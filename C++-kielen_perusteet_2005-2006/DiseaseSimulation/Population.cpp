#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>
#include "Population.h"
#include "Randomizer.h"

inline constexpr int weight_age_0_9 = 10;
inline constexpr int weight_age_10_19 = 20;
inline constexpr int weight_age_20_29 = 25;
inline constexpr int weight_age_30_50 = 25;
inline constexpr int weight_age_51_100 = 20;

static const std::vector<double> WEIGHTS =
{
    weight_age_0_9,
    weight_age_10_19,
    weight_age_20_29,
    weight_age_30_50,
    weight_age_51_100
};

struct AgeSpan
{
    int min;
    int max;
};

inline constexpr const AgeSpan Age_Categories[] = { {0, 9}, {10, 19}, {20, 29}, {30, 50}, {51, 100} };

inline constexpr int N_Sick = 100;
inline constexpr int N_VerySick = 50;
inline constexpr int N_Dead = 2;

inline constexpr int N_Infected = 79;

static const std::string HumanText{"Human "};

inline constexpr int AgeSpeedMin = 15;
inline constexpr int AgeSpeedMax = 45;
inline constexpr int InitialSpeedLow = 2;      // [km/h]
inline constexpr int InitialSpeedHigh = 4;


inline constexpr const std::array<Direction, 8> DIRECTIONS
{
    Direction::North,
    Direction::NorthEast,
    Direction::East,
    Direction::SouthEast,
    Direction::South,
    Direction::SouthWest,
    Direction::West,
    Direction::NorthWest
};


// ------------------------    code     ------------------------------------


void Population::Prepare(int side)
{

    auto rnd = Randomizer::GetRandomizer();

    std::cout << "Population: " << humans.size() << " people\n";
    std::cout << "Setting up population ages, human positions, initial speeds\n";

    int hum_id = 0;
    Position pos;
    pos.SetMax(side - 1);

    std::vector<int> indices;

    for (auto& hum : humans)
    {
        hum.SetName(HumanText + std::to_string(hum_id));
        const auto cat = rnd->RandomCategory(WEIGHTS);
        auto age = rnd->RandomNumber(Age_Categories[cat].min, Age_Categories[cat].max);
        hum.SetAge(age);

        if (age >= AgeSpeedMin && age <= AgeSpeedMax)
        {
            hum.SetMaxSpeed(InitialSpeedHigh);
        }
        else
        {
            hum.SetMaxSpeed(InitialSpeedLow);
        }
        const auto x = rnd->RandomNumber(0, side - 1);
        const auto y = rnd->RandomNumber(0, side - 1);
        pos.SetPosition(x, y);
        hum.SetPosition(pos);

        indices.push_back(hum_id);
        hum_id++;
    }

    std::cout << "Setting up population health\n";

    std::random_device rd{};
    std::mt19937 gen(rd());
    std::vector<int> selected;
    std::sample(indices.cbegin(), indices.cend(), std::back_inserter(selected), N_Sick + N_VerySick + N_Dead, gen);

    int processed = 0;
    for (const auto& ind : selected)
    {
        if (processed < N_Sick)
        {
            humans.at(ind).SetState(Health::Sick);
        }
        else if (processed < (N_Sick + N_VerySick))
        {
            humans.at(ind).SetState(Health::VerySick);
        }
        else
        {
            humans.at(ind).SetState(Health::Dead);
        }
        processed++;
    }

    std::cout << "Setting up infected (" << N_Infected << ")\n";

    selected.clear();
    std::sample(indices.cbegin(), indices.cend(), std::back_inserter(selected), N_Infected, gen);

    for (const auto& ind : selected)
    {
        humans.at(ind).SetCarrying(Birdflu);
    }

    std::cout << '\n';
}

void Population::Administer(std::vector<Vaccine>& doses)
{
    static bool vaccines_needed = true;

    if (!vaccines_needed)
    {
        return;
    }

    //std::cout << "Administering " << doses.size() << " vaccines\n";
    std::vector<int> indices;

    // the first round vaccination
    int id = 0;
    for (const auto& hum : humans)
    {
        if (hum.GetState() != Health::Dead && !hum.isVaccinated())
        {
            indices.push_back(id);
        }

        id++;
    }

    // everybody is vaccinated. second round
    if (indices.empty())
    {
        int id = 0;
        for (const auto& hum : humans)
        {
            if(hum.GetState() != Health::Dead && !hum.isImmuneTo(Birdflu))
            {
                indices.push_back(id);
            }

            id++;
        }
    }

    // everybody is totally vaccinated.
    if (indices.empty())
    {
        vaccines_needed = false;
        std::cout << "There is no one suitable to receive a vaccine\n";
        return;
    }

    std::random_device rd{};
    std::mt19937 gen(rd());
    std::vector<int> selected;
    std::sample(indices.cbegin(), indices.cend(), std::back_inserter(selected), doses.size(), gen);

    for (const auto& ind : selected)
    {
        humans.at(ind).Administer(doses.back());
        doses.pop_back();
    }

    if (!doses.empty())
    {
        std::cout << "*** There were more vaccines than potential recipients ***\n";
    }

}

void Population::Add(const Human& aHuman)
{
    humans.push_back(aHuman);
}

void Population::DoSimulationStep()
{
    MoveCreatures();
    MakeContacts();
    EvaluateCreatureStates();
}

Humans::size_type Population::Size() const
{
    return humans.size();
}

void Population::MoveCreatures()
{
    auto rnd = Randomizer::GetRandomizer();

    for (auto& hum : humans)
    {
        if (hum.GetState() != Health::Dead)
        {
            const auto dir = rnd->RandomNumber(0, DIRECTIONS.size() - 1);
            hum.Move(DIRECTIONS[dir]);
        }
    }
}

void Population::MakeContacts()
{
    const auto size = humans.size();

    for (unsigned long i = 0; i < size; i++)
    {
        for (unsigned long j = i + 1; j < size; j++)
        {
            auto& human1 = humans[i];
            auto& human2 = humans[j];

            if (isNear(human1.GetPosition(), human2.GetPosition()))
            {
                human1.Contact(human2);
                human2.Contact(human1);
            }
        }
    }
}

void Population::EvaluateCreatureStates()
{
    for (auto& hum : humans)
    {
        hum.EvaluateState();
    }
}

void Population::AgeReport() const
{
    int age_0_9 = 0;
    int age_10_19 = 0;
    int age_20_29 = 0;
    int age_30_50 = 0;
    int age_51_plus = 0;

    for (const auto& hum : humans)
    {
        auto a = hum.Age();

        if ( a < 10)
        {
            age_0_9++;
        }
        else if (a >= 10 && a < 20)
        {
            age_10_19++;
        }
        else if (a >= 20 && a < 30)
        {
            age_20_29++;
        }
        else if (a >= 30 && a < 51)
        {
            age_30_50++;
        }
        else
        {
            age_51_plus++;
        }
    }

    auto sz = humans.size();
    std::cout << "Age distribution:\n";
    std::cout << "0 - 9: " << age_0_9 << " (" << (100.0 * age_0_9 / sz) << " %) [" << weight_age_0_9 << " %]\n";
    std::cout << "10 - 19: " << age_10_19 << " (" << (100.0 * age_10_19 / sz) << " %) [" << weight_age_10_19 << " %]\n";
    std::cout << "20 - 29: " << age_20_29 << " (" << (100.0 * age_20_29 / sz) << " %) [" << weight_age_20_29 << " %]\n";
    std::cout << "30 - 50: " << age_30_50 << " (" << (100.0 * age_30_50 / sz) << " %) [" << weight_age_30_50 << " %]\n";
    std::cout << "51 - 100: " << age_51_plus << " (" << (100.0 * age_51_plus / sz) << " %) [" << weight_age_51_100 << " %]\n";
}

void Population::Report() const
{
    int n_healthy = 0;
    int n_sick = 0;
    int n_verysick = 0;
    int n_dead = 0;

    int n_infected = 0;
    int n_healthy_infected = 0;
    int n_dead_infected = 0;
    int n_immune = 0;
    int n_dead_immune = 0;
    int n_immune_infected = 0;

    for (const auto& hum : humans)
    {
        switch (hum.GetState())
        {
            case Health::Healthy:
                n_healthy++;
                break;
            case Health::Sick:
                n_sick++;
                break;
            case Health::VerySick:
                n_verysick++;
                break;
            case Health::Dead:
                n_dead++;
                break;
        }

        if (hum.isCarrying(Birdflu))
        {
            n_infected++;

            if (hum.GetState() == Health::Healthy)
            {
                n_healthy_infected++;
            }
            else if (hum.GetState() == Health::Dead)
            {
                n_dead_infected++;
            }
        }

        if (hum.isImmuneTo(Birdflu))
        {
            n_immune++;

            if (hum.GetState() == Health::Dead)
            {
                n_dead_immune++;
            }

            if (hum.isCarrying(Birdflu))
            {
                n_immune_infected++;
            }
        }
    }

    std::cout << "Healthy: " << n_healthy << " Sick: " << n_sick << " VerySick: " << n_verysick << " Dead: " << n_dead << '\n';
    std::cout << "Total: " << (n_healthy + n_sick + n_verysick + n_dead) << " [" << humans.size() << "]\n";
    std::cout << "Infected: " << n_infected << " of which healthy " << n_healthy_infected << " and dead " << n_dead_infected << '\n';
    std::cout << "Immune: " << n_immune << " of which infected " << n_immune_infected << " and dead " << n_dead_immune << '\n';

}
