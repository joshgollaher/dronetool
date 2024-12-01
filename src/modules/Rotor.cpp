#include <algorithm>
#include <format>
#include <imgui.h>
#include <modules/Rotor.h>

namespace DroneTool
{
    int Rotor::_rotor_counts = 0;

    std::string Rotor::print_state() const
    {
        return std::format("RPM: {}/{}, F={:.2f}N, Duty={:.2f}%", m_current_rpm, m_max_rpm, m_rpm_thrust_curve.sample(m_current_rpm), duty_cycle() * 100);
    }

    void Rotor::set_input(const double duty_cycle)
    {
        m_current_rpm = m_max_rpm * duty_cycle;
    }

    double Rotor::get_thrust() const
    {
        return m_rpm_thrust_curve.sample(m_current_rpm);
    }

    double Rotor::get_power_draw() const
    {
        return m_rpm_power_draw_curve.sample(m_current_rpm);
    }

    void Rotor::imgui_tools()
    {
        if (ImGui::Button(std::format("-10%##{}", m_rotor_id).c_str()))
        {
            add_percent_duty_cycle(-0.1);
        }
        if (ImGui::Button(std::format("-5%##{}", m_rotor_id).c_str()))
        {
            add_percent_duty_cycle(-0.05);
        }
        if (ImGui::Button(std::format("-1%##{}", m_rotor_id).c_str()))
        {
            add_percent_duty_cycle(-0.01);
        }
        if (ImGui::Button(std::format("+1%##{}", m_rotor_id).c_str()))
        {
            add_percent_duty_cycle(0.01);
        }
        if (ImGui::Button(std::format("+5%##{}", m_rotor_id).c_str()))
        {
            add_percent_duty_cycle(0.05);
        }
        if (ImGui::Button(std::format("+10%##{}", m_rotor_id).c_str()))
        {
            add_percent_duty_cycle(0.1);
        }
    }

    void Rotor::add_percent_duty_cycle(const double amt)
    {
        const double new_dc = std::clamp<double>(duty_cycle() + amt, 0.0, 1.0);
        set_input(new_dc);
    }
}
