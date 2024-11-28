#ifndef PACKET_H
#define PACKET_H

#include <cstdint>
#include <vector>

namespace DroneTool
{
    // Packet: [0xAA Marker, PacketCommand: u8, Length: u16, data: Length, Cumulative XOR: u8]
    enum PacketCommand : uint8_t
    {
        FLY_HOME = 0,
        LATERAL_MOVE,
        POWER,
        LAND,
        STOP
    };

    std::vector<uint8_t> make_packet(PacketCommand command, std::vector<uint8_t> data);

}

#endif
