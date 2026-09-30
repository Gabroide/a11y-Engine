// [CAP.5] registro.cpp - Implementacion del registro de eventos
#include "registro.h"

Registro::Registro(const char* rutaArchivo) {
    // [CAP.5] fopen_s es la variante seleccionada por MSVC como
    // [CAP.5] alternativa mas segura a fopen: comprueba errores
    // [CAP.5] y evita algunos avisos del compilador (C4996).
    errno_t error = fopen_s(&archivo, rutaArchivo, "w");
    if (error != 0 || archivo == nullptr) {
        archivo = nullptr;
        printf("[Registro] Aviso: no se pudo abrir '%s' para escritura.\n", rutaArchivo);
        // [CAP.5] Nota: no llamamos a exit() aqui. Un fallo al abrir el
        // [CAP.5] registro no debe cerrar el motor: es exactamente el
        // [CAP.5] mismo principio de "degradacion elegante" que usaremos,
        // [CAP.5] de forma mucho mas critica, con el lector de pantalla
        // [CAP.5] a partir del capitulo 11.
    }
}

Registro::~Registro() {
    if (archivo != nullptr) {
        fclose(archivo); // [CAP.5] Liberacion garantizada del recurso
    }
}

void Registro::escribir(const char* mensaje) {
    if (archivo == nullptr) {
        return; // [CAP.5] Degradacion elegante: sin fichero, no se escribe, no se rompe nada
    }
    fprintf(archivo, "%s\n", mensaje);
    fflush(archivo); // [CAP.5] Aseguramos que cada linea se escribe de inmediato
}

Registro::Registro(Registro&& otro) noexcept {
    archivo = otro.archivo;   // [CAP.5] Nos apropiamos del recurso de "otro"
    otro.archivo = nullptr;   // [CAP.5] "otro" ya no posee nada: evita el doble cierre
}

Registro& Registro::operator=(Registro&& otro) noexcept {
    if (this != &otro) {           // [CAP.5] Comprobacion de auto-asignacion
        if (archivo != nullptr) {
            fclose(archivo);         // [CAP.5] Cerramos nuestro propio fichero actual, si lo hay
        }
        archivo = otro.archivo;
        otro.archivo = nullptr;
    }
    return *this;
}
