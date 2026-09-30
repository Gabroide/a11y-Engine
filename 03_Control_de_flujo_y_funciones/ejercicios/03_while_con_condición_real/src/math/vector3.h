// [CAP.2] vector3.h - Vector matematico de 3 componentes en coma flotante
#pragma once

typedef struct {
    float x; // [CAP.2]
    float y; // [CAP.2]
    float z; // [CAP.2]
} Vector3;

Vector3 vector3_crear(float x, float y, float z);       // [CAP.2]
Vector3 vector3_sumar(Vector3 a, Vector3 b);             // [CAP.2]
Vector3 vector3_escalar(Vector3 v, float escalar);       // [CAP.2]
void vector3_imprimir(Vector3 v);                        // [CAP.2]
