#include <iostream>

#include <Simulation.h>
#include <drones/SimpleDrone.h>

int main()
{
    DroneTool::Simulation simulation(new DroneTool::SimpleDrone{});
    simulation.initialize(100, 100);

    for (int i = 0; i < 1000; ++i)
    {
        simulation.update(1.0 / 60);
    }

    return 0;
}

