#ifndef BATTERY_H
#define BATTERY_H

#include <format>
#include <Modules/Module.h>

namespace DroneTool
{
    class Battery final : public Module {
    public:
        explicit Battery(const int mah) : m_mah(mah), m_charge(100) {}
        [[nodiscard]] std::string name() const override { return "Battery"; }
        [[nodiscard]] std::string print_state() const override { return std::format("{:.3f}%", m_charge); }

        void update(double time_step, class Drone& drone) override;

    private:
        int m_mah;
        double m_charge;
    };
}

#endif //BATTERY_H