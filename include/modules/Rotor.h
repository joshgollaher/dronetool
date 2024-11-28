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

        Rotor(const double max_rpm, Distribution rpm_thrust_curve) : m_rpm_thrust_curve(std::move(rpm_thrust_curve)), m_max_rpm(max_rpm), m_current_rpm(0) {}

        [[nodiscard]] std::string name() const override { return "Rotor"; }
        [[nodiscard]] std::string print_state() const override;

        void set_input(double duty_cycle); // [0.0, 1.0]

        void update(double time_step, Drone& drone) override;  // FIXME: We do NOT model rotor inertia! This is wrong!

    private:
        Distribution m_rpm_thrust_curve;
        double m_max_rpm;
        double m_current_rpm;
    };
}

#endif
