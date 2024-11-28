#ifndef SIMULATION_H
#define SIMULATION_H

namespace DroneTool
{
    class Simulation
    {
    public:
        Simulation();

        void transmit_data();
        void receive_data();

    private:
        void build_environment();
    };
}

#endif
