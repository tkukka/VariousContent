#include <iostream>
#include "Simulator.h"

int main(int argc, char *argv[])
{
    using std::cout;

    Parameters p;
    
    if (argc == 1)
    {
        cout << "Using default parameters\n";
    }
    else if (argc == 4 || argc == 7)
    {
        p.area = parse_int(argv[ARG_AREA]);
        p.N_humans = parse_int(argv[ARG_N_HUMANS]);
        p.simulation_time = parse_int(argv[ARG_SIMULATION_TIME]);

        if (argc == 7)
        {
            p.vaccine_used = true;
            p.vaccine_name = argv[ARG_VACCINE_NAME];
            p.N_doses = parse_int(argv[ARG_N_DOSES]);
            p.effectiveness = parse_int(argv[ARG_EFFECTIVENESS]);
        }
    }
    else
    {
        cout << "Usage: " << argv[0] << " [<area> <number of humans> <simulation time> [ <vaccine name> <doses> <effectiveness>] ]\n";
        return 1;
    }

    cout << p;

    auto sim = Simulator::GetSimulator();
    sim->SetParameters(p);
    sim->Prepare();
    sim->Run();

    return 0;
}
