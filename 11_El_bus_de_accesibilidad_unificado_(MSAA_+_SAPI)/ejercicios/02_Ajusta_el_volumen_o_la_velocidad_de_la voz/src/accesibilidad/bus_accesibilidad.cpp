// [CAP.11] bus_accesibilidad.cpp
// [CAP.11] initguid.h DEBE incluirse antes que cualquier cabecera que
// [CAP.11] declare GUIDs (como sapi.h, incluida indirectamente a traves
// [CAP.11] de nuestro propio .h). Ver el apartado 11.5.
#include <initguid.h>
#include "bus_accesibilidad.h"
#include <cstdio>

// [CAP.11] Conversion "rapida" de ASCII a texto ancho para SAPI.
// [CAP.11] AVISO - DEUDA TECNICA DECLARADA: esta conversion solo es
// [CAP.11] correcta para caracteres ASCII (0-127). Todo el texto de
// [CAP.11] accesibilidad del motor, desde el capitulo 3, se ha escrito
// [CAP.11] deliberadamente sin acentos ni caracteres especiales por esta
// [CAP.11] misma razon. En el capitulo 16 sustituiremos esta funcion por
// [CAP.11] una conversion UTF-8 a UTF-16 correcta con MultiByteToWideChar.
static std::wstring conversionRapidaAAncho(const std::string& textoAscii) {
    std::wstring resultado;
    resultado.reserve(textoAscii.size());
    for (char c : textoAscii) {
        resultado.push_back((wchar_t)(unsigned char)c);
    }
    return resultado;
}

BusAccesibilidad::BusAccesibilidad() : voz(nullptr), comInicializado(false) {
    HRESULT resultadoCom = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    comInicializado = SUCCEEDED(resultadoCom);

    HRESULT resultado = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&voz);
    if (FAILED(resultado)) {
        voz = nullptr;
        // [CAP.11] Degradacion elegante: NO llamamos a exit() ni lanzamos
        // [CAP.11] ninguna excepcion. El motor sigue funcionando sin voz;
        // [CAP.11] los anuncios quedaran disponibles igualmente por
        // [CAP.11] consola y por el fichero de registro.
        printf("[BusAccesibilidad] Aviso: SAPI no disponible. Los anuncios solo se registraran por texto.\n");
    } else {
        printf("[BusAccesibilidad] SAPI inicializado correctamente.\n");
    }
}

BusAccesibilidad::~BusAccesibilidad() {
    if (voz != nullptr) {
        voz->Release();
    }
    if (comInicializado) {
        CoUninitialize();
    }
}

void BusAccesibilidad::establecerVelocidad(int velocidad) {
    if (velocidad < -10 || velocidad > 10) {
        printf("[BusAccesibilidad] Error: la velocidad SAPI debe estar entre -10 y 10 (recibido: %d).\n", velocidad);
        return;
    }

    if (voz != nullptr) {
        HRESULT resultado = voz->SetRate(velocidad);
        if (FAILED(resultado)) {
            printf("[BusAccesibilidad] Error al establecer la velocidad SAPI (HRESULT: 0x%08lX).\n",
                static_cast<unsigned long>(resultado));
        }
    }
}

void BusAccesibilidad::anunciar(const std::string& mensaje, Registro& registro) {
    // [CAP.11] El registro y la consola SIEMPRE reciben el mensaje,
    // [CAP.11] exista o no un motor de voz disponible en este equipo.
    printf("[Accesibilidad] %s\n", mensaje.c_str());
    registro.escribir(std::string("[Accesibilidad] ") + mensaje);

    if (voz != nullptr) {
        std::wstring mensajeAncho = conversionRapidaAAncho(mensaje);
        voz->Speak(mensajeAncho.c_str(), SPF_ASYNC | SPF_PURGEBEFORESPEAK, NULL);
    }
}

void BusAccesibilidad::notificarCambioFocoMSAA(HWND hwnd) {
    // [CAP.11] AVISO: esto NO sustituye a una implementacion de IAccessible.
    // [CAP.11] Es una notificacion de bajo nivel que indica a cualquier
    // [CAP.11] observador de eventos de MSAA que "algo ha cambiado el foco"
    // [CAP.11] en esta ventana. Sin un proveedor de IAccessible propio que
    // [CAP.11] responda a WM_GETOBJECT, ninguna herramienta puede consultar
    // [CAP.11] a traves de este evento el nombre o el rol de nuestro
    // [CAP.11] control concreto; ese trabajo queda fuera del alcance de
    // [CAP.11] este curso y se documenta como tarea futura en el epilogo.
    NotifyWinEvent(EVENT_OBJECT_FOCUS, hwnd, OBJID_CLIENT, CHILDID_SELF);
}
