// [EJ.4] mundo.c - Implementacion de la logica basica de mundo
#include <stddef.h>
#include "mundo.h"
#include "entidad.h"

void mundo_actualizar_todas(Entidad* entidades, int numero, float deltaTiempo) {
    if (entidades == NULL || numero <= 0) {
        return; // [EJ.4] Nunca desreferenciamos un puntero sin comprobarlo
    }

    for (int i = 0; i < numero; i++) {
        entidad_actualizar(&entidades[i], deltaTiempo);
        
        printf("Entidad %d [%s]: ", entidades[i].id, entidad_nombre_estado(entidades[i].estado));
        vector2_imprimir(entidades[i].posicion);
    }
}