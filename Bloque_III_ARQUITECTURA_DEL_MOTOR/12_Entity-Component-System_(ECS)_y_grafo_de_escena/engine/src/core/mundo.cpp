// [CAP.12] mundo.cpp
#include "mundo.h"
#include "../components/componente_transform.h"
#include <cstdio>

Entidad& Mundo::crearEntidad(int id) {
    entidades.push_back(std::make_unique<Entidad>(id));
    return *entidades.back(); // [CAP.12] Devolvemos una referencia a la entidad recien creada
}

void Mundo::actualizar(float deltaTiempo) {
    for (auto& entidad : entidades) {
        entidad->actualizarComponentes(deltaTiempo);
    }
}

void Mundo::imprimirJerarquia() const {
    printf("--- Jerarquia de la escena ---\n");
    for (const auto& entidad : entidades) {
        printf("Entidad %d:", entidad->obtenerId());

        for (const auto& nombre : entidad->listarNombresComponentes()) {
            printf(" [%s]", nombre.c_str());
        }

        // [CAP.12] Si tiene un ComponenteTransform con padre, buscamos a
        // [CAP.12] que entidad pertenece ese transform padre.
        ComponenteTransform* transform = const_cast<Entidad&>(*entidad).obtenerComponente<ComponenteTransform>();
        if (transform != nullptr && transform->obtenerTransformPadre() != nullptr) {
            for (const auto& otra : entidades) {
                ComponenteTransform* otroTransform = const_cast<Entidad&>(*otra).obtenerComponente<ComponenteTransform>();
                if (otroTransform == transform->obtenerTransformPadre()) {
                    printf(" (hijo de Entidad %d)", otra->obtenerId());
                    break;
                }
            }
        }
        printf("\n");
    }
    printf("------------------------------\n");
}
