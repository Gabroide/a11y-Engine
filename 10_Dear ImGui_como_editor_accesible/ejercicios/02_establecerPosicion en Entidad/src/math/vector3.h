// [CAP.5] vector3.h - Vector matematico de 3 componentes en coma flotante
#pragma once

struct Vector3 {
    float x; // [CAP.5]
    float y; // [CAP.5]
    float z; // [CAP.5]

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    Vector3 sumar(const Vector3& otro) const;
    Vector3 escalar(float escalar) const;
    float longitud() const;
    void imprimir() const;
};
