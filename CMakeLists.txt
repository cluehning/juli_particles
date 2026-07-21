cmake_minimum_required(VERSION 3.20)

project(AtomSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "c:/Users/cheyenne/Downloads/SFML-3.0.0")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(AtomSimulation
    src/main.cpp
    src/Atom.cpp
    src/Simulation.cpp
    src/Renderer.cpp
)

target_include_directories(AtomSimulation PRIVATE src)

target_link_libraries(AtomSimulation
    PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)