// [CAP.8] Punto de entrada del Game Engine (ahora con ventana real)
#include <windows.h>
#include <cstdio>
#include <string>
#include "core/registro.h"
#include "plataforma/ventana.h"

void abrirConsolaDeDepuracion(void) {
    AllocConsole();
    FILE* flujo;
    freopen_s(&flujo, "CONOUT$", "w", stdout);
    freopen_s(&flujo, "CONOUT$", "w", stderr);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    abrirConsolaDeDepuracion();

    printf("Game Engine - Capitulo 8\n\n");

    Registro registro("bin/motor.log");
    registro.escribir(std::string("Motor iniciado (Capitulo 8)."));

    Ventana ventana(hInstance, "Game Engine - Motor de prueba", 1280, 720, nCmdShow);

    registro.escribir(std::string("Ventana creada correctamente."));
    printf("Ventana creada. Cierra la ventana (Alt+F4 o el boton de cerrar) para terminar.\n");

    ventana.establecerTitulo("Game Engine - Titulo actualizado en tiempo real");
    ventana.ejecutarBucleDeMensajes();

    registro.escribir(std::string("Motor cerrado correctamente."));

    return 0;
}
