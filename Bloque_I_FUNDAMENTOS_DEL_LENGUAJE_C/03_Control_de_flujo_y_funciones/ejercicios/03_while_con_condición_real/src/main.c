// [CAP.3] main.c - Punto de entrada del proyecto Game Engine
#include <stdio.h>
#include <stdlib.h>
#include "math/vector2.h"
#include "math/vector3.h"
#include "core/entidad.h" // [CAP.3]

int main(void) {
    printf("Game Engine - Capitulo 3\n\n");

    // [CAP.3] Creamos tres entidades con distintos estados iniciales.
    Entidad jugador = entidad_crear(1, vector2_crear(0.0f, 0.0f), vector2_crear(1.0f, 0.0f));
    Entidad enemigo = entidad_crear(2, vector2_crear(5.0f, 0.0f), vector2_crear(-0.5f, 0.0f));
    Entidad decoracion = entidad_crear(3, vector2_crear(2.0f, 2.0f), vector2_crear(0.0f, 0.0f));

    jugador.estado = ESTADO_MOVIENDO;   // [CAP.3] El jugador se movera
    enemigo.estado = ESTADO_MOVIENDO;   // [CAP.3] El enemigo tambien
    decoracion.estado = ESTADO_IDLE;    // [CAP.3] La decoracion se queda quieta

    Entidad entidades[3] = { jugador, enemigo, decoracion }; // [CAP.3]
    int numeroEntidades = 3;                                  // [CAP.3]
    float deltaTiempo = 1.0f; // [CAP.3] Un "paso" de tiempo simplificado

    // [CAP.3] Simulamos 3 pasos de actualizacion del motor.
    for (int paso = 0; paso < 3; paso++) {
        printf("--- Paso %d ---\n", paso);

        for (int i = 0; i < numeroEntidades; i++) {
            entidad_actualizar(&entidades[i], deltaTiempo); // [CAP.3] Paso por puntero

            printf("Entidad %d [%s]: ", entidades[i].id, entidad_nombre_estado(entidades[i].estado));
            vector2_imprimir(entidades[i].posicion);
        }
        printf("\n");
    }

    // [CAP.3] La entidad enemigo "muere" tras el tercer paso.
    entidades[1].estado = ESTADO_MUERTO;
    printf("El enemigo ha pasado a estado: %s\n", entidad_nombre_estado(entidades[1].estado));

    // [EJ.3] while: una cuenta atras que se ejecuta al menos una vez.
    int cuentaAtras = 3;
    printf("\nCerrando el motor en:\n");
    while (cuentaAtras > 0) {
        printf("%d...\n", cuentaAtras);
        cuentaAtras--;
    }

    printf("Motor cerrado correctamente.\n");

    exit(EXIT_SUCCESS);
}
