#pragma once

#include <ctime>

class Temporizador {
private:
	std::clock_t horaInicio;

public:
	// Solo guarda un valor numerico: no adquiere ni libera recursos como Registro.
	// Por eso sus operaciones especiales implicitas son seguras y no necesita
	// aplicar la Regla de los Tres/Cinco.
	Temporizador();

	float segundosTranscurridos() const;
};