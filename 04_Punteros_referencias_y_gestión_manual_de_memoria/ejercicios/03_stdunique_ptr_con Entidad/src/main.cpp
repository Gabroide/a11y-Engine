// [CAP.4] main.cpp - Punto de entrada del proyecto Game Engine
// [CAP.4] Primer fichero del motor compilado como C++ (antes era main.c)
#include <cstdio>
#include <cstdlib>
#include <memory> // [CAP.4] std::unique_ptr, std::make_unique
#include "math/vector2.h"
#include "math/vector3.h"
#include "core/entidad.h"
#include "core/buffer_raii.h" // [CAP.4]

int main(void) {
    printf("Game Engine - Capitulo 4\n\n");

    // [CAP.4] --- Aritmetica de punteros ---
    int valores[5] = { 10, 20, 30, 40, 50 };
    int* p = valores;
    printf("Recorriendo un array con aritmetica de punteros:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(p + %d) = %d\n", i, *(p + i));
    }

    // [CAP.4] --- RAII con nuestra propia estructura ---
    printf("\n--- Demostracion de RAII ---\n");
    {
        BufferRAII buffer(5);
        buffer.datos[0] = 3.14f;
        printf("Primer valor del buffer: %f\n", buffer.datos[0]);
    } // El destructor de "buffer" se ejecuta automaticamente aqui
    printf("El buffer ya se ha liberado automaticamente.\n");

    // [CAP.4] --- std::unique_ptr sustituyendo a malloc/free (capitulo 2) ---
    printf("\n--- Posiciones de enemigos con std::unique_ptr ---\n");
    int numeroEnemigos = 3;
    std::unique_ptr<Vector3[]> posicionesEnemigos = std::make_unique<Vector3[]>(numeroEnemigos);

    for (int i = 0; i < numeroEnemigos; i++) {
        posicionesEnemigos[i] = vector3_crear((float)i, 0.0f, (float)i * 2.0f);
    }

    for (int i = 0; i < numeroEnemigos; i++) {
        vector3_imprimir(posicionesEnemigos[i]);
    }
    // No hay free() ni delete[]: posicionesEnemigos se libera sola al salir de main.

    // [CAP.4] --- Entidades actualizadas con referencias, no punteros ---
    printf("\n--- Entidades (ahora con referencias) ---\n");
    std::unique_ptr<Entidad> jugador = std::make_unique<Entidad>(entidad_crear(1, vector2_crear(0.0f, 0.0f), vector2_crear(1.0f, 0.0f)));
    jugador->estado = ESTADO_MOVIENDO;

    for (int paso = 0; paso < 3; paso++) {
        // [EJ. 3] Ahora jugador es un std::unique_ptr, asi que para pasar la referencia al objeto real usamos "*jugador"
        entidad_actualizar(*jugador, 1.0f);
        printf("Paso %d [%s]: ", paso, entidad_nombre_estado(jugador->estado));
        vector2_imprimir(jugador->posicion);
    }

    exit(EXIT_SUCCESS);
}
