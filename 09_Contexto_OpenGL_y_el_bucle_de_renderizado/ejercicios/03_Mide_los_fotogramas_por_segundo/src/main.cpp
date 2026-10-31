// [CAP.9] main.cpp - Punto de entrada del Game Engine
#include <windows.h>
#include <gl/gl.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include "core/registro.h"
#include "core/entidad.h"
#include "plataforma/ventana.h"
#include "plataforma/contexto_opengl.h" // [CAP.9]
#include "plataforma/entrada_teclado.h" // [CAP.9]

void abrirConsolaDeDepuracion(void) {
    AllocConsole();
    FILE* flujo;
    freopen_s(&flujo, "CONOUT$", "w", stdout);
    freopen_s(&flujo, "CONOUT$", "w", stderr);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    abrirConsolaDeDepuracion();
    printf("Game Engine - Capitulo 9\n\n");

    Registro registro("bin/motor.log");
    registro.escribir(std::string("Motor iniciado (Capitulo 9)."));

    Ventana ventana(hInstance, "Game Engine - Motor de prueba", 1280, 720, nCmdShow);
    ContextoOpenGL contexto(ventana.obtenerHandle()); // [CAP.9]
    contexto.establecerVSync(true);                    // [CAP.9] Ver apartado 9.5

    registro.escribir(std::string("Ventana y contexto OpenGL creados."));
    printf("Pulsa ESC para cerrar el motor de forma accesible (sin necesidad de raton).\n");

    Entidad jugador(1, Vector2(0.0f, 0.0f), Vector2(0.3f, 0.0f)); // [CAP.9] Reutilizamos el motor del Bloque I
    jugador.setEstado(ESTADO_MOVIENDO);

    // [CAP.9] Temporizador de alta resolucion (ver apartado 9.9)
    LARGE_INTEGER frecuencia;
    QueryPerformanceFrequency(&frecuencia);
    LARGE_INTEGER tiempoAnterior;
    QueryPerformanceCounter(&tiempoAnterior);

    float tiempoTotal = 0.0f;               // [EJ.3] Acumulado desde el inicio, para animar el color de fondo
    float acumuladorRegistro = 0.0f;        // [EJ.3] Para no escribir en el log en CADA fotograma
    float acumuladorFPS = 0.0f;             // [EJ.3] Para mostrar los FPS en la consola
    unsigned int fotogramasEsteSegundo = 0; // [EJ.3] Contador de fotogramas para mostrar los FPS

    MSG mensaje;
    bool ejecutando = true;

    while (ejecutando) {
        // --- 1. Mensajes del sistema operativo (no bloqueante) ---
        while (PeekMessage(&mensaje, NULL, 0, 0, PM_REMOVE)) {
            if (mensaje.message == WM_QUIT) {
                ejecutando = false;
            }
            TranslateMessage(&mensaje);
            DispatchMessage(&mensaje);
        }
        if (!ejecutando) {
            break;
        }

        // --- 2. Tiempo delta ---
        LARGE_INTEGER tiempoActual;
        QueryPerformanceCounter(&tiempoActual);
        float deltaTiempo = (float)(tiempoActual.QuadPart - tiempoAnterior.QuadPart) / (float)frecuencia.QuadPart;
        tiempoAnterior = tiempoActual;
        tiempoTotal += deltaTiempo;

        // --- 3. Entrada de teclado: cierre accesible sin raton ---
        if (EntradaTeclado::fuePulsadaEsteFrame(VK_ESCAPE)) {
            registro.escribir(std::string("Cierre solicitado mediante ESC (teclado)."));
            PostQuitMessage(0);
        }

        // --- 4. Actualizacion (reutilizando el motor del Bloque I) ---
        jugador.actualizar(deltaTiempo);

        acumuladorRegistro += deltaTiempo;
        if (acumuladorRegistro >= 1.0f) { // [CAP.9] Registramos como mucho una vez por segundo
            char linea[128];
            Vector2 posicion = jugador.getPosicion();
            sprintf_s(linea, sizeof(linea), "Posicion del jugador tras %.1fs: (%.2f, %.2f)",
                tiempoTotal, posicion.x, posicion.y);
            registro.escribir(linea);
            acumuladorRegistro = 0.0f;
        }

        // --- 5. Renderizado ---
        // [CAP.9] Un color de fondo animado, solo para comprobar visualmente
        // [CAP.9] que el bucle esta funcionando fotograma a fotograma.
        float rojo = (sinf(tiempoTotal) + 1.0f) * 0.5f; // [EJ.3] Oscila entre 0.0 y 1.0
        glClearColor(rojo, 0.2f, 0.4f, 1.0f);           // [EJ.3] Color de fondo animado
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        contexto.intercambiarBuffers();

        acumuladorFPS += deltaTiempo;
        ++fotogramasEsteSegundo;
        if (acumuladorFPS >= 1.0f) {
            printf("FPS: %u\n", fotogramasEsteSegundo);
            acumuladorFPS = 0.0f;
            fotogramasEsteSegundo = 0;
        }

        // --- 6. Cierre del fotograma ---
        EntradaTeclado::actualizarFinDeFrame();
    }

    registro.escribir(std::string("Motor cerrado correctamente."));
    return 0;
}
