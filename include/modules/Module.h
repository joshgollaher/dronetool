#ifndef MODULE_H
#define MODULE_H
#include <string>

namespace DroneTool
{
    class Module
    {
    public:
        virtual ~Module() = default;

        [[nodiscard]] virtual std::string name() const = 0;
        [[nodiscard]] virtual std::string print_state() const = 0;

        virtual void update(double time_step, class Drone& drone) {}
    };
}

#endif
