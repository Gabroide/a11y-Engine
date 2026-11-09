// [CAP.6] componente_salud.h - Componente de puntos de vida con regeneracion
#pragma once
#include "componente.h"

class ComponenteSalud : public Componente {
private:
    float vidaActual;
    float vidaMaxima;
    float regeneracionPorSegundo;

public:
    ComponenteSalud(float vidaMaxima, float regeneracionPorSegundo)
        : vidaActual(vidaMaxima), vidaMaxima(vidaMaxima), regeneracionPorSegundo(regeneracionPorSegundo) {}

    void actualizar(float deltaTiempo) override;
    const char* nombre() const override;

    void recibirDano(float cantidad);
    float obtenerVidaActual() const { return vidaActual; }
};
