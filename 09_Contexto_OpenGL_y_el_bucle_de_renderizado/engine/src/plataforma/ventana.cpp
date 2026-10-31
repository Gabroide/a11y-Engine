// [CAP.8] ventana.cpp - Implementacion de la clase Ventana
#include "ventana.h"
#include <cstdio>
#include "entrada_teclado.h" // [CAP.9] Se anade a los includes existentes

const char* Ventana::NOMBRE_CLASE = "GameEngineWindowClass"; // [CAP.8]

Ventana::Ventana(HINSTANCE instanciaApp, const char* titulo, int ancho, int alto, int modoMostrar)
    : hwnd(nullptr), instancia(instanciaApp) {

    WNDCLASSEXA wc = {};
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.lpfnWndProc = procedimientoVentana;
    wc.hInstance = instancia;
    wc.lpszClassName = NOMBRE_CLASE;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassExA(&wc);

    hwnd = CreateWindowExA(
        0,
        NOMBRE_CLASE,
        titulo, // [CAP.8] El titulo se recibe como parametro: ver el apartado 8.7
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        ancho, alto,
        NULL, NULL,
        instancia,
        NULL
    );

    if (hwnd == NULL) {
        printf("[Ventana] Error: no se pudo crear la ventana.\n");
        return;
    }

    ShowWindow(hwnd, modoMostrar);
}

Ventana::~Ventana() {
    if (hwnd != nullptr) {
        DestroyWindow(hwnd);          // [CAP.8] Libera el recurso HWND
    }
    UnregisterClassA(NOMBRE_CLASE, instancia); // [CAP.8] Libera el recurso de la clase registrada
}

HWND Ventana::obtenerHandle() const {
    return hwnd;
}

void Ventana::ejecutarBucleDeMensajes() {
    MSG mensaje;
    bool ejecutando = true;

    while (ejecutando) {
        // [CAP.9] Procesamos TODOS los mensajes pendientes sin bloquear.
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

        LARGE_INTEGER frecuencia;
        QueryPerformanceFrequency(&frecuencia); // Cuentas por segundo de este equipo (se obtiene una sola vez)

        LARGE_INTEGER tiempoAnterior;
        QueryPerformanceCounter(&tiempoAnterior);

        // ... en cada iteracion del game loop ...
        LARGE_INTEGER tiempoActual;
        QueryPerformanceCounter(&tiempoActual);

        float deltaTiempo = (float)(tiempoActual.QuadPart - tiempoAnterior.QuadPart) / (float)frecuencia.QuadPart;
        tiempoAnterior = tiempoActual;
    }
}

LRESULT CALLBACK Ventana::procedimientoVentana(HWND hwnd, UINT mensaje, WPARAM wParam, LPARAM lParam) {
    switch (mensaje) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_KEYDOWN: // [CAP.9]
            EntradaTeclado::actualizarTecla((int)wParam, true);
            return 0;

        case WM_KEYUP: // [CAP.9]
            EntradaTeclado::actualizarTecla((int)wParam, false);
            return 0;

        default:
            return DefWindowProcA(hwnd, mensaje, wParam, lParam);
    }
}