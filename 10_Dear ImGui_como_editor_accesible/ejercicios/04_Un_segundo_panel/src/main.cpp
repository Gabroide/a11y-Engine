// [CAP.10] main.cpp - Punto de entrada del Game Engine
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
#include "editor/interfaz_editor.h" // [CAP.10]
#include "../libs/imgui/imgui.h"    // [CAP.10]

void abrirConsolaDeDepuracion(void) {
    AllocConsole();
    FILE* flujo;
    freopen_s(&flujo, "CONOUT$", "w", stdout);
    freopen_s(&flujo, "CONOUT$", "w", stderr);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    abrirConsolaDeDepuracion();
    printf("Game Engine - Capitulo 10\n\n");

    Registro registro("bin/motor.log");
    registro.escribir(std::string("Motor iniciado (Capitulo 10)."));

    Ventana ventana(hInstance, "Game Engine - Motor de prueba", 1280, 720, nCmdShow);
    ContextoOpenGL contexto(ventana.obtenerHandle());
    contexto.establecerVSync(true);

    InterfazEditor editor(ventana.obtenerHandle()); // [CAP.10]

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

        // [CAP.10] --- Calculo de FPS para mostrar en el panel ---
        fotogramasContados++;
        acumuladorFps += deltaTiempo;
        if (acumuladorFps >= 1.0f) {
            fps = (float)fotogramasContados / acumuladorFps;
            fotogramasContados = 0;
            acumuladorFps = 0.0f;
        }

        ImGuiIO& io = ImGui::GetIO();

        // [CAP.10] Si ImGui quiere capturar el teclado (por ejemplo, el
        // [CAP.10] usuario esta escribiendo en un campo de texto), no
        // [CAP.10] procesamos ESC como accion de cierre del motor.
        if (!io.WantCaptureKeyboard && EntradaTeclado::fuePulsadaEsteFrame(VK_ESCAPE)) {
            registro.escribir(std::string("Cierre solicitado mediante ESC (teclado)."));
            PostQuitMessage(0);
        }

        jugador.actualizar(deltaTiempo);

        // [CAP.10] --- Interfaz del editor ---
        editor.nuevoFrame();

        ImGui::Begin("Panel de depuracion"); // [CAP.10] Orden del codigo == orden de tabulacion

        ImGui::Text("FPS: %.1f", fps);

        ImGui::Text("Posicion del jugador: (%.2f, %.2f)", jugador.getPosicion().x, jugador.getPosicion().y);

        if (ImGui::Checkbox("VSync activado", &vsyncActivo)) {
            contexto.establecerVSync(vsyncActivo);
            registro.escribir(std::string("VSync cambiado desde el editor."));
        }
        InterfazEditor::anunciarSiCambioFoco("Casilla: VSync activado", registro); // [CAP.10]

        if (ImGui::Button("Reiniciar posicion del jugador")) {
            jugador.setEstado(ESTADO_IDLE);
            registro.escribir(std::string("Posicion del jugador reiniciada desde el editor."));
        }
        InterfazEditor::anunciarSiCambioFoco("Boton: Reiniciar posicion del jugador", registro); // [CAP.10]

        ImGui::End();

        // [EJ.04] --- Panel de entidad ---
        ImGui::SetNextWindowPos(ImVec2(340.0f, 60.0f), ImGuiCond_FirstUseEver);
        ImGui::Begin("Panel de entidad");
        ImGui::Text("ID del jugador: %d", jugador.getId());
        ImGui::Text("Estado actual: %s", Entidad::nombreEstado(jugador.getEstado()));
        ImGui::End();

        // [CAP.10] --- Renderizado: primero la escena, luego la interfaz encima ---
        float rojo = (sinf(tiempoTotal) + 1.0f) * 0.5f;
        glClearColor(rojo, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        editor.renderizar();       // [CAP.10] Dibuja los paneles de ImGui sobre la escena
        contexto.intercambiarBuffers();

        EntradaTeclado::actualizarFinDeFrame();
    }

    registro.escribir(std::string("Motor cerrado correctamente."));
    return 0;
}
