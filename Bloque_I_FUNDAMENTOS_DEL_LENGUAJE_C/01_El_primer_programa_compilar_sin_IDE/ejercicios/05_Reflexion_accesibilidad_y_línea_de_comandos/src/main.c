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

    printf("La hora actual es: %TIME%\n");
    printf("La fecha actual es: %DATE%\n");
    printf("El directorio actual es: %CD%\n");
    printf("El usuario actual es: %USERNAME%\n");
    printf("El sistema operativo es: %OS%\n");
    printf("El procesador es: %PROCESSOR_IDENTIFIER%\n");
    printf("La arquitectura del sistema es: %PROCESSOR_ARCHITECTURE%\n");
    printf("La version del sistema operativo es: %OS_VERSION%\n");
    printf("La version del compilador es: %COMPILER_VERSION%\n");
    printf("La version del enlazador es: %LINKER_VERSION%\n");
    printf("La version de la libreria estandar es: %STDLIB_VERSION%\n");
    printf("La version de la libreria de cabecera es: %HEADER_VERSION%\n");
    printf("La version de la libreria de tiempo es: %TIME_LIB_VERSION%\n");
    printf("La version de la libreria de entrada/salida es: %IO_LIB_VERSION%\n");
    printf("La version de la libreria de matematicas es: %MATH_LIB_VERSION%\n");
    printf("La version de la libreria de cadenas es: %STRING_LIB_VERSION%\n");
    printf("La version de la libreria de memoria es: %MEMORY_LIB_VERSION%\n");
    printf("La version de la libreria de hilos es: %THREAD_LIB_VERSION%\n");
    printf("La version de la libreria de red es: %NETWORK_LIB_VERSION%\n");
    printf("La version de la libreria de seguridad es: %SECURITY_LIB_VERSION%\n");
    printf("La version de la libreria de compresion es: %COMPRESSION_LIB_VERSION%\n");
    printf("La version de la libreria de cifrado es: %CRYPTO_LIB_VERSION%\n");
    printf("La version de la libreria de base de datos es: %DATABASE_LIB_VERSION%\n");
    printf("La version de la libreria de graficos es: %GRAPHICS_LIB_VERSION%\n");
    printf("La version de la libreria de audio es: %AUDIO_LIB_VERSION%\n");
    printf("La version de la libreria de video es: %VIDEO_LIB_VERSION%\n");
    printf("La version de la libreria de inteligencia artificial es: %AI_LIB_VERSION%\n");
    printf("La version de la libreria de fisica es: %PHYSICS_LIB_VERSION%\n");
    printf("La version de la libreria de realidad virtual es: %VR_LIB_VERSION%\n");
    printf("La version de la libreria de realidad aumentada es: %AR_LIB_VERSION%\n");
    printf("La version de la libreria de aprendizaje automatico es: %ML_LIB_VERSION%\n");
    printf("La version de la libreria de vision por computadora es: %CV_LIB_VERSION%\n");
    printf("La version de la libreria de procesamiento de lenguaje natural es: %NLP_LIB_VERSION%\n");
    printf("La version de la libreria de robótica es: %ROBOTICS_LIB_VERSION%\n");
    printf("La version de la libreria de simulación es: %SIMULATION_LIB_VERSION%\n");
    printf("La version de la libreria de automatización es: %AUTOMATION_LIB_VERSION%\n");
    
    // [CAP.1] exit() termina el programa de forma inmediata y controlada,
    // [CAP.1] devolviendo un codigo de salida al sistema operativo.
    // [CAP.1] EXIT_SUCCESS esta definido en stdlib.h y equivale a 0.
    exit(EXIT_SUCCESS);
}
