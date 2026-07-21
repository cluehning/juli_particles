#include "Atom.h"

Atom::Atom()
    : type(AtomType::Hydrogen),
      position(0.f, 0.f),
      velocity(0.f, 0.f),
      acceleration(0.f, 0.f),
      mass(1.f),
      radius(2.f),
      color(sf::Color::White)
{
}

Atom::Atom(
    AtomType atomType,
    const sf::Vector2f& atomPosition,
    const sf::Vector2f& atomVelocity,
    float atomMass,
    float atomRadius,
    const sf::Color& atomColor)
    : type(atomType),
      position(atomPosition),
      velocity(atomVelocity),
      acceleration(0.f, 0.f),
      mass(atomMass),
      radius(atomRadius),
      color(atomColor)
{
}