// [CAP.4] vector3.cpp - Implementacion de las operaciones de Vector3
#include "vector3.h"
#include <stdio.h>

Vector3 vector3_crear(float x, float y, float z) {
    Vector3 resultado;
    resultado.x = x; // [CAP.2]
    resultado.y = y; // [CAP.2]
    resultado.z = z; // [CAP.2]
    return resultado;
}

Vector3 vector3_sumar(Vector3 a, Vector3 b) {
    return vector3_crear(a.x + b.x, a.y + b.y, a.z + b.z); // [CAP.2]
}

Vector3 vector3_escalar(Vector3 v, float escalar) {
    return vector3_crear(v.x * escalar, v.y * escalar, v.z * escalar); // [CAP.2]
}

void vector3_imprimir(Vector3 v) {
    printf("Vector3(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z); // [CAP.2]
}
