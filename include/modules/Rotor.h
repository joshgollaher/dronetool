#ifndef ROTOR_H
#define ROTOR_H

#include <Modules/Module.h>
#include <Distribution.h>

#include <utility>

namespace DroneTool
{
    class Rotor final : public Module
    {
    public:

        Rotor(const double max_rpm, Distribution rpm_thrust_curve, Distribution rpm_power_draw_curve) : m_rpm_thrust_curve(std::move(rpm_thrust_curve)), m_rpm_power_draw_curve(std::move(rpm_power_draw_curve)), m_max_rpm(max_rpm), m_current_rpm(0) {}

        [[nodiscard]] std::string name() const override { return "Rotor"; }
        [[nodiscard]] std::string print_state() const override;

        void set_input(double duty_cycle); // [0.0, 1.0]

        [[nodiscard]] double duty_cycle() const { return m_current_rpm / m_max_rpm; }

        [[nodiscard]] double get_thrust() const;

        [[nodiscard]] double get_power_draw() const;

        void imgui_tools() override;

    private:

        void add_percent_duty_cycle(double amt);

        Distribution m_rpm_thrust_curve;
        Distribution m_rpm_power_draw_curve;
        double m_max_rpm;
        double m_current_rpm;

        static int _rotor_counts;
        int m_rotor_id = _rotor_counts++;
    };
}

#endif
