#include <format>
#include <modules/Rotor.h>

namespace DroneTool
{
    std::string Rotor::print_state() const
    {
        return std::format("RPM: {}/{}, F={:.2f}N", m_current_rpm, m_max_rpm, m_rpm_thrust_curve.sample(m_current_rpm));
    }

    void Rotor::set_input(const double duty_cycle)
    {
        m_current_rpm = m_max_rpm * duty_cycle;
    }
}
