#include "vector2.h"
#include <stdio.h>

Vector2 vector2_crear(float x, float y) {
    Vector2 resultado;   // [CAP.2] Variable local: vive en la pila
    resultado.x = x;     // [CAP.2]
    resultado.y = y;     // [CAP.2]
    return resultado;    // [CAP.2] Se devuelve una copia del struct
}

Vector2 vector2_sumar(Vector2 a, Vector2 b) {
    return vector2_crear(a.x + b.x, a.y + b.y); // [CAP.2]
}

Vector2 vector2_restar(Vector2 a, Vector2 b) {
    return vector2_crear(a.x - b.x, a.y - b.y); // [EJ.2]
}

Vector2 vector2_escalar(Vector2 v, float escalar) {
    return vector2_crear(v.x * escalar, v.y * escalar); // [CAP.2]
}

void vector2_imprimir(Vector2 v) {
    // [CAP.2] %.2f redondea a 2 decimales: evita leer en voz alta ruido
    // [CAP.2] de precision como "3.09999998" en lugar de "3.10".
    printf("Vector2(%.2f, %.2f)\n", v.x, v.y);
}