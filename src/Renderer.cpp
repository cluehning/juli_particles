#include "Renderer.h"

Renderer::Renderer(
    sf::RenderWindow& renderWindow)
    : window(renderWindow),
      cameraSpeed(800.f)
{
    camera =
        window.getDefaultView();

    if (!font.openFromFile(
        "assets/arial.ttf"))
    {
        // Handle error if font fails to load
    }

    fpsText = new sf::Text(
        font,
        "",
        18u);
    fpsText->setFillColor(
        sf::Color::White);
}

void Renderer::update(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::A))
    {
        camera.move({
            -cameraSpeed * deltaTime,
            0.f
        });
    }

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::D))
    {
        camera.move({
            cameraSpeed * deltaTime,
            0.f
        });
    }

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::W))
    {
        camera.move({
            0.f,
            -cameraSpeed * deltaTime
        });
    }

    if (sf::Keyboard::isKeyPressed(
        sf::Keyboard::Key::S))
    {
        camera.move({
            0.f,
            cameraSpeed * deltaTime
        });
    }

    window.setView(camera);
}

sf::Vector2f Renderer::screenToWorld(
    const sf::Vector2i& pixel) const
{
    return window.mapPixelToCoords(
        pixel,
        camera);
}

void Renderer::draw(
    const Simulation& simulation,
    float fps)
{
    window.clear(
        sf::Color(10,10,16));

    window.setView(camera);

    sf::CircleShape particle;

    for (const auto& atom :
         simulation.getAtoms())
    {
        particle.setRadius(
            atom.radius);

        particle.setOrigin({
            atom.radius,
            atom.radius
        });

        particle.setFillColor(
            atom.color);

        particle.setPosition(
            atom.position);

        window.draw(particle);
    }

    fpsText->setString(
        "FPS: " +
        std::to_string(
            static_cast<int>(fps)));

    auto uiView =
        window.getDefaultView();

    window.setView(uiView);

    fpsText->setPosition({
        10.f,
        10.f
    });

    window.draw(*fpsText);

    window.display();
}