#include <iostream>
#include <fmt/core.h>
#include <fmt/format.h>
#include <SFML/Graphics.hpp>
#include <cmath> //Libreria en <> archivo del sistema
#include <omp.h>

// Proviene de nuestro proyecto
#include "fractal-serial.h" 
#include "fractal-simd.h"
#include "fractal-openmp.h"

int max_iteraciones = 15;

// Parámetros: límites del rectángulo complejo que vamos a muestrear
double x_min = -1.5;
double x_max = 1.5;
double y_min = -1.5;
double y_max = 1.5;

//Tamaño de la pantalla
#define WIDTH 1660
#define HEIGHT 900

// Buffer de píxeles (RGBA empaquetado en uint32_t). Se inicializa en main.
uint32_t* buffer = nullptr;

enum class runtime_type {
    SERIAL_1 = 0,
    SERIAL_2,
    SIMD,
    OPEN_MP_REGIONES,
    OPEN_MP_FOR

};

int thread_count = 0;


int main () {

    #pragma omp parallel
    {
        #pragma omp master
        {
            thread_count = omp_get_num_threads();
            std::cout << "Hola desde el hilo " << omp_get_thread_num() << " de " << thread_count << " hilos." << std::endl;

        }
    }

    buffer = new uint32_t[WIDTH*HEIGHT];

    runtime_type r_type = runtime_type::SERIAL_1;


    //Crear la ventana principal
    sf::RenderWindow window(
        sf::VideoMode({WIDTH, HEIGHT}),
        "Ventana de Muestra"
    );

    sf::Texture texture({WIDTH, HEIGHT});
    texture.update((const uint8_t *)buffer);
    sf::Sprite sprite(texture);

    const sf::Font font("ARIAL.TTF");
    std::cout << "Fuente cargada correctamente" << std::endl;
    sf::Text text(font, "Hello SFML", 40);
    text.setFillColor(sf::Color::Blue);
    text.setPosition({20.f, 20.f});
    text.setStyle(sf::Text::Bold);

    std::string options = "[1] Serial_1 | [2] Serial_2 | [3] SIMD | [4] OpenMP Regiones | [5] OpenMP For | Up/Down: Iteraciones";
    sf::Text text_options(font, options, 20);
    text_options.setFillColor(sf::Color::Blue);
    text_options.setPosition({10, window.getView().getSize().y -40});

    //FPS
    int frames = 0;
    int fps = 0;
    sf::Clock clock;

    //Bucle principal
    while (window.isOpen()) {
        //Procesar eventos
        while (const std::optional event = window.pollEvent()) {
            //Cerrar ventana
            if (event->is<sf::Event::Closed>()){
                window.close();

            }
                else if(event->is<sf::Event::KeyReleased>()) {
                    auto evt = event->getIf<sf::Event::KeyReleased>();
                    switch (evt->scancode) {
                        case sf::Keyboard::Scan::Up:
                            max_iteraciones +=10;
                            break;
                        case sf::Keyboard::Scan::Down:
                            max_iteraciones -=10;
                            break;
                        case sf::Keyboard::Scan::Num1:
                            r_type = runtime_type::SERIAL_1;
                        break; 
                        case sf::Keyboard::Scan::Num2:
                            r_type = runtime_type::SERIAL_2;
                        break; 
                        case sf::Keyboard::Scan::Num3:
                            r_type = runtime_type::SIMD;
                        break; 
                        case sf::Keyboard::Scan::Num4:
                            r_type = runtime_type::OPEN_MP_REGIONES;
                        break; 
                        case sf::Keyboard::Scan::Num5:
                            r_type = runtime_type::OPEN_MP_FOR;
                        break; 
                        default:
                        break;    
                        
                    }
                }
        }
            

        //--dibujar fractal
        //
        
        std::string mode = "";

        if(r_type == runtime_type::SERIAL_1){
            mode = "Julia Serial_1";
            julia_serial_1(x_min, y_min, x_max, y_max, WIDTH, HEIGHT, buffer);

        }
        else if(r_type == runtime_type::SERIAL_2){
            mode = "Julia Serial_2";
            julia_serial_2(x_min, y_min, x_max, y_max, WIDTH, HEIGHT, buffer);
        }
        else if(r_type == runtime_type::SIMD){
            mode = "Julia SIMD";
            julia_simd(x_min, y_min, x_max, y_max, WIDTH, HEIGHT, buffer);
        }
        else if(r_type == runtime_type::OPEN_MP_REGIONES){
            mode = fmt::format("OPENMP REGIONES - Threads: {}", thread_count);
            julia_openmp_regiones(x_min, y_min, x_max, y_max, WIDTH, HEIGHT, buffer);
        }
        else if(r_type == runtime_type::OPEN_MP_FOR){
            mode = fmt::format("OPENMP FOR - Threads: {}", thread_count);
            julia_openmp_for(x_min, y_min, x_max, y_max, WIDTH, HEIGHT, buffer);
        }

        texture.update((const uint8_t*)buffer);

        //--Medir FPS
        frames++;

        if (clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            fps = frames;
            frames = 0;
            clock.restart();

        }

        //Actualizar los textos
        auto msg = fmt::format("Fractal -{} - Iteraciones: {}, FPS: {}", mode, max_iteraciones, fps);
            text.setString(msg);


        std::cout <<"FPS: "<<fps<<std::endl;

        //Limpiar pantalla
        window.clear();

        window.draw(sprite);
        window.draw(text);
        window.draw(text_options);

        //Mostrar contenido
        window.display();

    }
    
}

