#include <iostream>
#include <SFML/Graphics.hpp>

#include <Simulation.h>
#include <drones/SimpleDrone.h>

#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>

#include "SlidingBuffer.h"

int main()
{
    DroneTool::Simulation simulation(new DroneTool::SimpleDrone{});
    simulation.initialize(100, 100);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Drone Sim");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);
    ImPlot::CreateContext();

    sf::Clock clock;

    DroneTool::SlidingBuffer<float, 100> plot_x_values{};
    plot_x_values.clear(0);

    DroneTool::SlidingBuffer<float, 100> plot_y_values{};
    plot_y_values.clear(0);

    DroneTool::SlidingBuffer<float, 100> plot_z_values{};
    plot_z_values.clear(0);

    while (window.isOpen())
    {
        const auto delta_time = clock.restart();

        sf::Event event{};
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        simulation.update(delta_time.asSeconds());
        ImGui::SFML::Update(window, delta_time);

        const auto [x, y, z] = simulation.drone()->position();
        plot_x_values.update(x);
        plot_y_values.update(y);
        plot_z_values.update(z);

        ImGui::Begin("Positional Data");
        if (ImPlot::BeginPlot("Position"))
        {
            ImPlot::PlotLine("X Position", plot_x_values.data(), plot_x_values.size());
            ImPlot::EndPlot();
        }
        if (ImPlot::BeginPlot("Y Position"))
        {
            ImPlot::PlotLine("Y Position", plot_y_values.data(), plot_y_values.size());
            ImPlot::EndPlot();
        }
        if (ImPlot::BeginPlot("Z Position"))
        {
            ImPlot::PlotLine("Z Position", plot_z_values.data(), plot_z_values.size());
            ImPlot::EndPlot();
        }
        ImGui::End();

        ImGui::Begin("Drone Modules");

        for (auto* module : simulation.drone()->modules())
        {
            ImGui::Text(std::format("{}: {}", module->name(), module->print_state()).c_str());
            module->imgui_tools();
            ImGui::Separator();
        }

        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}

