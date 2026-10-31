// [CAP.9] entrada_teclado.cpp
#include "entrada_teclado.h"

bool EntradaTeclado::teclasActuales[256] = {};       // [CAP.9] Inicializadas a "false"
bool EntradaTeclado::teclasFrameAnterior[256] = {};  // [CAP.9]

void EntradaTeclado::actualizarTecla(int codigoTecla, bool presionada) {
    if (codigoTecla >= 0 && codigoTecla < 256) { // [CAP.9] Comprobacion de limites, capitulo 4
        teclasActuales[codigoTecla] = presionada;
    }
}

bool EntradaTeclado::estaPresionada(int codigoTecla) {
    if (codigoTecla < 0 || codigoTecla >= 256) {
        return false;
    }
    return teclasActuales[codigoTecla];
}

bool EntradaTeclado::fuePulsadaEsteFrame(int codigoTecla) {
    if (codigoTecla < 0 || codigoTecla >= 256) {
        return false;
    }
    return teclasActuales[codigoTecla] && !teclasFrameAnterior[codigoTecla];
}

void EntradaTeclado::actualizarFinDeFrame() {
    for (int i = 0; i < 256; i++) {
        teclasFrameAnterior[i] = teclasActuales[i];
    }
}
