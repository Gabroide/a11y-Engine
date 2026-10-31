#pragma once

#include <windows.h>

class Ventana {
private:
    HWND hwnd;
    HINSTANCE instancia;

    static const char* NOMBRE_CLASE;
    static LRESULT CALLBACK procedimientoVentana(HWND hwnd, UINT mensaje, WPARAM wParam, LPARAM lParam);

public:
    Ventana(HINSTANCE instanciaApp, const char* titulo, int ancho, int alto, int modoMostrar);
    ~Ventana();

    HWND obtenerHandle() const;
    void ejecutarBucleDeMensajes();
};
