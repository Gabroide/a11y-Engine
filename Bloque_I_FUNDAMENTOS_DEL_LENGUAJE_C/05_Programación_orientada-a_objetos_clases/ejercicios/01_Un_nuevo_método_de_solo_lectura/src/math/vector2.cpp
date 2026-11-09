// [CAP.5] vector2.cpp - Implementacion de los metodos de Vector2
#include "vector2.h"
#include <cstdio>
#include <cmath>

Vector2 Vector2::sumar(const Vector2& otro) const {
    // [CAP.5] "this" es un puntero implicito al objeto sobre el que se
    // [CAP.5] llamo al metodo. this->x tambien podria escribirse "x"
    // [CAP.5] a secas, ya que dentro de un metodo los miembros son
    // [CAP.5] accesibles directamente por su nombre.
    return Vector2(x + otro.x, y + otro.y);
}

Vector2 Vector2::escalar(float escalar) const {
    return Vector2(x * escalar, y * escalar);
}

float Vector2::longitud() const {
    return sqrtf(x * x + y * y); // [CAP.5]
}

bool Vector2::esCero() const {
    return x == 0.0f && y == 0.0f;
}

void Vector2::imprimir() const {
    printf("Vector2(%.2f, %.2f)\n", x, y);
}
