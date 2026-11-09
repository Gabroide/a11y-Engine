// [CAP.9] contexto_opengl.h - Contexto de renderizado OpenGL (RAII)
#pragma once
#include <windows.h>

class ContextoOpenGL {
private:
    HWND hwnd;   // [CAP.9] La ventana sobre la que se dibuja
    HDC hdc;     // [CAP.9] Contexto de dispositivo de esa ventana
    HGLRC hglrc; // [CAP.9] El contexto de renderizado OpenGL en si

public:
    explicit ContextoOpenGL(HWND hwndDestino);
    ~ContextoOpenGL();

    // [CAP.9] Regla de los Cinco: un ContextoOpenGL posee recursos del
    // [CAP.9] sistema (HDC, HGLRC) que no deben compartirse copiando el objeto.
    ContextoOpenGL(const ContextoOpenGL&) = delete;
    ContextoOpenGL& operator=(const ContextoOpenGL&) = delete;

    void intercambiarBuffers();          // [CAP.9] SwapBuffers: ver apartado 9.3
    void establecerVSync(bool activado); // [CAP.9] Carga de extension: ver apartado 9.5
};
