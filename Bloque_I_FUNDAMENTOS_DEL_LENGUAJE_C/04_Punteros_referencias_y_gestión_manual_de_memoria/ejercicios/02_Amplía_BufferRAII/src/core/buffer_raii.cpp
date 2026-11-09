// [CAP.4] buffer_raii.cpp - Implementacion del patron RAII
#include "buffer_raii.h"
#include <cstdio>

BufferRAII::BufferRAII(int cantidadElementos) {
    cantidad = cantidadElementos;                 // [CAP.4]
    datos = new float[cantidadElementos];          // [CAP.4] Adquisicion del recurso
    printf("[BufferRAII] Reservados %d floats.\n", cantidad); // [CAP.4]

    for (int i = 0; i < cantidad; i++) {           // [CAP.4]
        datos[i] = 0.0f;                             // [CAP.4] Inicializamos a cero
    }
}

BufferRAII::~BufferRAII() {
    printf("[BufferRAII] Liberando %d floats.\n", cantidad); // [CAP.4]
    delete[] datos; // [CAP.4] Liberacion del recurso: SIEMPRE se ejecuta
}

// []EJ. 2] Agrega un metodo imprimir() que recorra el buffer y muestre sus valores.
void BufferRAII::imprimir() {
    printf("[BufferRAII] Valores del buffer:\n");
    for (int i = 0; i < cantidad; i++) {
        printf("datos[%d] = %f\n", i, datos[i]);
    }
}