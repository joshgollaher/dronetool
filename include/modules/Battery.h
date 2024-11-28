#ifndef BATTERY_H
#define BATTERY_H

#include <Modules/Module.h>

namespace DroneTool
{
    class Battery final : public Module {
    public:
        Battery(int mah);
        [[nodiscard]] std::string name() const override { return "Battery"; }
        [[nodiscard]] std::string print_state() const override;

    private:
        double voltage{0};
    };
}

#endif //BATTERY_H
