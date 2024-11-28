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
        ~SimpleDrone() override;

        void setup() override;
        void update() override;

        [[nodiscard]] std::vector<class Module*> modules() const override
        {
            return m_modules;
        }

    private:
        Battery* m_battery;
        Rotor* m_rotor_1;
        Rotor* m_rotor_2;
        Rotor* m_rotor_3;
        Rotor* m_rotor_4;

        std::vector<class Module*> m_modules;
    };
}

#endif