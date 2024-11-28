#ifndef SIMULATION_H
#define SIMULATION_H
#include <optional>

#include <Packet.h>

namespace DroneTool
{
    class Simulation
    {
    public:
        Simulation();

        void transmit_data(PacketCommand command, std::vector<uint8_t> data);
        std::optional<std::pair<PacketCommand, std::vector<uint8_t>>> receive_data();

    private:
        void build_environment();
    };
}

#endif
