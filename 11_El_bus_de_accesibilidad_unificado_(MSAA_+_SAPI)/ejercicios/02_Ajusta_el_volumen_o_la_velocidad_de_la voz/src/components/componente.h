// [CAP.6] componente.h - Interfaz base de todos los componentes del motor
#pragma once

class Componente {
public:
    // [CAP.6] Destructor virtual: obligatorio en toda clase base (ver 6.4).
    virtual ~Componente() = default;

    // [CAP.6] Funcion virtual pura: cada componente concreto decide
    // [CAP.6] que significa "actualizarse" para el.
    virtual void actualizar(float deltaTiempo) = 0;

    // [CAP.6] Tambien pura: cada componente se identifica a si mismo.
    // [CAP.6] La usaremos, entre otras cosas, para mensajes de registro
    // [CAP.6] y, mas adelante, para el inspector del editor (capitulo 19).
    virtual const char* nombre() const = 0;
};
