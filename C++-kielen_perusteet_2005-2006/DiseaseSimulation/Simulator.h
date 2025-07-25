#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <string>
#include <vector>

#include "Population.h"
#include "SimulatorHumanFactory.h"

inline constexpr int ARG_AREA = 1;
inline constexpr int ARG_N_HUMANS = 2;
inline constexpr int ARG_SIMULATION_TIME = 3;
inline constexpr int ARG_VACCINE_NAME = 4;
inline constexpr int ARG_N_DOSES = 5;
inline constexpr int ARG_EFFECTIVENESS = 6;

struct Parameters
{
    bool vaccine_used = false;
    int area = 51076;
    int N_humans = 2853;
    int simulation_time = 24;
    std::string vaccine_name;
    int N_doses;
    int effectiveness;
};


class Simulator
{
public:
    void SetParameters(const Parameters& p);
    void Prepare();
    void Run();
    int SimulationSteps() const  { return totalSteps; }
    static Simulator* GetSimulator();
    
private:
    Simulator();
    Simulator(const Simulator&) = delete;
    Simulator(Simulator&&) = delete;
    Simulator& operator=(const Simulator&) = delete;
    Simulator& operator=(Simulator&&) = delete;

    //void DoStep();
    void AddDoses(int amount);

    Parameters params;
    //std::vector<Vaccine> doses;  // used only in one method
    Population population;
    const SimulatorHumanFactory humanFactory;
    int side;
    int totalSteps;
    int stepNum;
    bool administer_more_vaccines;
};

int parse_int(const char* str);

inline std::ostream& operator<<(std::ostream& o, const Parameters& p)
{

  o << "Area: " << p.area << " Humans: " << p.N_humans << " Sim.time: " << p.simulation_time << '\n';

  if (p.vaccine_used)
  {
     o << "vaccine: " << p.vaccine_name << " doses: " << p.N_doses << " effectiveness: " << p.effectiveness << '\n';
  }
 
  return o; 
}

#endif
