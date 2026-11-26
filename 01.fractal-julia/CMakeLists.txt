cmake_minimum_required(VERSION 3.16)

project(FractalJulia)

#Pasar configuracion
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -fopenmp")

find_package(fmt CONFIG REQUIRED)

find_package(
    SFML
    COMPONENTS Graphics Window System Audio
    CONFIG REQUIRED
)

add_executable(fractal-julia 
    main.cpp
    fractal-serial.cpp
    palette.cpp
    fractal-simd.cpp
    fractal-openmp.cpp
    )

target_link_libraries(fractal-julia PRIVATE
    fmt::fmt
    SFML::Graphics
    SFML::Window
    SFML::System
)