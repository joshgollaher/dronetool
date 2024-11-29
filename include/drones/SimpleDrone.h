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

    protected:
        void setup_bullet_rigid_body() override;

    private:

        const double m_mass_kg = 0.8;

        Battery* m_battery;
        Rotor* m_rotor_1;
        Rotor* m_rotor_2;
        Rotor* m_rotor_3;
        Rotor* m_rotor_4;

        std::vector<class Module*> m_modules;
    };
}

#endif