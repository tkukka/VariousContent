#include <memory>
#include <stdexcept>
#include <cmath>
#include "Simulator.h"
#include "Vaccine.h"

inline constexpr int SimulationStepsInHour = 4;
inline constexpr int VaccinationStart = 1 * SimulationStepsInHour;
inline constexpr int VaccinationSpacing = 2 * SimulationStepsInHour;

Simulator::Simulator() :
    params{false, 0, 0, 0, "", 0, 0},
    side{0},
    totalSteps{0},
    stepNum{0},
    administer_more_vaccines{true}
{

}

void Simulator::SetParameters(const Parameters& p)
{
    params = p;
    side = static_cast<int>(std::lround(std::sqrt(params.area)));
}

void Simulator::Prepare()
{
    std::cout << "Side length of the given area: " << side << '\n';
    humanFactory.CreateHumans(population, params.N_humans);
    population.Prepare(side);
    totalSteps = params.simulation_time * SimulationStepsInHour;

    population.AgeReport();

    std::cout << "\nInitial population:\n";
    population.Report();
}

void Simulator::Run()
{
    int vaccinationStep = 0;

    std::cout << "\nRunning the simulation...\n";
    for(stepNum = 0; stepNum < totalSteps; stepNum++)
    {
        population.DoSimulationStep();

        if (params.vaccine_used && administer_more_vaccines && stepNum >= VaccinationStart)
        {
            if (vaccinationStep % VaccinationSpacing == 0)
            {
                AddDoses(params.N_doses);
            }

            vaccinationStep++;
        }
    }

    std::cout << "\nSimulation result:\n";
    population.Report();
    population.DumpPopulation();
}

void Simulator::AddDoses(int amount)
{
    std::vector<Vaccine> doses;
    Vaccine v{params.vaccine_name, params.effectiveness};

    for (int i = 0; i < amount; i++)
    {
        doses.push_back(v);
    }

    administer_more_vaccines = population.Administer(doses);
}

Simulator* Simulator::GetSimulator()
{
    static std::unique_ptr<Simulator> sim;

    if (!sim)
    {
        sim.reset(new Simulator);
        std::cout << "Created Simulator\n";
    }

    return sim.get();
}

int parse_int(const char* str)
{
    int ret = 0;
    const std::string s{str};

    try
    {
        ret = std::stoi(s);
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Invalid argument: " << s << '\n';
    }

    catch(const std::out_of_range& e)
    {
        std::cout << "Out of numeric range\n";
    }
    return ret;
}
