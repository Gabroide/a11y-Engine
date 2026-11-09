// [CAP.11] main.cpp - Punto de entrada del Game Engine
#include <windows.h>
#include <gl/gl.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include "core/registro.h"
#include "core/entidad.h"
#include "plataforma/ventana.h"
#include "plataforma/contexto_opengl.h"
#include "plataforma/entrada_teclado.h"
#include "editor/interfaz_editor.h"
#include "accesibilidad/bus_accesibilidad.h" // [CAP.11]
#include "../libs/imgui/imgui.h"

void abrirConsolaDeDepuracion(void) {
    AllocConsole();
    FILE* flujo;
    freopen_s(&flujo, "CONOUT$", "w", stdout);
    freopen_s(&flujo, "CONOUT$", "w", stderr);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    abrirConsolaDeDepuracion();
    printf("Game Engine - Capitulo 11\n\n");

    Registro registro("bin/motor.log");
    registro.escribir(std::string("Motor iniciado (Capitulo 11)."));

    Ventana ventana(hInstance, "Game Engine - Motor de prueba", 1280, 720, nCmdShow);
    ContextoOpenGL contexto(ventana.obtenerHandle());
    contexto.establecerVSync(true);

    InterfazEditor editor(ventana.obtenerHandle());
    BusAccesibilidad busAccesibilidad; // [CAP.11]
    busAccesibilidad.anunciar("Motor de prueba iniciado.", PrioridadAnuncio::NORMAL, registro); // [CAP.11] Primer anuncio audible

    Entidad jugador(1, Vector2(0.0f, 0.0f), Vector2(0.3f, 0.0f));
    jugador.setEstado(ESTADO_MOVIENDO);

    LARGE_INTEGER frecuencia;
    QueryPerformanceFrequency(&frecuencia);
    LARGE_INTEGER tiempoAnterior;
    QueryPerformanceCounter(&tiempoAnterior);

    float tiempoTotal = 0.0f;
    float fps = 0.0f;
    float acumuladorFps = 0.0f;
    int fotogramasContados = 0;
    bool vsyncActivo = true;

    MSG mensaje;
    bool ejecutando = true;

    while (ejecutando) {
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

        LARGE_INTEGER tiempoActual;
        QueryPerformanceCounter(&tiempoActual);
        float deltaTiempo = (float)(tiempoActual.QuadPart - tiempoAnterior.QuadPart) / (float)frecuencia.QuadPart;
        tiempoAnterior = tiempoActual;
        tiempoTotal += deltaTiempo;

        fotogramasContados++;
        acumuladorFps += deltaTiempo;
        if (acumuladorFps >= 1.0f) {
            fps = (float)fotogramasContados / acumuladorFps;
            fotogramasContados = 0;
            acumuladorFps = 0.0f;
        }

        ImGuiIO& io = ImGui::GetIO();

        if (!io.WantCaptureKeyboard && EntradaTeclado::fuePulsadaEsteFrame(VK_ESCAPE)) {
            busAccesibilidad.anunciar("Cerrando el motor.", PrioridadAnuncio::NORMAL, registro); // [CAP.11]
            PostQuitMessage(0);
        }

        jugador.actualizar(deltaTiempo);

        editor.nuevoFrame();

        ImGui::Begin("Panel de depuracion");

        ImGui::Text("FPS: %.1f", fps);
        ImGui::Text("Posicion del jugador: (%.2f, %.2f)", jugador.getPosicion().x, jugador.getPosicion().y);

        if (ImGui::Checkbox("VSync activado", &vsyncActivo)) {
            contexto.establecerVSync(vsyncActivo);
        }
        // [CAP.11] Mensaje con tipo, nombre Y estado: la leccion del capitulo 10.
        std::string estadoVSync = vsyncActivo ? "activada" : "desactivada";
        editor.anunciarSiCambioFoco(("Casilla, VSync, " + estadoVSync).c_str(), busAccesibilidad, registro);

        if (ImGui::Button("Reiniciar posicion del jugador")) {
            jugador.setEstado(ESTADO_IDLE);
            busAccesibilidad.anunciar("Posicion del jugador reiniciada.", PrioridadAnuncio::ALTA, registro); // [CAP.11] La confirmacion prevalece sobre el anuncio NORMAL del foco
        }
        editor.anunciarSiCambioFoco("Boton, Reiniciar posicion del jugador", busAccesibilidad, registro);

        ImGui::End();

        float rojo = (sinf(tiempoTotal) + 1.0f) * 0.5f;
        glClearColor(rojo, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        editor.renderizar();
        contexto.intercambiarBuffers();

        EntradaTeclado::actualizarFinDeFrame();
    }

    registro.escribir(std::string("Motor cerrado correctamente."));
    return 0;
}