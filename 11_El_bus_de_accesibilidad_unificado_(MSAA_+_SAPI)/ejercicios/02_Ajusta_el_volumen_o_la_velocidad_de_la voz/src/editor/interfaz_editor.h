// [CAP.11] interfaz_editor.h - Capa de integracion de Dear ImGui en el motor
#pragma once
#include <windows.h>
#include "../core/registro.h"
#include "../accesibilidad/bus_accesibilidad.h" // [CAP.11]

class InterfazEditor {
private:
    HWND hwndVentana;                // [CAP.11] Necesario para notificarCambioFocoMSAA
    const char* ultimoControlAnunciado; // [CAP.11] Ya no es "static": ver el apartado 11.7

public:
    explicit InterfazEditor(HWND hwnd);
    ~InterfazEditor();

    InterfazEditor(const InterfazEditor&) = delete;
    InterfazEditor& operator=(const InterfazEditor&) = delete;

    void nuevoFrame();
    void renderizar();

    // [CAP.11] Ahora recibe el bus y el registro: sustituye por completo
    // [CAP.11] al printf "PROVISIONAL" del capitulo 10.
    void anunciarSiCambioFoco(const char* nombreControl, BusAccesibilidad& bus, Registro& registro);
};
