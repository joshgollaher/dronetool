#ifndef DRONE_H
#define DRONE_H
#include <tuple>

namespace DroneTool
{
    // Sensors will be specified by subclass drones
    class Drone
    {
        using Vector3 = std::tuple<double, double, double>;
        using Vector4 = std::tuple<double, double, double, double>;

    public:
        virtual ~Drone() = default;

        virtual void setup() = 0;
        virtual void update() = 0;

        [[nodiscard]] Vector3 position() const { return m_position; }
        [[nodiscard]] Vector3 velocity() const { return m_velocity; }
        [[nodiscard]] Vector3 acceleration() const { return m_acceleration; }
        [[nodiscard]] Vector3 rotation() const { return m_rotation; }
        [[nodiscard]] Vector3 angular_velocity() const { return m_angular_velocity; }

        [[nodiscard]] Vector4 rotor_rates() const { return m_rotor_rates; }

    protected:
        Vector3 m_position;
        Vector3 m_velocity;
        Vector3 m_acceleration;
        Vector3 m_rotation;  // Maybe switch to quaternions, to avoid gimbal lock
        Vector3 m_angular_velocity;

        Vector4 m_rotor_rates;
    };
}

#endif