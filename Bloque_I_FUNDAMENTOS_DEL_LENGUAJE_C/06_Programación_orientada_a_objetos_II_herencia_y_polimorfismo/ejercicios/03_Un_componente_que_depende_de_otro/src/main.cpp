// [CAP.6] main.cpp - Punto de entrada del proyecto Game Engine
#include <cstdio>
#include <cstdlib>
#include <memory>
#include "math/vector2.h"
#include "math/vector3.h"
#include "core/entidad.h"
#include "core/registro.h"
#include "components/componente.h"            // [CAP.6]
#include "components/componente_transform.h"  // [CAP.6]
#include "components/componente_salud.h"      // [CAP.6]

int main(void) {
    printf("Game Engine - Capitulo 6\n\n");

    Registro registro("bin/motor.log");
    registro.escribir("Motor iniciado (Capitulo 6).");

    // [EJ.3] Prueba aislada: al moverse mas alla del limite, recibe dano.
    ComponenteTransform transformPrueba(Vector2(9.5f, 0.0f), Vector2(1.0f, 0.0f));
    ComponenteSalud saludPrueba(100.0f, 0.0f);
    transformPrueba.actualizar(1.0f);
    transformPrueba.aplicarDano(saludPrueba, 15.0f);
    printf("Prueba de limite: x = %.2f, vida = %.2f\n\n",
        transformPrueba.obtenerPosicion().x, saludPrueba.obtenerVidaActual());

    // [CAP.6] Un array de punteros a la clase BASE Componente.
    // [CAP.6] Cada posicion puede contener un tipo derivado distinto:
    // [CAP.6] esto es polimorfismo funcionando delante de tus ojos.
    // [CAP.6] Usamos unique_ptr (capitulo 4) para que cada componente
    // [CAP.6] se libere automaticamente al final del programa.
    const int numeroComponentes = 2;
    std::unique_ptr<Componente> componentes[numeroComponentes];

    componentes[0] = std::make_unique<ComponenteTransform>(Vector2(0.0f, 0.0f), Vector2(1.0f, 0.5f));
    componentes[1] = std::make_unique<ComponenteSalud>(100.0f, 2.0f);

    // [CAP.6] Simulamos dano sobre el componente de salud antes de actualizar.
    // [CAP.6] "static_cast" sera formalizado en un capitulo posterior; por
    // [CAP.6] ahora, es simplemente la forma segura de decir "se que este
    // [CAP.6] Componente concreto es en realidad un ComponenteSalud".
    static_cast<ComponenteSalud*>(componentes[1].get())->recibirDano(40.0f);

    printf("--- Simulando 3 fotogramas ---\n");
    for (int fotograma = 0; fotograma < 3; fotograma++) {
        printf("\nFotograma %d:\n", fotograma);

        for (int i = 0; i < numeroComponentes; i++) {
            // [CAP.6] Llamada POLIMORFICA: el codigo no sabe (ni le hace
            // [CAP.6] falta saber) si "componentes[i]" es un Transform,
            // [CAP.6] una Salud, o cualquier otro componente futuro.
            componentes[i]->actualizar(1.0f);
            printf("  [%s] actualizado.\n", componentes[i]->nombre());
        }
    }

    ComponenteSalud* salud = static_cast<ComponenteSalud*>(componentes[1].get());
    printf("\nVida final tras la regeneracion: %.2f\n", salud->obtenerVidaActual());

    registro.escribir("Motor cerrado correctamente.");

    // [CAP.6] No hay ningun "delete": los unique_ptr liberan cada
    // [CAP.6] componente automaticamente al salir de ambito, y gracias
    // [CAP.6] al destructor VIRTUAL de Componente, cada uno se destruye
    // [CAP.6] correctamente segun su tipo real, no como un simple Componente.
    exit(EXIT_SUCCESS);
}