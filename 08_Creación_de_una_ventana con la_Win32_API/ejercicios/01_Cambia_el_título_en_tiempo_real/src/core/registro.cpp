#include "registro.h"

#include <cstdio>

Registro::Registro(const char* rutaArchivo)
    : archivo(std::fopen(rutaArchivo, "a")) {
    if (archivo == nullptr) {
        std::perror("[Registro] No se pudo abrir el archivo de registro");
    }
}

Registro::~Registro() {
    if (archivo != nullptr && std::fclose(archivo) != 0) {
        std::perror("[Registro] No se pudo cerrar el archivo de registro");
    }
}

void Registro::escribir(const char* mensaje) {
    if (archivo == nullptr) {
        std::fprintf(stderr, "[Registro] No se puede escribir: el archivo no esta abierto.\n");
        return;
    }

    if (mensaje == nullptr) {
        std::fprintf(stderr, "[Registro] No se puede escribir un mensaje nulo.\n");
        return;
    }

    if (std::fprintf(archivo, "%s\n", mensaje) < 0) {
        std::perror("[Registro] No se pudo escribir en el archivo de registro");
    }
}

void Registro::escribir(const std::string& mensaje) {
    escribir(mensaje.c_str());
}

Registro::Registro(Registro&& otro) noexcept
    : archivo(otro.archivo) {
    otro.archivo = nullptr;
}

Registro& Registro::operator=(Registro&& otro) noexcept {
    if (this != &otro) {
        if (archivo != nullptr && std::fclose(archivo) != 0) {
            std::perror("[Registro] No se pudo cerrar el archivo de registro");
        }
        archivo = otro.archivo;
        otro.archivo = nullptr;
    }
    return *this;
}
