#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

enum class AtomType
{
    Hydrogen,
    Oxygen,
    Carbon,
    Neon
};

class Atom
{
public:
    Atom();

    Atom(
        AtomType type,
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        float mass,
        float radius,
        const sf::Color& color
    );

    AtomType type;

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    float mass;
    float radius;

    sf::Color color;
};