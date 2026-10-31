// [CAP.9] contexto_opengl.cpp
#include "contexto_opengl.h"
#include <gl/gl.h>
#include <cstdio>

typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int); // [CAP.9] Ver apartado 9.5

ContextoOpenGL::ContextoOpenGL(HWND hwndDestino) : hwnd(hwndDestino), hdc(nullptr), hglrc(nullptr) {
    hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int formato = ChoosePixelFormat(hdc, &pfd);
    if (formato == 0 || !SetPixelFormat(hdc, formato, &pfd)) {
        printf("[ContextoOpenGL] Error: no se pudo configurar el formato de pixel.\n");
        return;
    }

    hglrc = wglCreateContext(hdc);
    if (hglrc == nullptr) {
        printf("[ContextoOpenGL] Error: no se pudo crear el contexto de renderizado.\n");
        return;
    }

    wglMakeCurrent(hdc, hglrc);
    printf("[ContextoOpenGL] Contexto OpenGL creado: %s\n", (const char*)glGetString(GL_VERSION));
}

ContextoOpenGL::~ContextoOpenGL() {
    if (hglrc != nullptr) {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hglrc);
    }
    if (hdc != nullptr) {
        ReleaseDC(hwnd, hdc);
    }
}

void ContextoOpenGL::intercambiarBuffers() {
    SwapBuffers(hdc);
}

void ContextoOpenGL::establecerVSync(bool activado) {
    static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
        (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

    if (wglSwapIntervalEXT != nullptr) {
        wglSwapIntervalEXT(activado ? 1 : 0);
    } else {
        printf("[ContextoOpenGL] Aviso: la extension de VSync no esta disponible en este equipo.\n");
    }
}
