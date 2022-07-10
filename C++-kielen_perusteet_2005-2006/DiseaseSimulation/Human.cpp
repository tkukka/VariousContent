//#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "Human.h"
#include "Randomizer.h"

inline constexpr int stepMeters = 2;
inline constexpr int ImmunityByChance = 5;
inline constexpr int SpeedUp = 1.2;
inline constexpr int SlowDown = 0.8;
inline constexpr int SimulationHour = 4;

static double infection_prob(Health state, int age, int n_virus_contacts);



Human::Human() :
    Creature(),
    maxSpeed{0},
    speed{0},
    contactsWithVirus{0},
    hasBeenVaccinated{false},
    timeInfected{0}
{

}
void Human::SetMaxSpeed(int aSpeed)
{
    maxSpeed = aSpeed;
    speed = maxSpeed;
}

void Human::Move(Direction aDirection)
{
    double x_step = 0, y_step = 0;

    switch(aDirection)
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

    if(isCarrying(Birdflu) && timeInfected > 0)
    {
        auto p = 100 * infection_prob(o.GetState(), o.Age(), o.contactsWithVirus);
        auto rnd = Randomizer::GetRandomizer();
        auto x = rnd->RandomNumber(1, 100);

        if (x < p)
        {
            o.SetCarrying(Birdflu);
        }

        o.contactsWithVirus++;
    }


}

void Human::EvaluateState()
{

    if(isCarrying(Birdflu))
    {
        timeInfected++;
        auto st = GetState();

        // immunity chance
        if (timeInfected >= SimulationHour && st != Health::Dead)
        {
            auto rnd = Randomizer::GetRandomizer();
            auto x = rnd->RandomNumber(0, 99);
            if (x < ImmunityByChance)
            {
                GrantImmunity(Birdflu);
            }
        }


        if(timeInfected % SimulationHour == 0)
        {

            if(!isImmuneTo(Birdflu) )
            {
                switch(st)
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
                        break;
                    case(Health::Dead):
                        break;
                }
            }
            else
            {
                switch(st)
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

    auto rnd = Randomizer::GetRandomizer();
    auto x = rnd->RandomNumber(0, 99);
    if (x < vaccine.Effectiveness())
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
    if(!isImmuneTo(aVirus))
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
