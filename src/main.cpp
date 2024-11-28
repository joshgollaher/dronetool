#include <iostream>
#include <SFML/Graphics.hpp>

#include <Simulation.h>
#include <drones/SimpleDrone.h>

#include <imgui.h>
#include <imgui-SFML.h>

int main()
{
    DroneTool::Simulation simulation(new DroneTool::SimpleDrone{});
    simulation.initialize(100, 100);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Drone Sim");
    window.setFramerateLimit(120);
    ImGui::SFML::Init(window);

    sf::Clock clock;

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

        // TODO: Add components...

        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}

