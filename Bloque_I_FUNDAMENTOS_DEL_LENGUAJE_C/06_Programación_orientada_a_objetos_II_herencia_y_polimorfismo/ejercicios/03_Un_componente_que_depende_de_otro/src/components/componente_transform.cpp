// [CAP.6] componente_transform.cpp
#include "componente_transform.h"
#include "componente_salud.h" // [EJ3.]

void ComponenteTransform::actualizar(float deltaTiempo) {
    posicion = posicion.sumar(velocidad.escalar(deltaTiempo)); // [CAP.6]
}
// [EJ.3] Implementación de la función aplicarDano, que aplica daño a un componente de salud si la posición x supera un límite.
void ComponenteTransform::aplicarDano(ComponenteSalud& salud, float cantidad) {
    // La regla depende del limite espacial, por eso la coordina el Transform.
    if (posicion.x > 10.0f) {
        salud.recibirDano(cantidad);
    }
}

const char* ComponenteTransform::nombre() const {
    return "Transform";
}
