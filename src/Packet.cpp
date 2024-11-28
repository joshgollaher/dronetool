#include <Packet.h>

namespace DroneTool
{
    std::vector<uint8_t> make_packet(const PacketCommand command, std::vector<uint8_t> data)
    {
        std::vector<uint8_t> packet;

        // ReSharper disable once CppRedundantCastExpression
        packet.push_back(static_cast<uint8_t>(command));

        const uint16_t size = data.size();
        packet.push_back((size & 0xFF00 >> 8));
        packet.push_back((size & 0x00FF));

        packet.insert(packet.end(), data.begin(), data.end());

        // Don't feel like doing CRC
        uint8_t checksum = command;
        checksum ^= (size & 0xFF00 >> 8);
        checksum ^= (size & 0x00FF);
        for (const auto byte : data)
        {
            checksum ^= byte;
        }
        packet.push_back(checksum);

        return packet;
    }

}
