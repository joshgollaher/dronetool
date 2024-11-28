#include <iostream>
#include <SFML/Graphics.hpp>

#include <Simulation.h>
#include <drones/SimpleDrone.h>

#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>

int main()
{
    DroneTool::Simulation simulation(new DroneTool::SimpleDrone{});
    simulation.initialize(100, 100);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Drone Sim");
    window.setFramerateLimit(120);

    ImGui::SFML::Init(window);
    ImPlot::CreateContext();

    sf::Clock clock;

    float xs[1000], ys[1000], zs[1000];
    memset(xs, 0, 1000 * sizeof(float));
    memset(ys, 0, 1000 * sizeof(float));
    memset(zs, 0, 1000 * sizeof(float));

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

        for (int i = 1; i < 1000; i++)
        {
            xs[i-1] = xs[i];
        }

        const auto [x, y, z] = simulation.drone()->position();
        xs[999] = static_cast<float>(x);
        ys[999] = static_cast<float>(y);
        zs[999] = static_cast<float>(z);

        ImGui::Begin("Positional Data");
        if (ImPlot::BeginPlot("Position"))
        {
            ImPlot::PlotLine("X Position", xs, 1000);
            ImPlot::PlotLine("Y Position", ys, 1000);
            ImPlot::PlotLine("Z Position", zs, 1000);
            ImPlot::EndPlot();
        }
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}

