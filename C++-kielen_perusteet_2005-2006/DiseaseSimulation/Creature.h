#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include "Position.h"


enum class Health : int
{
    Healthy = 0,
    Sick,
    VerySick,
    Dead
};

enum class Direction : int
{
    North = 0,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest
};

class Creature
{
public:
    Creature();
    Creature(const std::string& aName, int anAge, Health aState);
    virtual void Move(Direction aDirection);
    virtual void Contact(Creature& other);
    void SetAge(int anAge) { age = anAge; }
    int Age() const { return age; }
    void SetName(const std::string& aName) { name = aName; }
    std::string Name() const { return name; }
    void SetPosition(const Position& aPosition) { position = aPosition; }
    const Position& GetPosition() const { return position; }
    void SetState(Health aState) { state = aState; }
    Health GetState() const { return state; }
    virtual void EvaluateState();
    virtual ~Creature() = default;

private:
    std::string name;
    Position position;
    int age;
    Health state;
};

#endif
