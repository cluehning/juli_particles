#include "Simulation.h"

#include <cmath>

namespace
{
constexpr float PI = 3.14159265359f;

float lengthSquared(const sf::Vector2f& v)
{
    return v.x * v.x + v.y * v.y;
}

float length(const sf::Vector2f& v)
{
    return std::sqrt(lengthSquared(v));
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
    const float len = length(v);

    if (len <= 0.0001f)
        return {};

    return v / len;
}
}

Simulation::Simulation()
    : rng(std::random_device{}()),
      worldWidth(5000.f),
      worldHeight(5000.f),
      preferredDistance(18.f),
      interactionRadius(60.f),
      attractionStrength(14.f),
      repulsionStrength(190.f),
      maximumVelocity(250.f)
{
    atoms.reserve(10000);

    spawnRandomAtoms(5000);
}

const std::vector<Atom>& Simulation::getAtoms() const
{
    return atoms;
}

void Simulation::spawnRandomAtoms(std::size_t count)
{
    std::uniform_real_distribution<float> posX(
        0.f,
        worldWidth);

    std::uniform_real_distribution<float> posY(
        0.f,
        worldHeight);

    std::uniform_real_distribution<float> velocityDist(
        -20.f,
        20.f);

    std::uniform_int_distribution<int> typeDist(
        0,
        3);

    for (std::size_t i = 0; i < count; ++i)
    {
        AtomType type =
            static_cast<AtomType>(typeDist(rng));

        float mass = 1.f;
        float radius = 2.f;
        sf::Color color;

        switch (type)
        {
        case AtomType::Hydrogen:
            mass = 1.f;
            radius = 2.f;
            color = sf::Color(120,180,255);
            break;

        case AtomType::Oxygen:
            mass = 2.f;
            radius = 3.f;
            color = sf::Color(255,100,100);
            break;

        case AtomType::Carbon:
            mass = 3.f;
            radius = 4.f;
            color = sf::Color(160,160,160);
            break;

        case AtomType::Neon:
            mass = 1.5f;
            radius = 2.5f;
            color = sf::Color(255,220,90);
            break;
        }

        atoms.emplace_back(
            type,
            sf::Vector2f(posX(rng), posY(rng)),
            sf::Vector2f(
                velocityDist(rng),
                velocityDist(rng)),
            mass,
            radius,
            color);
    }
}

void Simulation::applyMouseForce(
    const sf::Vector2f& worldPosition,
    bool attract)
{
    const float radius = 250.f;

    for (auto& atom : atoms)
    {
        sf::Vector2f offset =
            worldPosition - atom.position;

        float distSq = lengthSquared(offset);

        if (distSq > radius * radius)
            continue;

        float dist =
            std::max(5.f, std::sqrt(distSq));

        sf::Vector2f dir = offset / dist;

        float strength =
            attract ? 150.f : -150.f;

        atom.velocity +=
            dir * strength * 0.016f;
    }
}

void Simulation::computeInteractions(float)
{
    const float interactionRadiusSq =
        interactionRadius * interactionRadius;

    for (auto& atom : atoms)
        atom.acceleration = {};

    const std::size_t count = atoms.size();

    for (std::size_t i = 0; i < count; ++i)
    {
        for (std::size_t j = i + 1;
             j < count;
             ++j)
        {
            sf::Vector2f delta =
                atoms[j].position -
                atoms[i].position;

            float distSq =
                lengthSquared(delta);

            if (distSq >
                interactionRadiusSq)
            {
                continue;
            }

            float distance =
                std::max(
                    0.1f,
                    std::sqrt(distSq));

            sf::Vector2f direction =
                delta / distance;

            float force = 0.f;

            if (distance >
                preferredDistance)
            {
                force =
                    attractionStrength *
                    ((distance -
                    preferredDistance) /
                    interactionRadius);
            }
            else
            {
                force =
                    -repulsionStrength *
                    ((preferredDistance -
                    distance) /
                    preferredDistance);
            }

            sf::Vector2f applied =
                direction * force;

            atoms[i].acceleration +=
                applied / atoms[i].mass;

            atoms[j].acceleration -=
                applied / atoms[j].mass;
        }
    }
}

void Simulation::integrate(float deltaTime)
{
    for (auto& atom : atoms)
    {
        atom.velocity +=
            atom.acceleration *
            deltaTime;

        float speed =
            length(atom.velocity);

        // Prevent runaway energy from
        // exploding the whole simulation.

        if (speed >
            maximumVelocity)
        {
            atom.velocity =
                atom.velocity /
                speed *
                maximumVelocity;
        }

        atom.position +=
            atom.velocity *
            deltaTime;

        if (atom.position.x < 0.f)
        {
            atom.position.x = 0.f;
            atom.velocity.x *= -0.85f;
        }

        if (atom.position.x >
            worldWidth)
        {
            atom.position.x =
                worldWidth;

            atom.velocity.x *= -0.85f;
        }

        if (atom.position.y < 0.f)
        {
            atom.position.y = 0.f;
            atom.velocity.y *= -0.85f;
        }

        if (atom.position.y >
            worldHeight)
        {
            atom.position.y =
                worldHeight;

            atom.velocity.y *= -0.85f;
        }

        atom.velocity *= 0.9992f;
    }
}

void Simulation::update(float deltaTime)
{
    computeInteractions(deltaTime);
    integrate(deltaTime);
}