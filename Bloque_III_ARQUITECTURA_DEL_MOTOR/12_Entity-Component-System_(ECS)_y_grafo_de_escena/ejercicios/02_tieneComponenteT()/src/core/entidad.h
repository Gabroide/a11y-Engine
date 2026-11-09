// [CAP.12] entidad.h - Entidad ECS: un identificador y un contenedor de componentes
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../components/componente.h"

class Entidad {
private:
    int id;
    std::vector<std::unique_ptr<Componente>> componentes; // [CAP.12] Composicion, no herencia

public:
    explicit Entidad(int id) : id(id) {}

    int obtenerId() const { return id; }

    // [CAP.12] Toma posesion de un componente ya construido con std::make_unique.
    void agregarComponente(std::unique_ptr<Componente> componente) {
        componentes.push_back(std::move(componente));
    }

    // [CAP.12] Metodo de PLANTILLA: T puede ser ComponenteTransform,
    // [CAP.12] ComponenteSalud, o cualquier componente futuro. dynamic_cast
    // [CAP.12] comprueba en TIEMPO DE EJECUCION si cada componente
    // [CAP.12] almacenado es realmente del tipo T, y devuelve nullptr si
    // [CAP.12] ninguno lo es, en lugar de arriesgarse a una conversion
    // [CAP.12] incorrecta como hariamos con static_cast (capitulo 6).
    // [CAP.12] Esto SOLO funciona porque Componente tiene al menos un
    // [CAP.12] metodo virtual (es "polimorfico"): sin eso, dynamic_cast
    // [CAP.12] no dispondria de informacion de tipo en tiempo de ejecucion.
    template<typename T>
    T* obtenerComponente() {
        for (auto& componente : componentes) {
            T* resultado = dynamic_cast<T*>(componente.get());
            if (resultado != nullptr) {
                return resultado;
            }
        }
        return nullptr;
    }

    template<typename T>
    bool tieneComponente() {
        return obtenerComponente<T>() != nullptr;
    }

    // [CAP.12] Usado por la serializacion preliminar del apartado 12.6.
    std::vector<std::string> listarNombresComponentes() const {
        std::vector<std::string> nombres;
        for (const auto& componente : componentes) {
            nombres.push_back(componente->nombre());
        }
        return nombres;
    }

    void actualizarComponentes(float deltaTiempo) {
        for (auto& componente : componentes) {
            componente->actualizar(deltaTiempo);
        }
    }
};
