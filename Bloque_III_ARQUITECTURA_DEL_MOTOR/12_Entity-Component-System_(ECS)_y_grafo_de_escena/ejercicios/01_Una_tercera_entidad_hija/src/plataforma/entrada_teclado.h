// [CAP.9] entrada_teclado.h - Estado del teclado, accesible desde todo el motor
#pragma once

class EntradaTeclado {
private:
    // [CAP.9] "static": un unico estado de teclado compartido por todo
    // [CAP.9] el motor, sin necesidad de pasar un objeto de un lado a
    // [CAP.9] otro. 256 posiciones: el maximo de codigos de tecla virtuales
    // [CAP.9] que define la Win32 API.
    static bool teclasActuales[256];
    static bool teclasFrameAnterior[256];

public:
    // [CAP.9] Llamado desde el WindowProc de Ventana en cada WM_KEYDOWN/WM_KEYUP.
    static void actualizarTecla(int codigoTecla, bool presionada);

    // [CAP.9] true mientras la tecla permanezca pulsada (util para movimiento continuo).
    static bool estaPresionada(int codigoTecla);

    // [CAP.9] true SOLO en el fotograma en que la tecla pasa de no pulsada
    // [CAP.9] a pulsada (util para acciones puntuales: confirmar, cerrar un menu...).
    static bool fuePulsadaEsteFrame(int codigoTecla);

    // [CAP.9] Debe llamarse una vez al final de cada fotograma del game loop.
    static void actualizarFinDeFrame();
};
