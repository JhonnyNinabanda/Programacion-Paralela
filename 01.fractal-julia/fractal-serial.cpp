#include "fractal-serial.h"
#include "palette.h"

#include <complex>
#include <cmath>
#include <cstdint>


std::complex<double> c(-0.7, 0.27015);
extern int max_iteraciones;

uint32_t acotado_1(std::complex<double> z0) {
    /*
    datos: c, z0
    Zn+1 = Zn^2 + c
    */
    
    int iter = 1;
    std::complex<double> z = z0;

    while (iter<max_iteraciones && std::abs(z)<2.0){
        z = z * z + c;
        iter++;
    }
    {
    if (iter<max_iteraciones)
    {
        //norma<2
        int index = iter % PALETTE_SIZE;
        return color_ramp[index];
        //return 0xFFFFFFFF;
    }

    return 0XFF000000;
    
    }
    
}

uint32_t acotado_2(double x, double y) {

    int iter = 1;

    double zr = x;
    double zi = y;

    while (iter<max_iteraciones && (zr*zr + zi*zi)<4.0){
        double new_zr = zr*zr - zi*zi + c.real();
        double new_zi = 2 * zr * zi + c.imag();

        zr = new_zr;
        zi = new_zi;

        iter++;

    }
    
    if(iter<max_iteraciones){
            int index = iter % PALETTE_SIZE;
            return color_ramp[index];
    }

    return 0xFF000000;
    

}

void julia_serial_1(double x_min, double y_min, double x_max, double y_max,
    uint32_t width, uint32_t height,
    uint32_t* pixel_buffer) {

        double dx = (x_max - x_min) / width;
        double dy = (y_max - y_min) / height;

        for (int  i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                double x = x_min + i * dx;
                double y = y_max - j * dy;

                double z = x*x + y*y;
              //double z = sin(x*x) + cos(y*y);

                std::complex<double> z0(x,y);

                uint32_t color = acotado_1(z0);

                pixel_buffer[j * width + i] = color;

            }
            
        }
        
    }

    void julia_serial_2(double x_min, double y_min, double x_max, double y_max,
    uint32_t width, uint32_t height,
    uint32_t* pixel_buffer) {

        double dx = (x_max - x_min) / width;
        double dy = (y_max - y_min) / height;

        for (int  i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                double x = x_min + i * dx;
                double y = y_max - j * dy;


                //std::complex<double> z0(x,y);

                uint32_t color = acotado_2(x, y);

                pixel_buffer[j * width + i] = color;

            }
            
        }
        
    }
