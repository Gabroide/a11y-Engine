// [CAP.5] entidad.cpp - Implementacion de la clase Entidad
#include "entidad.h"
#include <cstdio>

void Entidad::actualizar(float deltaTiempo) {
    switch (estado) {
        case ESTADO_IDLE:
            break;

        case ESTADO_MOVIENDO:
            posicion = posicion.sumar(velocidad.escalar(deltaTiempo)); // [CAP.5] Metodos, no funciones libres
            break;

        case ESTADO_MUERTO:
            break;

        default:
            printf("Aviso: estado de entidad desconocido (%d)\n", estado);
            break;
    }
}

void Entidad::setEstado(EstadoEntidad nuevo) {
    estado = nuevo; // [CAP.5] Unico punto de entrada para cambiar el estado
}

void Entidad::establecerVelocidad(Vector2 nuevaVelocidad) {
    // Sigue siendo encapsulacion: se cambia el dato mediante la interfaz publica,
    // sin exponer el miembro privado ni su forma interna de almacenamiento.
    velocidad = nuevaVelocidad;
}

EstadoEntidad Entidad::getEstado() const {
    return estado;
}

Vector2 Entidad::getPosicion() const {
    return posicion;
}

int Entidad::getId() const {
    return id;
}

const char* Entidad::nombreEstado(EstadoEntidad estado) {
    switch (estado) {
        case ESTADO_IDLE:     return "En reposo";
        case ESTADO_MOVIENDO: return "Moviendose";
        case ESTADO_MUERTO:   return "Muerta";
        default:               return "Estado desconocido";
    }
}
