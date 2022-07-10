#ifndef VIRUS_H
#define VIRUS_H

#include <functional>
#include "Creature.h"

class Virus : public Creature
{
public:
    Virus() : Creature() {}
    Virus(const std::string& aName) : Creature{aName, 0, Health::Healthy} {}
    virtual void Contact(Creature& other) override;

private:

};

extern const Virus Birdflu;


inline bool operator==(const Virus& lhs, const Virus& rhs)
{
    return lhs.Name() == rhs.Name();
}

template<>
struct std::hash<Virus>
{
    std::size_t operator()(const Virus& aVirus) const noexcept
    {
        
        return std::hash<std::string>{}(aVirus.Name());
    }
};

#endif
