
#include "Creature.h"

Creature::Creature() : Creature("", 0, Health::Healthy)
{

}

Creature::Creature(const std::string& aName, int anAge, Health aState) : name{aName}, position(), age{anAge}, state{aState}
{

}

void Creature::Move( [[maybe_unused]] Direction aDirection)
{

}

void Creature::Contact( [[maybe_unused]] Creature& other)
{

}

void Creature::EvaluateState()
{

}
