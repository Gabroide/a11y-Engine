// [CAP.8] ventana.cpp - Implementacion de la clase Ventana
#include "ventana.h"
#include <cstdio>

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

// [EJ.01] Nueva funcion para cambiar el titulo de la ventana
void Ventana::establecerTitulo(const char* nuevoTitulo) {
    if (!SetWindowTextA(hwnd, nuevoTitulo)) {
        printf("[Ventana] Error: no se pudo cambiar el titulo (codigo %lu).\n", GetLastError());
    }
}

void Ventana::ejecutarBucleDeMensajes() {
    MSG mensaje;
    while (GetMessage(&mensaje, NULL, 0, 0)) {
        TranslateMessage(&mensaje);
        DispatchMessage(&mensaje);
    }
}

LRESULT CALLBACK Ventana::procedimientoVentana(HWND hwnd, UINT mensaje, WPARAM wParam, LPARAM lParam) {
    switch (mensaje) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProcA(hwnd, mensaje, wParam, lParam);
    }
}
