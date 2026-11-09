// [CAP.5] main.cpp - Punto de entrada del proyecto Game Engine
#include <cstdio>
#include <cstdlib>
#include <memory>
#include "math/vector2.h"
#include "math/vector3.h"
#include "core/entidad.h"
#include "core/registro.h" // [CAP.5]

// [EJ.3] Esta funcion recibe un Registro por referencia, no por valor.
void escribirDosVeces(Registro& r, const char* mensaje) {
    r.escribir(mensaje);
    r.escribir(mensaje);
}

int main(void) {
    printf("Game Engine - Capitulo 5\n\n");

    // [CAP.5] --- El registro de eventos, gestionado con RAII ---
    Registro registro("bin/motor.log");
    escribirDosVeces(registro, "Motor iniciado (Capitulo 5).");

    // [CAP.5] --- Vectores usados ahora como objetos con metodos ---
    Vector2 posicion(1.0f, 2.0f);
    Vector2 velocidad(0.5f, -0.25f);
    Vector2 nuevaPosicion = posicion.sumar(velocidad);

    printf("Posicion inicial: ");
    posicion.imprimir();
    printf("Nueva posicion:   ");
    nuevaPosicion.imprimir();
    printf("Longitud del vector velocidad: %.2f\n\n", velocidad.longitud());

    // [CAP.5] --- Entidad con acceso encapsulado, no directo ---
    Entidad jugador(1, Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f));
    jugador.setEstado(ESTADO_MOVIENDO); // [CAP.5] Ya no se escribe "jugador.estado = ..."

    registro.escribir("Entidad jugador creada.");

    for (int paso = 0; paso < 3; paso++) {
        jugador.actualizar(1.0f);

        printf("Paso %d [%s]: ", paso, Entidad::nombreEstado(jugador.getEstado()));
        jugador.getPosicion().imprimir();

        char lineaRegistro[128];
        sprintf_s(lineaRegistro, "Paso %d: entidad %d en estado %s",
            paso, jugador.getId(), Entidad::nombreEstado(jugador.getEstado()));
        registro.escribir(lineaRegistro);
    }

    registro.escribir("Motor cerrado correctamente.");
    printf("\nConsulta bin/motor.log para ver el registro completo de esta ejecucion.\n");

    exit(EXIT_SUCCESS);
}
