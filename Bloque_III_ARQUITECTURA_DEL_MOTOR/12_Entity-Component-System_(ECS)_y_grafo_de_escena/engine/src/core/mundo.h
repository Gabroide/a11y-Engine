// [CAP.12] mundo.h - Contenedor y orquestador de todas las entidades de la escena
#pragma once
#include <vector>
#include <memory>
#include "entidad.h"

class Mundo {
private:
    std::vector<std::unique_ptr<Entidad>> entidades;

public:
    Entidad& crearEntidad(int id);
    void actualizar(float deltaTiempo);
    void imprimirJerarquia() const; // [CAP.12] Ver apartado 12.6

    const std::vector<std::unique_ptr<Entidad>>& obtenerEntidades() const { return entidades; }
};
