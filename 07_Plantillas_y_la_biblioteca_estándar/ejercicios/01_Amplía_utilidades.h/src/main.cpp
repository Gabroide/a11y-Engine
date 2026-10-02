// [CAP.7] main.cpp - Punto de entrada del proyecto Game Engine
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>          // [CAP.7]
#include <string>          // [CAP.7]
#include <unordered_map>   // [CAP.7]
#include "math/vector2.h"
#include "math/vector3.h"
#include "core/entidad.h"
#include "core/registro.h"
#include "core/utilidades.h" // [CAP.7]
#include "components/componente.h"
#include "components/componente_transform.h"
#include "components/componente_salud.h"

int main(void) {
    printf("Game Engine - Capitulo 7\n\n");

    Registro registro("bin/motor.log");
    registro.escribir(std::string("Motor iniciado (Capitulo 7).")); // [CAP.7] Sobrecarga con std::string

    // [CAP.7] "restringir" (nuestra plantilla) aplicada a un caso real:
    // [CAP.7] limitar una velocidad calculada a un rango razonable.
    float velocidadCalculada = 8.5f;
    float velocidadFinal = restringir(velocidadCalculada, -5.0f, 5.0f);
    printf("Velocidad calculada: %.2f -> restringida: %.2f\n\n", velocidadCalculada, velocidadFinal);

    int mayorEntero = maximo(12, 7);
    float mayorDecimal = maximo(3.5f, 2.25f);
    std::string mayorCadena = maximo(std::string("manzana"), std::string("pera"));
    printf("Maximo entre enteros (12, 7): %d\n", mayorEntero);
    printf("Maximo entre decimales (3.5, 2.25): %.2f\n", mayorDecimal);
    printf("Maximo entre cadenas (manzana, pera): %s\n",
        mayorCadena.c_str()); // std::string compara lexicograficamente.

    // [CAP.7] Antes: std::unique_ptr<Componente> componentes[numeroComponentes];
    // [CAP.7] Ahora: un vector que puede crecer sin limite fijado de antemano.
    std::vector<std::unique_ptr<Componente>> componentes;
    componentes.push_back(std::make_unique<ComponenteTransform>(Vector2(0.0f, 0.0f), Vector2(1.0f, 0.5f)));
    componentes.push_back(std::make_unique<ComponenteSalud>(100.0f, 2.0f));
    componentes.push_back(std::make_unique<ComponenteTransform>(Vector2(5.0f, 5.0f), Vector2(-1.0f, 0.0f)));

    static_cast<ComponenteSalud*>(componentes[1].get())->recibirDano(40.0f);

    printf("--- Simulando 3 fotogramas ---\n");
    for (int fotograma = 0; fotograma < 3; fotograma++) {
        printf("\nFotograma %d:\n", fotograma);

        // [CAP.7] Bucle basado en rango: mas legible que un indice manual,
        // [CAP.7] y funciona sin cambios aunque "componentes" crezca o
        // [CAP.7] encoja entre una ejecucion y otra del programa.
        for (const auto& componente : componentes) {
            componente->actualizar(1.0f);
            printf("  [%s] actualizado.\n", componente->nombre());
        }
    }

    // [CAP.7] std::unordered_map para contar tipos de componente presentes.
    std::unordered_map<std::string, int> conteoPorTipo;
    for (const auto& componente : componentes) {
        conteoPorTipo[componente->nombre()]++;
    }

    printf("\n--- Resumen de componentes ---\n");
    for (const auto& par : conteoPorTipo) {
        std::string linea = par.first + ": " + std::to_string(par.second);
        printf("%s\n", linea.c_str());
        registro.escribir(linea); // [CAP.7] Usa la sobrecarga con std::string
    }

    registro.escribir("Motor cerrado correctamente.");

    // [CAP.7] Sin delete, sin free: vector, unique_ptr y string se
    // [CAP.7] liberan todos automaticamente al salir de ambito.
    exit(EXIT_SUCCESS);
}
