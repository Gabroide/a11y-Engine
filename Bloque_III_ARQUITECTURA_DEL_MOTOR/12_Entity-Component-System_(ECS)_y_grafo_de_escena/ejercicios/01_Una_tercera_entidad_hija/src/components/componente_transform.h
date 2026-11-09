// [CAP.12] componente_transform.h - Componente de posicion, movimiento y jerarquia
#pragma once
#include "componente.h"
#include "../math/vector2.h"

class ComponenteTransform : public Componente {
private:
    Vector2 posicion;
    Vector2 velocidad;

    // [CAP.12] Puntero NO PROPIETARIO al transform padre (puede ser
    // [CAP.12] nullptr si esta entidad es raiz). "No propietario" significa
    // [CAP.12] que ComponenteTransform NUNCA llama a delete sobre este
    // [CAP.12] puntero: la propiedad real la tiene la Entidad dueña del
    // [CAP.12] padre, a traves de su propio unique_ptr<Componente>.
    // [CAP.12] AVISO: si la entidad padre se destruyera antes que la hija,
    // [CAP.12] este puntero quedaria colgante (capitulo 4). Un motor de
    // [CAP.12] produccion resolveria esto con std::weak_ptr; lo dejamos
    // [CAP.12] como puntero en bruto por simplicidad, y lo planteamos como
    // [CAP.12] reflexion en los ejercicios de este capitulo.
    ComponenteTransform* padre;

public:
    ComponenteTransform(Vector2 posicionInicial, Vector2 velocidadInicial)
        : posicion(posicionInicial), velocidad(velocidadInicial), padre(nullptr) {}

    void actualizar(float deltaTiempo) override;
    const char* nombre() const override;

    Vector2 obtenerPosicion() const { return posicion; }
    void establecerPosicion(Vector2 nuevaPosicion) { posicion = nuevaPosicion; }
    void establecerVelocidad(Vector2 nuevaVelocidad) { velocidad = nuevaVelocidad; }

    void establecerPadre(ComponenteTransform* nuevoPadre) { padre = nuevoPadre; }
    ComponenteTransform* obtenerTransformPadre() const { return padre; }

    // [CAP.12] Posicion LOCAL (relativa al padre) frente a posicion GLOBAL
    // [CAP.12] (acumulada recursivamente hasta la raiz del grafo de escena).
    Vector2 obtenerPosicionGlobal() const {
        if (padre != nullptr) {
            return padre->obtenerPosicionGlobal().sumar(posicion);
        }
        return posicion;
    }
};
