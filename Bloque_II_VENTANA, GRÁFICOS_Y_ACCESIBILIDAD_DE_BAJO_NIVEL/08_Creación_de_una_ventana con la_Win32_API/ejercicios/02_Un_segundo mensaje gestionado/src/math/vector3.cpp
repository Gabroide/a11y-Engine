// [CAP.5] vector3.cpp - Implementacion de los metodos de Vector3
#include "vector3.h"
#include <cstdio>
#include <cmath>

Vector3 Vector3::sumar(const Vector3& otro) const {
    return Vector3(x + otro.x, y + otro.y, z + otro.z);
}

Vector3 Vector3::escalar(float escalar) const {
    return Vector3(x * escalar, y * escalar, z * escalar);
}

float Vector3::longitud() const {
    return sqrtf(x * x + y * y + z * z);
}

void Vector3::imprimir() const {
    printf("Vector3(%.2f, %.2f, %.2f)\n", x, y, z);
}
