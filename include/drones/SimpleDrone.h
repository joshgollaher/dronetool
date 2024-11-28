#ifndef SIMPLEDRONE_H
#define SIMPLEDRONE_H

#include <Drone.h>

#include "modules/Battery.h"
#include "modules/Rotor.h"

namespace DroneTool
{
    class SimpleDrone final : public Drone
    {
    public:

        SimpleDrone();
        ~SimpleDrone();

        void setup() override;
        void update() override;

        [[nodiscard]] std::vector<class Module*> modules() const override
        {
            return {};
        }

    private:
        Battery* m_battery;
        std::tuple<Rotor, Rotor, Rotor, Rotor>* m_rotors{};
    };
}

#endif