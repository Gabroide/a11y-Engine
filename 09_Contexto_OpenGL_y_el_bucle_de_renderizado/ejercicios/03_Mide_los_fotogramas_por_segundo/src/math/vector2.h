// [CAP.5] vector2.h - Vector matematico de 2 componentes en coma flotante
#pragma once

struct Vector2 {
    float x; // [CAP.5]
    float y; // [CAP.5]

    // [CAP.5] Constructor con lista de inicializacion y valores por defecto.
    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    // [CAP.5] Antes eran funciones libres (vector2_sumar, etc.).
    // [CAP.5] Ahora son METODOS: se llaman sobre un objeto concreto,
    // [CAP.5] por ejemplo "a.sumar(b)" en lugar de "vector2_sumar(a, b)".
    Vector2 sumar(const Vector2& otro) const;
    Vector2 escalar(float escalar) const;
    float longitud() const;
    void imprimir() const;
};
