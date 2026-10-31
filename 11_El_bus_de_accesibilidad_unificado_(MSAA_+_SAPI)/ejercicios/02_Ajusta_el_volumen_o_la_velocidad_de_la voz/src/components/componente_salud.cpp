// [CAP.6] componente_salud.cpp
#include "componente_salud.h"

void ComponenteSalud::actualizar(float deltaTiempo) {
    // [CAP.6] Cada fotograma, regenera vida hasta el maximo.
    vidaActual += regeneracionPorSegundo * deltaTiempo;
    if (vidaActual > vidaMaxima) {
        vidaActual = vidaMaxima;
    }
}

const char* ComponenteSalud::nombre() const {
    return "Salud";
}

void ComponenteSalud::recibirDano(float cantidad) {
    vidaActual -= cantidad;
    if (vidaActual < 0.0f) {
        vidaActual = 0.0f;
    }
}
