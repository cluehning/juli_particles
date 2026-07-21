#include "Simulation.h"
#include "Renderer.h"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1600, 900}),
        "Atom Simulation",
        sf::Style::Default);

    window.setFramerateLimit(144);

    Simulation simulation;
    Renderer renderer(window);

    sf::Clock clock;

    float fps = 0.f;

    while (window.isOpen())
    {
        float deltaTime =
            clock.restart()
            .asSeconds();

        fps = 1.f /
            std::max(
                deltaTime,
                0.0001f);

        while (const auto event =
            window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* wheel =
                event->getIf<
                sf::Event::MouseWheelScrolled>())
            {
                sf::View view = window.getView();
                if (wheel->delta > 0)
                {
                    view.zoom(0.9f);
                }
                else
                {
                    view.zoom(1.1f);
                }
                window.setView(view);
            }
        }

        renderer.update(
            deltaTime);

        if (sf::Mouse::isButtonPressed(
            sf::Mouse::Button::Left))
        {
            renderer.screenToWorld(
                sf::Mouse::getPosition(
                    window));

            simulation.applyMouseForce(
                renderer.screenToWorld(
                    sf::Mouse::getPosition(
                    window)),
                true);
        }

        if (sf::Mouse::isButtonPressed(
            sf::Mouse::Button::Right))
        {
            simulation.applyMouseForce(
                renderer.screenToWorld(
                    sf::Mouse::getPosition(
                        window)),
                false);
        }

        simulation.update(
            deltaTime);

        renderer.draw(
            simulation,
            fps);
    }

    return 0;
}