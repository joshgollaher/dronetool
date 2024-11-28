#include <Simulation.h>

namespace DroneTool
{
    Simulation::Simulation()
    {
        build_environment();
    }

    void Simulation::transmit_data(PacketCommand command, const std::vector<uint8_t> data)
    {

    }

    std::optional<std::pair<PacketCommand, std::vector<uint8_t>>> Simulation::receive_data()
    {
        return {};
    }

    void Simulation::build_environment()
    {

    }
}