// [CAP.3] entidad.c - Implementacion de la logica basica de una entidad
#include "entidad.h"
#include <stdio.h>

Entidad entidad_crear(int id, Vector2 posicion, Vector2 velocidad) {
    Entidad e;                 // [CAP.3] Variable local: vive en la pila
    e.id = id;                 // [CAP.3]
    e.posicion = posicion;     // [CAP.3]
    e.velocidad = velocidad;   // [CAP.3]
    e.estado = ESTADO_IDLE;    // [CAP.3] Toda entidad nace en reposo
    return e;
}

// [CAP.3] Recibe un PUNTERO a Entidad para poder modificarla: en C, esta
// [CAP.3] es la unica forma de que una funcion cambie una variable del
// [CAP.3] llamador (compara con la seccion 3.7: en C++ podriamos usar
// [CAP.3] "Entidad& entidad" en su lugar, sin asteriscos).
void entidad_actualizar(Entidad* entidad, float deltaTiempo) {
    if (entidad == NULL) {
        return; // [CAP.3] Nunca desreferenciamos un puntero sin comprobarlo
    }

    switch (entidad->estado) {
        case ESTADO_IDLE:
            // [CAP.3] En reposo, no hay nada que actualizar.
            break;

        case ESTADO_MOVIENDO:
            // [CAP.3] Integracion simple: posicion += velocidad * tiempo
            entidad->posicion = vector2_sumar(
                entidad->posicion,
                vector2_escalar(entidad->velocidad, deltaTiempo)
            );
            break;

        case ESTADO_MUERTO:
            // [CAP.3] Una entidad muerta no se actualiza. Intencionado:
            // [CAP.3] cae directamente al "default" sin hacer nada mas.
            break;

        default:
            printf("Aviso: estado de entidad desconocido (%d)\n", entidad->estado);
            break;
    }
}

const char* entidad_nombre_estado(EstadoEntidad estado) {
    switch (estado) {
        case ESTADO_IDLE:     return "En reposo";
        case ESTADO_MOVIENDO: return "Moviendose";
        case ESTADO_MUERTO:   return "Muerto";
        default:               return "Estado desconocido";
    }
}
