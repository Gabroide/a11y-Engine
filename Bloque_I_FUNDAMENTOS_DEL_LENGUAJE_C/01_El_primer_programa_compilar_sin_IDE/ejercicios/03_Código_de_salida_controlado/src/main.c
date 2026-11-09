// [CAP.1] main.c - Punto de entrada del proyecto Game Engine
// [CAP.1] Este fichero se sustituira progresivamente por el motor real
// [CAP.1] a partir del capitulo 2. Por ahora, solo verificamos que la
// [CAP.1] cadena de herramientas (compilador + enlazador) funciona.

#include <stdio.h>   // [CAP.1] printf
#include <stdlib.h>  // [CAP.1] exit, EXIT_SUCCESS

int main(void) {
    // [CAP.1] printf escribe en la salida estandar (stdout).
    // [CAP.1] La consola de Windows es, por defecto, accesible: un lector
    // [CAP.1] de pantalla como Narrador, JAWS o NVDA puede leer este texto
    // [CAP.1] sin ninguna configuracion adicional por nuestra parte.
    printf("Game Engine - Capitulo 1\n");
    printf("Cadena de herramientas MSVC configurada correctamente.\n");

    // [EXE.2] nombre
    printf("Gabriel Cambronero Serentill\n");

    // [EXE.2] fecha
    printf("22 de septiembre de 2026");

    // [CAP.1] exit() termina el programa de forma inmediata y controlada,
    // [CAP.1] devolviendo un codigo de salida al sistema operativo.
    // [CAP.1] EXIT_SUCCESS esta definido en stdlib.h y equivale a 0.
    exit(2);
}
