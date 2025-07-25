#ifndef VACCINE_H
#define VACCINE_H

#include <string>

class Vaccine
{
public:
    Vaccine(): effectiveness{0} {}
    Vaccine(const std::string& aName, int eff) : effectiveness{eff}, name{aName} {}
    int Effectiveness() const { return effectiveness; }
    const std::string& Name() const { return name; }
    
private:
    int effectiveness;
    std::string name;
};

extern const Vaccine VaccineA;
extern const Vaccine VaccineB;

#endif
