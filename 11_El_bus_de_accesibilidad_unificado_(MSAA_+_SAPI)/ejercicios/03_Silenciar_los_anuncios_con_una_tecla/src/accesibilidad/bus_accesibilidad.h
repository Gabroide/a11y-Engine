// [CAP.11] bus_accesibilidad.h - Anuncios de accesibilidad del motor (SAPI + MSAA)
#pragma once
#include <windows.h>
#include <sapi.h>
#include <string>
#include "../core/registro.h"

class BusAccesibilidad {
private:
    ISpVoice* voz;         // [CAP.11] nullptr si SAPI no esta disponible (degradacion elegante)
    bool comInicializado;  // [CAP.11] Para no llamar a CoUninitialize si CoInitializeEx fallo
    bool silenciado;

public:
    BusAccesibilidad();
    ~BusAccesibilidad();

    // [CAP.11] Regla de los Cinco: posee un recurso COM que no debe copiarse.
    BusAccesibilidad(const BusAccesibilidad&) = delete;
    BusAccesibilidad& operator=(const BusAccesibilidad&) = delete;

    // [CAP.11] Anuncia un mensaje por voz (si SAPI esta disponible) y lo
    // [CAP.11] registra siempre, independientemente de si se pudo hablar.
    void anunciar(const std::string& mensaje, Registro& registro);

    void alternarSilencio();

    // [CAP.11] Notificacion MSAA de bajo nivel: ver el aviso del apartado 11.7.
    void notificarCambioFocoMSAA(HWND hwnd);
};
