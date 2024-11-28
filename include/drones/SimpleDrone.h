#ifndef SIMPLEDRONE_H
#define SIMPLEDRONE_H

#include <Drone.h>

namespace DroneTool
{
    class SimpleDrone final : public Drone
    {
    public:
        void setup() override;
        void update() override;
    };
}

#endif