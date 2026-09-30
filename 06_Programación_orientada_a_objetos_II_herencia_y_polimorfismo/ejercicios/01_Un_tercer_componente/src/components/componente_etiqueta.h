// [EJ.1] componente_etiqueta.h - Nombre de texto asociado a una entidad
#pragma once

#include "componente.h"

class ComponenteEtiqueta : public Componente {
private:
    const char* nombreEtiqueta;

public:
    explicit ComponenteEtiqueta(const char* nombre) : nombreEtiqueta(nombre) {}

    void actualizar(float deltaTiempo) override;
    const char* nombre() const override;
};