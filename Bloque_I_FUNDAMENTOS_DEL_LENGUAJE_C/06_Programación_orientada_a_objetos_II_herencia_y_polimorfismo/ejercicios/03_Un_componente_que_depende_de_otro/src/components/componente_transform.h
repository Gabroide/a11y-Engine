// [CAP.6] componente_transform.h - Componente de posicion y movimiento
#pragma once
#include "componente.h"
#include "../math/vector2.h"

class ComponenteSalud; // [EJ3.]

class ComponenteTransform : public Componente {
private:
    Vector2 posicion;
    Vector2 velocidad;

public:
    ComponenteTransform(Vector2 posicionInicial, Vector2 velocidadInicial)
        : posicion(posicionInicial), velocidad(velocidadInicial) {}

    void actualizar(float deltaTiempo) override;
    const char* nombre() const override;
    void aplicarDano(ComponenteSalud& salud, float cantidad); //€J3 

    Vector2 obtenerPosicion() const { return posicion; }
    void establecerVelocidad(Vector2 nuevaVelocidad) { velocidad = nuevaVelocidad; }
};
