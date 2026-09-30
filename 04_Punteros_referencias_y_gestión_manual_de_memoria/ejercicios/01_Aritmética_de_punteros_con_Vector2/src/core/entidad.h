// [CAP.4] entidad.h - Representacion basica de una entidad del juego
#pragma once
#include "../math/vector2.h"

typedef enum {
    ESTADO_IDLE,
    ESTADO_MOVIENDO,
    ESTADO_MUERTO
} EstadoEntidad;

typedef struct {
    int id;
    Vector2 posicion;
    Vector2 velocidad;
    EstadoEntidad estado;
} Entidad;

Entidad entidad_crear(int id, Vector2 posicion, Vector2 velocidad);

// [CAP.4] Antes: void entidad_actualizar(Entidad* entidad, float deltaTiempo);
// [CAP.4] Ahora: recibimos una REFERENCIA, no un puntero. Ya no hace falta
// [CAP.4] comprobar "if (entidad == NULL)": una referencia en C++ nunca
// [CAP.4] puede ser nula por construccion, siempre esta ligada a un objeto
// [CAP.4] valido en el momento de crearse.
void entidad_actualizar(Entidad& entidad, float deltaTiempo);

const char* entidad_nombre_estado(EstadoEntidad estado);