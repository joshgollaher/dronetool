#include <drones/SimpleDrone.h>

namespace DroneTool
{
    static std::vector<double> generate_rpm_thrust_curve(const double max_rpm, const int steps) {
        std::vector<double> thrust_values;
        double k = 10.0; // Arbitrary scaling factor for thrust (adjust as needed)

        for (int i = 0; i < steps; ++i) {
            const double rpm = i * max_rpm / (steps - 1); // Evenly spaced RPM
            double thrust = k * std::log(rpm + 1); // Logarithmic thrust
            thrust_values.push_back(thrust);
        }
        return thrust_values;
    }

    SimpleDrone::SimpleDrone()
    {
        m_battery = new Battery(3150);

        constexpr double max_rotor_rpm = 14000;
        const Distribution rpm_thrust_curve(0, max_rotor_rpm, generate_rpm_thrust_curve(max_rotor_rpm, 100)); // Fill in the vector ({}) with the thrust values. Assume they will be evenly spaced, and a log-style curve
        const Distribution rpm_power_draw_curve(0, max_rotor_rpm, {0, 45}); // Linear curve for now
        m_rotors = new std::tuple(
            Rotor(max_rotor_rpm, rpm_thrust_curve, rpm_power_draw_curve),
            Rotor(max_rotor_rpm, rpm_thrust_curve, rpm_power_draw_curve),
            Rotor(max_rotor_rpm, rpm_thrust_curve, rpm_power_draw_curve),
            Rotor(max_rotor_rpm, rpm_thrust_curve, rpm_power_draw_curve)
        );

    }

    SimpleDrone::~SimpleDrone()
    {
        delete m_battery;
        delete m_rotors;
    }

    void SimpleDrone::setup()
    {
    }

    void SimpleDrone::update()
    {
    }
}
