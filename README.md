# Atom

A simple atom-inspired particle simulation built as one of my first larger C++ projects.

The goal of this project was not to create a scientifically accurate model of atomic physics, but rather to explore simulation programming, real-time rendering, and modern C++ development. It started as a small experiment with particles and gradually evolved into a system capable of simulating thousands of interacting particles in real time.

Along the way, I learned a great deal about project structure, physics simulation fundamentals, performance considerations, debugging, and working with external libraries such as SFML.

---

## Overview

The simulation consists of thousands of particles, referred to as *atoms*, moving inside a bounded world. Each atom has physical properties such as position, velocity, acceleration, mass, and type. Nearby atoms influence each other through a combination of attraction and repulsion forces, creating emergent behaviors that resemble clustering and molecule-like formations.

Rather than scripting specific patterns, all visible structures emerge naturally from simple interaction rules applied every frame.

The result is a dynamic system where groups constantly form, separate, and reorganize while remaining interactive and visually engaging.

---

## Motivation

This project was primarily created as a learning experience.

Some of the concepts I wanted to explore included:

- Organizing a C++ project across multiple source files
- Separating simulation and rendering logic
- Using CMake for project configuration
- Working with SFML for graphics rendering
- Real-time update loops
- Delta-time based simulations
- Basic force-based physics
- Performance optimization for large numbers of objects
- Camera systems and user interaction

As my understanding improved, the project grew from a simple particle renderer into a small interactive simulation.

---

## Features

### Simulation

- Thousands of particles simulated simultaneously
- Multiple atom types
- Individual mass values
- Velocity and acceleration based movement
- Attraction forces between particles
- Repulsion forces to prevent overlap
- Boundary collision handling
- Stable delta-time integration
- Randomized atom spawning

### Interaction

- Mouse attraction force
- Mouse repulsion force
- Camera movement
- Camera zooming
- Real-time controls

### Rendering

- Dark themed visualization
- Color-coded atom types
- Smooth particle rendering
- FPS counter
- Simple simulation overlay

---

## How It Works

Each particle continuously evaluates nearby particles and applies simple interaction forces.

### Attraction

When two particles are farther apart than a preferred distance, a small attraction force is applied:

```text
Too far apart
    ↓
Pull together
```

### Repulsion

When particles become too close, a stronger repulsion force pushes them apart:

```text
Too close
    ↓
Push apart
```

The balance between these opposing forces naturally creates stable clusters and constantly evolving particle structures.

While the simulation is inspired by chemical and atomic interactions, it should be viewed primarily as a visual and programming experiment rather than a physical model.

---

## Controls

| Input | Action |
|---------|---------|
| W A S D | Move camera |
| Mouse Wheel | Zoom camera |
| Left Mouse Button | Attract particles |
| Right Mouse Button | Repel particles |

---

## Project Structure

```text
Atom/
│
├── assets/
│
├── src/
│   ├── main.cpp
│   ├── Atom.h
│   ├── Atom.cpp
│   ├── Simulation.h
│   ├── Simulation.cpp
│   ├── Renderer.h
│   └── Renderer.cpp
│
└── CMakeLists.txt
```

### Source Breakdown

#### Atom

Represents an individual particle within the simulation.

Stores:

- Position
- Velocity
- Acceleration
- Mass
- Radius
- Color
- Atom type

#### Simulation

Responsible for:

- Spawning particles
- Calculating interaction forces
- Updating particle movement
- Handling collisions
- Processing mouse influence

#### Renderer

Handles:

- Drawing particles
- Camera control
- Zoom functionality
- UI rendering
- FPS display

#### Main

Contains:

- Application entry point
- Window creation
- Event processing
- Delta-time calculation
- Main update loop

---

## Building

### Requirements

- C++20 compatible compiler
- CMake 3.20+
- SFML

### Build Instructions

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

### Run

Linux:

```bash
./AtomSimulation
```

Windows:

```powershell
.\Debug\AtomSimulation.exe
```

or

```powershell
.\Release\AtomSimulation.exe
```

---

## Future Improvements

Some ideas I would like to explore in future versions include:

- Spatial partitioning for better performance
- GPU accelerated rendering
- Particle trails
- More complex force systems
- Molecule generation
- Custom UI panels
- Saving and loading simulation states
- 3D visualizations
- OpenGL or Vulkan rendering

---

## Final Thoughts

This project represents one of my first serious attempts at combining physics-inspired simulation, graphics programming, and modern C++ into a single application.

It is far from a perfect simulation, but it successfully achieved its original goal: building something interesting, interactive, and challenging enough to teach me new concepts along the way.

More than anything, this project helped me become more comfortable with C++.
