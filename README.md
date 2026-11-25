# Programación Paralela

Repositorio de prácticas, laboratorios y ejercicios desarrollados durante la asignatura de Programación Concurrente y Paralela.

## Entorno de Desarrollo

- GCC 16.2 (WinLibs)
- CMake
- VS Code
- SFML
- fmt
- OpenMP
- AVX2 SIMD
- Java
- Gradle
- JNR-FFI

---

## Estructura del Repositorio

### 00_Ejemplo

Configuración inicial del entorno de desarrollo.

Temas:

- GCC y G++
- CMake
- VS Code
- Compilación de proyectos C++

---

### 00_Ejemplo1

Primeros programas en C++.

Temas:

- Variables
- Entrada y salida
- Ciclos
- Funciones básicas

---

### 00_Ejemplo2

Prácticas iniciales con estructuras de datos y compilación mediante CMake.

Temas:

- Arreglos
- Bucles
- Organización de proyectos

---

### 01_Practica

Ejercicios de introducción a Programación Paralela.

Temas:

- Coordenadas cartesianas
- Buffers de imagen
- Mallas bidimensionales

---

### 01.fractal-julia

Implementación serial del Fractal de Julia usando SFML.

Temas:

- Números complejos
- Fractales de Julia
- Conversión de coordenadas
- Renderizado de píxeles
- Paletas de colores
- Medición de FPS

Conceptos matemáticos:

```
Zn+1 = Zn² + C
```

---

### 02.fractal-dll

Implementación optimizada del Fractal de Julia mediante SIMD.

Temas:

- Vectorización
- AVX2
- Intrinsics
- SIMD
- DLLs en C++
- Exportación de funciones

Conceptos estudiados:

```cpp
extern "C"
```

```cpp
__m256
```

```cpp
_mm256_add_ps()
```

```cpp
_mm256_mul_ps()
```

```cpp
_mm256_cmp_ps()
```

Archivos generados:

- libfractal-dll.dll
- libfractal-dll.dll.a

---

### 03.fractal-java

Consumo de la DLL SIMD desde Java utilizando JNR-FFI.

Temas:

- Interoperabilidad Java/C++
- Native Libraries
- JNR-FFI
- Buffers de memoria compartida

Conceptos estudiados:

```java
LibraryLoader
```

```java
ByteBuffer.allocateDirect()
```

```java
IntBuffer
```

```java
.load("libfractal-dll")
```

---

### OpenMP

Introducción al paralelismo mediante memoria compartida.

Conceptos estudiados:

- Fork-Join
- Threads
- Regiones paralelas
- Work Sharing
- Variables Shared y Private
- Race Conditions
- Synchronization
- Reduction

Directivas:

```cpp
#pragma omp parallel
```

```cpp
#pragma omp for
```

```cpp
#pragma omp parallel for
```

```cpp
#pragma omp master
```

```cpp
#pragma omp critical
```

```cpp
#pragma omp barrier
```

Funciones:

```cpp
omp_get_num_threads()
```

```cpp
omp_get_thread_num()
```

Compilación:

```bash
g++ -O3 -fopenmp archivo.cpp -o programa.exe
```

---

## Temas Cubiertos en el Curso

### Vectorización

- SIMD
- AVX2
- Auto-vectorización
- Intrinsics

### Memoria Compartida

- OpenMP
- Threads
- Fork-Join
- Synchronization

### Interoperabilidad

- DLLs
- Shared Libraries
- JNR-FFI
- Java + C++

### Computación Científica

- Fractales
- Números complejos
- Renderizado de imágenes
- Procesamiento paralelo de píxeles

---

## Autor

JHONNY EDUARDO NINABANDA PAMBABAY

Universidad Central del Ecuador

Carrera de Computación
