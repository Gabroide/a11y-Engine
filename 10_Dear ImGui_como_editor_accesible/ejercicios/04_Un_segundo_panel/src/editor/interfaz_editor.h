// [CAP.10] interfaz_editor.h - Capa de integracion de Dear ImGui en el motor
#pragma once
#include <windows.h>
#include "../core/registro.h"

class InterfazEditor {
private:
    // [CAP.10] Recordamos el ultimo control anunciado para no repetir el
    // [CAP.10] mismo anuncio en cada fotograma mientras el foco no cambia.
    // [CAP.10] Este es el "punto de enganche" rudimentario que el capitulo
    // [CAP.10] 11 sustituira por una llamada real a SAPI.
    static const char* ultimoControlAnunciado;

public:
    explicit InterfazEditor(HWND hwnd);
    ~InterfazEditor();

    InterfazEditor(const InterfazEditor&) = delete;
    InterfazEditor& operator=(const InterfazEditor&) = delete;

    void nuevoFrame();
    void renderizar();

    // [CAP.10] Debe llamarse justo despues de dibujar cualquier control
    // [CAP.10] interactivo (boton, casilla, deslizador...) sobre el que
    // [CAP.10] tenga sentido anunciar el foco.
    static void anunciarSiCambioFoco(const char* nombreControl, Registro& registro);
};
