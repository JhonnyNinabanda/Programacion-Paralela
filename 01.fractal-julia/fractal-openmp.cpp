#include "fractal-openmp.h"
#include "palette.h"

#include <cstdint>
#include <complex>
#include <omp.h>
#include <cmath>

extern std::complex<double> c;
extern int max_iteraciones;

uint32_t acotado_openmp(double x, double y) {

    int iter = 1;

    double zr = x;
    double zi = y;

    while (iter < max_iteraciones && (zr * zr + zi * zi) < 4.0) {

        double new_zr = zr * zr - zi * zi + c.real();
        double new_zi = 2.0 * zr * zi + c.imag();

        zr = new_zr;
        zi = new_zi;

        iter++;
    }

    if (iter < max_iteraciones) {
        int index = iter % PALETTE_SIZE;
        return color_ramp[index];
    }

    return 0xFF000000;
}

void julia_openmp_regiones(double x_min, double y_min,
                  double x_max, double y_max,
                  uint32_t width, uint32_t height,
                  uint32_t* pixel_buffer) {

    double dx = (x_max - x_min) / width;
    double dy = (y_max - y_min) / height;

    #pragma omp parallel
    {
        int thread_count = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        int delta = std::ceil(width * 1.0 / thread_count);

        int start = thread_id * delta;
        int end = (thread_id + 1) * delta;
        

        if (thread_id == thread_count - 1) {
            end = width;
        }

        for (int i = start; i < end; i++) {

            for (int j = 0; j < height; j++) {

                double x = x_min + i * dx;
                double y = y_max - j * dy;

                uint32_t color = acotado_openmp(x, y);

                pixel_buffer[j * width + i] = color;
            }
        }
    }
}

void julia_openmp_for(double x_min, double y_min,
                  double x_max, double y_max,
                  uint32_t width, uint32_t height,
                  uint32_t* pixel_buffer) {

    double dx = (x_max - x_min) / width;
    double dy = (y_max - y_min) / height;

    #pragma omp parallel for

        for (int i = 0; i < width; i++) {

            for (int j = 0; j < height; j++) {

                double x = x_min + i * dx;
                double y = y_max - j * dy;

                uint32_t color = acotado_openmp(x, y);

                pixel_buffer[j * width + i] = color;
            }
        }
    }


