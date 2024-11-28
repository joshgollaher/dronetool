#ifndef DRONE_H
#define DRONE_H
#include <tuple>

namespace DroneTool
{
    class Drone
    {
    public:
        virtual ~Drone() = default;

        virtual void setup() = 0;
        virtual void update() = 0;

    protected:
        std::tuple<double, double, double> m_position;
        std::tuple<double, double, double> m_velocity;
        std::tuple<double, double, double> m_rotation;  // Maybe switch to quaternions, to avoid gimbal lock

        std::tuple<double, double, double, double> m_rotor_rates;
    };
}

#endif