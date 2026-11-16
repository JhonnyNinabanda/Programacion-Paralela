#include "fractal-simd.h"
#include "palette.h"
#include <cstdint>     // Para usar uint32_t
#include <immintrin.h> // Para usar intrinsics de AVX
#include <complex>     // Para usar std::complex

std::complex<double> c(-0.7, 0.27015);

extern "C"

void julia_simd(double x_min, double y_min, double x_max, double y_max,
                uint32_t width, uint32_t height,
                int max_iteraciones,
                uint32_t *pixel_buffer)
{

    double dx = (x_max - x_min) / width;
    double dy = (y_max - y_min) / height;

    //(x_min,x_min,x_min,x_min,x_min,x_min,x_min,x_min)
    __m256 xmin = _mm256_set1_ps(x_min);
    //(y_max,y_max,y_max,y_max,y_max,y_max,y_max,y_max)
    __m256 ymax = _mm256_set1_ps(y_max);

    __m256 xscale = _mm256_set1_ps(dx); // (dx,dx,dx,dx,dx,dx,dx,dx)
    __m256 yscale = _mm256_set1_ps(dy); // (dy,dy,dy,dy,dy,dy,dy,dy)

    __m256 c_real = _mm256_set1_ps(c.real()); 
    __m256 c_imag = _mm256_set1_ps(c.imag());

    __m256 max_norma = _mm256_set1_ps(4.0);

    __m256 one = _mm256_set1_ps(1.0);

    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j += 8){

            __m256 mx = _mm256_set1_ps(i); // (i,i,i,i,i,i,i,i)
            __m256 my = _mm256_setr_ps(j, j+1, j+2, j+3, j+4, j+5, j+6, j+7);

            // xmin+mx*xscale --> (x0,x1,x2,x3,x4,x5,x6,x7) <-- real
            __m256 cr = _mm256_add_ps(xmin, _mm256_mul_ps(mx, xscale));
            // ymax-my*yscale --> (y0,y1,y2,y3,y4,y5,y6,y7) <-- imag
            __m256 ci = _mm256_sub_ps(ymax, _mm256_mul_ps(my, yscale));

            // verificar si los 8 complejos estan acotados
            int iter = 0;

            //(iter,iter,iter, .....8)
            __m256 mk = _mm256_set1_ps(iter);

            __m256 zr = cr;
            __m256 zi = ci;

            while(iter < max_iteraciones ){

                // Zn+1 = Zn^2 + c
                __m256 zr2 = _mm256_mul_ps(zr, zr);
                __m256 zi2 = _mm256_mul_ps(zi, zi);
                __m256 zrzi = _mm256_mul_ps(zr, zi);

                // zr^2 - zi^2 + c_real
                zr = _mm256_add_ps(_mm256_sub_ps(zr2, zi2), c_real);
                // 2*zr*zi + c_imag
                zi = _mm256_add_ps(_mm256_add_ps(zrzi, zrzi), c_imag);

                // normas
                zr2 = _mm256_mul_ps(zr, zr); // zr^2
                zi2 = _mm256_mul_ps(zi, zi); // zi^2

                __m256 norma2 = _mm256_add_ps(zr2, zi2);
                
                // si norma2<4 devuelve 0xFFFFFFFF, sino 0X000000
                __m256 mask = _mm256_cmp_ps(norma2, max_norma, _CMP_LE_OQ);

                mk = _mm256_add_ps(mk, _mm256_and_ps(mask, one));

                // verificar que mask = (0,0,0,0,0,0,0,0) -> todos los complejos son mayor que 4
                if(_mm256_testz_ps(mask, _mm256_set1_ps(-1))){
                    break;
                }

                iter++;

            }

            // verificar iter y seleccionar el color
            float d[8];
            _mm256_storeu_ps(d, mk);

            /**
             * d[0] -> #iteraciones para x0+y0i
             * d[1] -> #iteraciones para x1+y1i
             * d[2] -> #iteraciones para x2+y2i
             * ..
             * d[7] -> #iteraciones para x7+y7i
             */

            /**
             * [(j+0)*width+i]
             * [(j+1)*width+i]
             * [(j+2)*width+i]
             * ....
             * [(j+7)*width+i]
             */

            for(int it=0; it<8; it++){
                int index = (j+it) * width + i;

                if(index < width * height){
                    if(d[it] < max_iteraciones){
                        int color_index = (int)d[it] % PALETTE_SIZE;
                        pixel_buffer[index] = color_ramp[color_index];

                    }
                    else{
                        pixel_buffer[index] = 0xFF000000;
                    }
                }
            }

        }
    }
}