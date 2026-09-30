// [CAP.5] registro.h - Registro de eventos del motor (RAII sobre un fichero)
#pragma once
#include <cstdio>

class Registro {
private:
    FILE* archivo; // [CAP.5] El recurso real que esta clase gestiona

public:
    // [CAP.5] Constructor: ADQUIERE el recurso (abre el fichero).
    explicit Registro(const char* rutaArchivo);

    // [CAP.5] Destructor: LIBERA el recurso (cierra el fichero).
    ~Registro();

    // [CAP.5] Escribe una linea en el fichero de registro.
    void escribir(const char* mensaje);

    // [CAP.5] Regla de los tres: esta clase posee un recurso que no
    // [CAP.5] puede compartirse de forma segura entre dos objetos,
    // [CAP.5] asi que prohibimos explicitamente la copia.
    Registro(const Registro& otro) = delete;
    Registro& operator=(const Registro& otro) = delete;

    // [CAP.5] Regla de los cinco: SI permitimos "mover" la propiedad
    // [CAP.5] del recurso de un objeto a otro, igual que hace unique_ptr.
    Registro(Registro&& otro) noexcept;
    Registro& operator=(Registro&& otro) noexcept;
};
