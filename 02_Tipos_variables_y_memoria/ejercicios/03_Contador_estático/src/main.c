// [CAP.2] main.c - Punto de entrada del proyecto Game Engine
#include <stdio.h>
#include <stdlib.h>
#include "math/vector2.h" // [CAP.2]
#include "math/vector3.h" // [CAP.2]

int main(void) {
    printf("Game Engine - Capitulo 2\n\n");

    // [CAP.2] --- sizeof: medir en lugar de suponer ---
    printf("sizeof(float)   = %zu bytes\n", sizeof(float));
    printf("sizeof(Vector2) = %zu bytes\n", sizeof(Vector2));
    printf("sizeof(Vector3) = %zu bytes\n\n", sizeof(Vector3));

    // [CAP.2] --- Vectores en la pila ---
    Vector2 posicion = vector2_crear(1.0f, 2.0f);
    Vector2 velocidad = vector2_crear(0.5f, -0.25f);
    Vector2 nuevaPosicion = vector2_sumar(posicion, velocidad);

    printf("Posicion inicial: ");
    vector2_imprimir(posicion);
    printf("Nueva posicion:   ");
    vector2_imprimir(nuevaPosicion);

    // [CAP.2] --- Punteros: modificar una variable de forma indirecta ---
    float vida = 100.0f;
    float* punteroVida = &vida;
    printf("\nVida antes:   %.2f\n", vida);
    *punteroVida -= 35.0f;
    printf("Vida despues: %.2f\n", vida);

    // [CAP.2] --- Monton: un array de posiciones reservado dinamicamente ---
    int numeroEnemigos = 3;
    Vector3* posicionesEnemigos = (Vector3*)malloc(sizeof(Vector3) * numeroEnemigos);
    if (posicionesEnemigos == NULL) {
        printf("Error: no se pudo reservar memoria para los enemigos.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numeroEnemigos; i++) {
        posicionesEnemigos[i] = vector3_crear((float)i, 0.0f, (float)i * 2.0f);
    }

    // [Ej.3] --- Contador estatico: generar IDs unicos para entidades ---
    printf("\nPosiciones de los enemigos (reservadas en el monton):\n");
    for (int i = 0; i < numeroEnemigos; i++) {
        vector3_imprimir(posicionesEnemigos[i]);
    }

    free(posicionesEnemigos);   // [CAP.2] Liberacion obligatoria de memoria del monton
    posicionesEnemigos = NULL;  // [CAP.2] Evita usar el puntero tras liberarlo

    exit(EXIT_SUCCESS);
}
