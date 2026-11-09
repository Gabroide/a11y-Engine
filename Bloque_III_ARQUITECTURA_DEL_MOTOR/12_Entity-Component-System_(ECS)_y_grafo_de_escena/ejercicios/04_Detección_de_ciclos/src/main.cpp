// [CAP.12] main.cpp - Punto de entrada del Game Engine
#include <windows.h>
#include <gl/gl.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include "core/registro.h"
#include "core/mundo.h" // [CAP.12] Sustituye a la inclusion directa de entidad.h
#include "components/componente_transform.h"
#include "components/componente_salud.h"
#include "plataforma/ventana.h"
#include "plataforma/contexto_opengl.h"
#include "plataforma/entrada_teclado.h"
#include "editor/interfaz_editor.h"
#include "accesibilidad/bus_accesibilidad.h"
#include "../libs/imgui/imgui.h"

bool tieneCiclo(ComponenteTransform* transform) {
    if (transform == nullptr) {
        return false;
    }

    ComponenteTransform* actual = transform->obtenerTransformPadre();
    int iteraciones = 0;
    while (actual != nullptr && iteraciones < 1000) {
        if (actual == transform) {
            return true;
        }
        actual = actual->obtenerTransformPadre();
        iteraciones++;
    }
    return false;
}

bool creariaCiclo(ComponenteTransform* transform, ComponenteTransform* nuevoPadre) {
    ComponenteTransform* actual = nuevoPadre;
    int iteraciones = 0;
    while (actual != nullptr && iteraciones < 1000) {
        if (actual == transform) {
            return true;
        }
        actual = actual->obtenerTransformPadre();
        iteraciones++;
    }
    return actual != nullptr;
}

void abrirConsolaDeDepuracion(void) {
    AllocConsole();
    FILE* flujo;
    freopen_s(&flujo, "CONOUT$", "w", stdout);
    freopen_s(&flujo, "CONOUT$", "w", stderr);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    abrirConsolaDeDepuracion();
    printf("Game Engine - Capitulo 12\n\n");

    Registro registro("bin/motor.log");
    registro.escribir(std::string("Motor iniciado (Capitulo 12)."));

    Ventana ventana(hInstance, "Game Engine - Motor de prueba", 1280, 720, nCmdShow);
    ContextoOpenGL contexto(ventana.obtenerHandle());
    contexto.establecerVSync(true);

    InterfazEditor editor(ventana.obtenerHandle());
    BusAccesibilidad busAccesibilidad;
    busAccesibilidad.anunciar("Motor de prueba iniciado.", registro);

    // [CAP.12] --- Construccion de la escena con el nuevo ECS ---
    Mundo mundo;

    Entidad& jugador = mundo.crearEntidad(1);
    jugador.agregarComponente(std::make_unique<ComponenteTransform>(Vector2(0.0f, 0.0f), Vector2(0.3f, 0.0f)));
    jugador.agregarComponente(std::make_unique<ComponenteSalud>(100.0f, 2.0f));

    // [CAP.12] Un pequeño grafo de escena: una entidad raiz con dos hijos.
    Entidad& raiz = mundo.crearEntidad(2);
    raiz.agregarComponente(std::make_unique<ComponenteTransform>(Vector2(5.0f, 5.0f), Vector2(0.0f, 0.0f)));

    Entidad& hijoIzquierdo = mundo.crearEntidad(3);
    hijoIzquierdo.agregarComponente(std::make_unique<ComponenteTransform>(Vector2(-1.0f, 0.0f), Vector2(0.0f, 0.0f)));
    ComponenteTransform* transformHijoIzquierdo = hijoIzquierdo.obtenerComponente<ComponenteTransform>();
    ComponenteTransform* transformRaiz = raiz.obtenerComponente<ComponenteTransform>();
    if (tieneCiclo(transformHijoIzquierdo) || creariaCiclo(transformHijoIzquierdo, transformRaiz)) {
        printf("Aviso: se rechazo asignar el padre del hijo izquierdo porque crearia un ciclo.\n");
    } else {
        transformHijoIzquierdo->establecerPadre(transformRaiz);
    }

    Entidad& hijoDerecho = mundo.crearEntidad(4);
    hijoDerecho.agregarComponente(std::make_unique<ComponenteTransform>(Vector2(1.0f, 0.0f), Vector2(0.0f, 0.0f)));
    ComponenteTransform* transformHijoDerecho = hijoDerecho.obtenerComponente<ComponenteTransform>();
    if (tieneCiclo(transformHijoDerecho) || creariaCiclo(transformHijoDerecho, transformRaiz)) {
        printf("Aviso: se rechazo asignar el padre del hijo derecho porque crearia un ciclo.\n");
    } else {
        transformHijoDerecho->establecerPadre(transformRaiz);
    }

    mundo.imprimirJerarquia(); // [CAP.12] Serializacion preliminar (ver apartado 12.6)

    printf("Posicion global del hijo izquierdo: ");
    hijoIzquierdo.obtenerComponente<ComponenteTransform>()->obtenerPosicionGlobal().imprimir();

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
            busAccesibilidad.anunciar("Cerrando el motor.", registro);
            PostQuitMessage(0);
        }

        mundo.actualizar(deltaTiempo); // [CAP.12] Actualiza TODAS las entidades de la escena

        editor.nuevoFrame();

        ImGui::Begin("Panel de depuracion");
        ImGui::Text("FPS: %.1f", fps);

        Vector2 posicionJugador = jugador.obtenerComponente<ComponenteTransform>()->obtenerPosicion();
        ImGui::Text("Posicion del jugador: (%.2f, %.2f)", posicionJugador.x, posicionJugador.y);

        if (ImGui::Checkbox("VSync activado", &vsyncActivo)) {
            contexto.establecerVSync(vsyncActivo);
        }
        std::string estadoVSync = vsyncActivo ? "activada" : "desactivada";
        editor.anunciarSiCambioFoco(("Casilla, VSync, " + estadoVSync).c_str(), busAccesibilidad, registro);

        if (ImGui::Button("Reiniciar posicion del jugador")) {
            jugador.obtenerComponente<ComponenteTransform>()->establecerPosicion(Vector2(0.0f, 0.0f));
            busAccesibilidad.anunciar("Posicion del jugador reiniciada.", registro);
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