package com.programacion.paralela;

import jnr.ffi.LibraryLoader;
import java.nio.Buffer;

public interface FractalDll {

    FractalDll INSTANCE =
            LibraryLoader.create(FractalDll.class)

                    .search(
                            "C:/Users/HP/Documents/Universidad Central del Ecuador/10.1 SEMESTRE - COM 001/Programamacion Paralela/Code/02.fractal-dll/build/Release"
                    )

                    .load("libfractal-dll");

    void julia_simd(
            double x_min,
            double y_min,
            double x_max,
            double y_max,
            int width,
            int height,
            int max_iteraciones,
            Buffer pixel_buffer
    );
}