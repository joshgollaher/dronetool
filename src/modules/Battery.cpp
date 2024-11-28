#include <Modules/Battery.h>

namespace DroneTool
{
    void Battery::update(double time_step, Drone& drone)
    {
        Module::update(time_step, drone);

        // FIXME: Get motor currents, calculate power drain
    }
}
