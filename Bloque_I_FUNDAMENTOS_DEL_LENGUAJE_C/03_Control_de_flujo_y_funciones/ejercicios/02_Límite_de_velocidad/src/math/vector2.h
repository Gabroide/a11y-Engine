// [CAP.2] vector2.h - Vector matematico de 2 componentes en coma flotante
#pragma once // [CAP.2] Evita que este fichero se incluya mas de una vez en la misma compilacion

typedef struct {
    float x; // [CAP.2]
    float y; // [CAP.2]
} Vector2;

// [CAP.2] Crea un Vector2 a partir de dos componentes.
Vector2 vector2_crear(float x, float y);

// [CAP.2] Suma dos vectores componente a componente.
Vector2 vector2_sumar(Vector2 a, Vector2 b);

// [CAP.2] Escala un vector multiplicando ambas componentes por "escalar".
Vector2 vector2_escalar(Vector2 v, float escalar);

// [CAP.2] Imprime un vector con un formato legible y consistente,
// [CAP.2] pensado para que un lector de pantalla lo anuncie con claridad.
void vector2_imprimir(Vector2 v);
