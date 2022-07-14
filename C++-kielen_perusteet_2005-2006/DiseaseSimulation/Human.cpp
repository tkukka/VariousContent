//#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "Human.h"
#include "Randomizer.h"

inline constexpr int AgeMin = 15;
inline constexpr int AgeMax = 45;
inline constexpr int InitialSpeedLow = 2;
inline constexpr int InitialSpeedHigh = 4;
inline constexpr int stepMeters = 2;

inline constexpr double ImmunityByChance = 0.05;  // 5%
inline constexpr double SpeedUp = 1.2;
inline constexpr double SlowDown = 0.8;
inline constexpr int SimulationHour = 4;

static double infection_prob(Health state, int age, int n_virus_contacts);

Human::Human() :
    Creature(std::string("Human ") + std::to_string(id++)),
    maxSpeed{0},
    speed{0},
    contactsWithVirus{0},
    hasBeenVaccinated{false},
    timeInfected{0}
{

}

void Human::SetMaxSpeed()
{
    if (Age() >= AgeMin && Age() <= AgeMax)
    {
        maxSpeed = InitialSpeedHigh;
    }
    else
    {
        maxSpeed = InitialSpeedLow;
    }

    speed = maxSpeed;
}

void Human::Move(Direction aDirection)
{
    double x_step = 0, y_step = 0;

    switch (aDirection)
    {
        default:
        case Direction::North:
        {
            y_step = stepMeters * speed;
        }
        break;

        case Direction::NorthEast:
        {
            x_step = stepMeters * speed;
            y_step = stepMeters * speed;
        }
        break;

        case Direction::East:
        {
            x_step = stepMeters * speed;
        }
        break;

        case Direction::SouthEast:
        {
            x_step = stepMeters * speed;
            y_step = -stepMeters * speed;
        }
        break;

        case Direction::South:
        {
            y_step = -stepMeters * speed;
        }
        break;

        case Direction::SouthWest:
        {
            x_step = -stepMeters * speed;
            y_step = -stepMeters * speed;
        }
        break;

        case Direction::West:
        {
            x_step = -stepMeters * speed;
        }
        break;

        case Direction::NorthWest:
        {
            x_step = -stepMeters * speed;
            y_step = stepMeters * speed;
        }
        break;
    }

    auto pos = GetPosition();
    int newX = static_cast<int>(std::clamp(pos.XPos() + x_step, 0.0, static_cast<double>(Position::Max() )));
    int newY = static_cast<int>(std::clamp(pos.YPos() + y_step, 0.0, static_cast<double>(Position::Max() )));
    pos.SetPosition(newX, newY);
    SetPosition(pos);
}

void Human::Contact(Creature& other)
{
    auto& o = static_cast<Human&>(other);

    if (o.isImmuneTo(Birdflu) || o.GetState() == Health::Dead)
    {
        return;
    }

    if (isCarrying(Birdflu) && timeInfected > 0)
    {
        static auto rnd = Randomizer::GetRandomizer();
        auto prob = infection_prob(o.GetState(), o.Age(), o.contactsWithVirus);
        bool infected = rnd->SingleTrial(prob);

        if (infected)
        {
            o.SetCarrying(Birdflu);
        }

        o.contactsWithVirus++;
    }
}

void Human::EvaluateState()
{

    if (isCarrying(Birdflu))
    {
        timeInfected++;
        auto st = GetState();

        // immunity chance
        if (timeInfected >= SimulationHour && st != Health::Dead)
        {
            static auto rnd = Randomizer::GetRandomizer();
            bool immunized = rnd->SingleTrial(ImmunityByChance);

            if (immunized)
            {
                GrantImmunity(Birdflu);
            }
        }


        if (timeInfected % SimulationHour == 0)
        {

            if (!isImmuneTo(Birdflu) )
            {
                switch (st)
                {
                    case(Health::Healthy):
                        SetState(Health::Sick);
                        speed *= SlowDown;
                        break;
                    case(Health::Sick):
                        SetState(Health::VerySick);
                        speed *= SlowDown;
                        break;
                    case(Health::VerySick):
                        SetState(Health::Dead);
                        speed = 0;
                        break;
                    case(Health::Dead):
                        break;
                }
            }
            else
            {
                switch (st)
                {
                    case(Health::Healthy):
                        carry.erase(Birdflu);
                        speed = maxSpeed;
                        break;
                    case(Health::Sick):
                        SetState(Health::Healthy);
                        speed *= SpeedUp;
                        break;
                    case(Health::VerySick):
                        SetState(Health::Sick);
                        speed *= SpeedUp;
                        break;
                    case(Health::Dead):
                        break;
                }
            }
        }
    }

}

void Human::Administer(const Vaccine& aVaccine)
{
    hasBeenVaccinated = true;
    vaccine = aVaccine;

    static auto rnd = Randomizer::GetRandomizer();
    bool immunized = rnd->SingleTrial(aVaccine.Effectiveness() / 100.0);

    if (immunized)
    {
        GrantImmunity(Birdflu);
    }

}

void Human::GrantImmunity(const Virus& aVirus)
{
    immune.insert(aVirus);
}

void Human::SetCarrying(const Virus& aVirus)
{
    if (!isImmuneTo(aVirus))
    {
        carry.insert(aVirus);
    }
}

bool Human::isImmuneTo(const Virus& aVirus) const
{
    return immune.find(aVirus) != immune.end();
}

bool Human::isCarrying(const Virus& aVirus) const
{
    return carry.find(aVirus) != carry.end();
}


static double infection_prob(Health state, int age, int n_virus_contacts)
{
    auto h = static_cast<int>(state);
    return 1.0 - 1.0 / (1 + n_virus_contacts * (h + std::fmax(0.1, std::abs(30 - age) / 10.0 ) ));
    //return (1 - n_virus_contacts * (h + std::fmax(0.1, std::abs(30 - age) / 10.0 ) ));
    //return 1.0 - 1.0 / std::exp(n_virus_contacts * (h + std::fmax(0.1, std::abs(30 - age) / 10.0 ) ));
}
