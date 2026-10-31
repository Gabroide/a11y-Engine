// [CAP.7] registro.h - Registro de eventos del motor (RAII sobre un fichero)
#pragma once
#include <cstdio>
#include <string> // [CAP.7]

class Registro {
private:
    FILE* archivo;

public:
    explicit Registro(const char* rutaArchivo);
    ~Registro();

    void escribir(const char* mensaje);

    // [CAP.7] Sobrecarga: la misma funcion, aceptando ahora tambien
    // [CAP.7] std::string, para no obligar a llamar a .c_str() en
    // [CAP.7] cada punto de llamada del motor.
    void escribir(const std::string& mensaje);

    Registro(const Registro& otro) = delete;
    Registro& operator=(const Registro& otro) = delete;
    Registro(Registro&& otro) noexcept;
    Registro& operator=(Registro&& otro) noexcept;
};
