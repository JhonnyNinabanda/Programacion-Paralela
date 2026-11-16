cmake_minimum_required(VERSION 3.161)

project(PracticaFractal)

find_package(fmt CONFIG REQUIRED)

find_package(
    SFML
    COMPONENTS Graphics Window System Audio
    CONFIG REQUIRED
)

add_executable(
    practica-fractal
    main.cpp

)

target_link_libraries(practica-fractal PRIVATE
fmt::fmt
SFML::Graphics
SFML::Window
SFML::System
)