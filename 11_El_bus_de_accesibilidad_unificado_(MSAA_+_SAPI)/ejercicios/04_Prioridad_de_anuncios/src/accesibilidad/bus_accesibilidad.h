// [CAP.11] bus_accesibilidad.h - Anuncios de accesibilidad del motor (SAPI + MSAA)
#pragma once
#include <windows.h>
#include <sapi.h>
#include <string>
#include "../core/registro.h"

enum class PrioridadAnuncio {
    NORMAL,
    ALTA
};

class BusAccesibilidad {
private:
    ISpVoice* voz;         // [CAP.11] nullptr si SAPI no esta disponible (degradacion elegante)
    bool comInicializado;  // [CAP.11] Para no llamar a CoUninitialize si CoInitializeEx fallo
    PrioridadAnuncio prioridadEnCurso;

public:
    BusAccesibilidad();
    ~BusAccesibilidad();

    // [CAP.11] Regla de los Cinco: posee un recurso COM que no debe copiarse.
    BusAccesibilidad(const BusAccesibilidad&) = delete;
    BusAccesibilidad& operator=(const BusAccesibilidad&) = delete;

    // [CAP.11] Anuncia un mensaje por voz (si SAPI esta disponible) y lo
    // [CAP.11] registra siempre, independientemente de si se pudo hablar.
    // [CAP.11] NORMAL no interrumpe una voz ALTA que siga hablando; ALTA
    // [CAP.11] purga cualquier anuncio en curso, incluso otro de prioridad ALTA.
    void anunciar(const std::string& mensaje, PrioridadAnuncio prioridad, Registro& registro);

    // [CAP.11] Notificacion MSAA de bajo nivel: ver el aviso del apartado 11.7.
    void notificarCambioFocoMSAA(HWND hwnd);
};
