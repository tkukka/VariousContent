#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <iostream>

#include "Position.h"

enum class Direction : int;

enum class Health : int
{
    Healthy = 0,
    Sick,
    VerySick,
    Dead
};

inline std::ostream& operator<<(std::ostream& o, Health h)
{
    o << static_cast<int>(h);
    return o;
}


class Creature
{
public:
    Creature(const std::string& aName = "", int anAge = 0, Health aState = Health::Healthy);
    virtual void Move(Direction aDirection);
    virtual void Contact(Creature& other);
    void SetAge(int anAge) { age = anAge; }
    int Age() const { return age; }
    //void SetName(const std::string& aName) { name = aName; }
    std::string Name() const { return name; }
    void SetPosition(const Position& aPosition) { position = aPosition; }
    const Position& GetPosition() const { return position; }
    void SetState(Health aState) { state = aState; }
    Health GetState() const { return state; }
    virtual void EvaluateState();
    virtual ~Creature() = default;

private:
    const std::string name;
    Position position;
    int age;
    Health state;
};

#endif
