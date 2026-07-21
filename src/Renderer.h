#pragma once

#include "Simulation.h"

#include <SFML/Graphics.hpp>

class Renderer
{
public:
    Renderer(sf::RenderWindow& window);

    void update(float deltaTime);

    void draw(
        const Simulation& simulation,
        float fps);

    sf::Vector2f screenToWorld(
        const sf::Vector2i& pixel) const;

private:
    sf::RenderWindow& window;
    sf::View camera;

    sf::Font font;
    sf::Text* fpsText = nullptr;

    float cameraSpeed;
};