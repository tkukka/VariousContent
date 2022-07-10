#ifndef HUMAN_H
#define HUMAN_H

#include <unordered_set>
#include "Vaccine.h"
#include "Virus.h"

using Immunity = std::unordered_set<Virus>;
using Carrying = std::unordered_set<Virus>;

class Human : public Creature
{
public:
    Human();
    void SetMaxSpeed(int aSpeed);
    virtual void Move(Direction aDirection) override;
    virtual void Contact(Creature& other) override;
    virtual void EvaluateState() override;
    void Administer(const Vaccine& aVaccine);
    void GrantImmunity(const Virus& aVirus);
    void SetCarrying(const Virus& aVirus);
    bool isImmuneTo(const Virus& aVirus) const;
    bool isCarrying(const Virus& aVirus) const;

private:
    Immunity immune;
    Carrying carry;
    int maxSpeed;
    double speed;
    int contactsWithVirus;
    bool hasBeenVaccinated;
    int timeInfected;
};

#endif