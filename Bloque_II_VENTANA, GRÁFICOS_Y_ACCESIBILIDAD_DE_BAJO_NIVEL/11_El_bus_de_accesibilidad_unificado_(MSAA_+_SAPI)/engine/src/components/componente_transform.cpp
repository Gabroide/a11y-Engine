// [CAP.6] componente_transform.cpp
#include "componente_transform.h"

void ComponenteTransform::actualizar(float deltaTiempo) {
    posicion = posicion.sumar(velocidad.escalar(deltaTiempo)); // [CAP.6]
}

const char* ComponenteTransform::nombre() const {
    return "Transform";
}
