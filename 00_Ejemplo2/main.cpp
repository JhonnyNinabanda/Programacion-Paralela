#include <iostream> // Para imprimir mensajes en la consola
#include <SFML/Graphics.hpp> // Para crear la ventana y dibujar en ella
#include <cmath> // Para usar sin() y cos()

// RANGO DEL SISTEMA DE COORDENADAS MATEMÁTICAS
// Límite izquierdo del eje X
double x_min = -5;

// Límite derecho del eje X
double x_max = 5;

// Límite inferior del eje Y
double y_min = -5;

// Límite superior del eje Y
double y_max = 5;

// TAMAÑO DE LA VENTANA EN PÍXELES
#define WIDTH 1600
#define HEIGHT 900

// BUFFER DE IMAGEN
// Aquí se almacenará el color de cada píxel.
// Inicialmente no apunta a ninguna memoria.
uint32_t* buffer = nullptr;

// FUNCIÓN QUE CALCULA Y DIBUJA LA IMAGEN
void dibujar()
{
    // Calcula cuánto avanza en X cada píxel
    double dx = (x_max - x_min) / WIDTH;
    // Calcula cuánto avanza en Y cada píxel
    double dy = (y_max - y_min) / HEIGHT;

    // Recorre todas las columnas
    for(int i = 0; i < WIDTH; i++)
    {
        // Recorre todas las filas
        for(int j = 0; j < HEIGHT; j++)
        {
            // Convierte la posición del píxel (i,j)
            // a una coordenada matemática real x
            double x = x_min + i * dx;

            // Convierte la posición del píxel (i,j)
            // a una coordenada matemática real y
            double y = y_max - j * dy;

            // FUNCIÓN MATEMÁTICA A REPRESENTAR
            // z = sin(x²) + cos(y²)
            double z = sin(x * x) + cos(y * y);

            // CONVERSIÓN A COLOR
            // Convierte el resultado matemático
            // a una intensidad de color rojo.
            int rojo = z * 255 / 2;

            // GUARDAR PÍXEL EN EL BUFFER

            // j * WIDTH + i calcula la posición lineal del píxel dentro del arreglo.
            // rojo << 24 mueve el valor rojo a los bits correspondientes al canal de color.
            buffer[j * WIDTH + i] =
                rojo << 24 | 0x000000FF;
        }
    }
}

int main()
{
    // Reserva memoria para todos los píxeles.
    // WIDTH * HEIGHT = 1600 * 900
    buffer = new uint32_t[WIDTH * HEIGHT];

    // CREAR VENTANA
    sf::RenderWindow window(
        sf::VideoMode({WIDTH, HEIGHT}),
        "SFML window"
    );

    // Calcula toda la imagen
    dibujar();

    // CREAR TEXTURA Y SPRITE
    // La textura almacenará la imagen.
    sf::Texture texture({WIDTH, HEIGHT});

    // El sprite es el objeto que se dibuja.
    sf::Sprite sprite(texture);

    // Copia los datos del buffer a la textura.
    texture.update((const uint8_t*)buffer);

    // BUCLE PRINCIPAL DEL PROGRAMA
    while(window.isOpen())
    {
        // Procesa eventos de la ventana
        while(const auto event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                window.close();
        }
        
        // Limpia la pantalla
        window.clear();

        // Dibuja el sprite
        window.draw(sprite);

        // Muestra la imagen en pantalla
        window.display();
    }

    return 0;
}
