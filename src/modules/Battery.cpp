#include <imgui.h>
#include <Modules/Battery.h>

namespace DroneTool
{
    void Battery::imgui_tools()
    {
        if (ImGui::Button("Kill"))
        {
            m_charge = 0;
        }
        if (ImGui::Button("Recharge"))
        {
            m_charge = 100;
        }
    }

    void Battery::update(const double time_step, Drone& drone)
    {
        Module::update(time_step, drone);

        // FIXME: Get motor currents, calculate power drain

    }
}
