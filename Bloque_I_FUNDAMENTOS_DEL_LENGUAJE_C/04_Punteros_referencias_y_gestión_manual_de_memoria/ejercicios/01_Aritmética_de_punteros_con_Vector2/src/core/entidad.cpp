// [CAP.4] entidad.cpp - Implementacion de la logica basica de una entidad
#include "entidad.h"
#include <cstdio>

Entidad entidad_crear(int id, Vector2 posicion, Vector2 velocidad) {
    Entidad e;
    e.id = id;
    e.posicion = posicion;
    e.velocidad = velocidad;
    e.estado = ESTADO_IDLE;
    return e;
}

void entidad_actualizar(Entidad& entidad, float deltaTiempo) {
    // [CAP.4] Ya no hay comprobacion de NULL: una referencia siempre
    // [CAP.4] esta ligada a un objeto real. El compilador no permite
    // [CAP.4] crear una referencia "vacia".

    switch (entidad.estado) { // [CAP.4] "." en lugar de "->": no es un puntero
        case ESTADO_IDLE:
            break;

        case ESTADO_MOVIENDO:
            entidad.posicion = vector2_sumar(
                entidad.posicion,
                vector2_escalar(entidad.velocidad, deltaTiempo)
            );
            break;

        case ESTADO_MUERTO:
            break;

        default:
            printf("Aviso: estado de entidad desconocido (%d)\n", entidad.estado);
            break;
    }
}

const char* entidad_nombre_estado(EstadoEntidad estado) {
    switch (estado) {
        case ESTADO_IDLE:     return "En reposo";
        case ESTADO_MOVIENDO: return "Moviendose";
        case ESTADO_MUERTO:   return "Muerta";
        default:               return "Estado desconocido";
    }
}
