// [CAP.4] buffer_raii.h - Ejemplo minimo de RAII: un buffer de floats
// [CAP.4] que se reserva en el constructor y se libera en el destructor.
#pragma once

struct BufferRAII {
    float* datos;   // [CAP.4] Puntero al array reservado dinamicamente
    int cantidad;   // [CAP.4] Numero de elementos del array

    // [CAP.4] Constructor: aqui se ADQUIERE el recurso (la memoria).
    BufferRAII(int cantidadElementos);

    // [CAP.4] Destructor: aqui se LIBERA el recurso, automaticamente,
    // [CAP.4] sin que quien use BufferRAII tenga que llamar a nada.
    ~BufferRAII();
};
