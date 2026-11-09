// [CAP.5] entidad.h - Representacion de una entidad del juego (ahora como clase)
#pragma once
#include "../math/vector2.h"

typedef enum {
    ESTADO_IDLE,
    ESTADO_MOVIENDO,
    ESTADO_MUERTO
} EstadoEntidad;

class Entidad {
private:
    // [CAP.5] Datos privados: inaccesibles desde fuera de la clase.
    int id;
    Vector2 posicion;
    Vector2 velocidad;
    EstadoEntidad estado;

public:
    // [CAP.5] Constructor con lista de inicializacion.
    Entidad(int id, Vector2 posicion, Vector2 velocidad)
        : id(id), posicion(posicion), velocidad(velocidad), estado(ESTADO_IDLE) {}

    // [CAP.5] Interfaz publica: la unica forma de interactuar con una Entidad.
    void actualizar(float deltaTiempo);
    void setEstado(EstadoEntidad nuevo);

    // [CAP.5] Metodos de solo lectura, marcados "const".
    EstadoEntidad getEstado() const;
    Vector2 getPosicion() const;
    int getId() const;

    static const char* nombreEstado(EstadoEntidad estado); // [CAP.5] ver nota mas abajo
};
