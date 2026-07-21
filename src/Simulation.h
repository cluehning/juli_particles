#pragma once

#include "Atom.h"

#include <vector>
#include <random>

class Simulation
{
public:
    Simulation();

    void update(float deltaTime);

    void spawnRandomAtoms(std::size_t count);

    void applyMouseForce(
        const sf::Vector2f& worldPosition,
        bool attract);

    const std::vector<Atom>& getAtoms() const;

private:
    void computeInteractions(float deltaTime);
    void integrate(float deltaTime);

    std::vector<Atom> atoms;

    std::mt19937 rng;

    float worldWidth;
    float worldHeight;

    float preferredDistance;
    float interactionRadius;
    float attractionStrength;
    float repulsionStrength;

    float maximumVelocity;
};