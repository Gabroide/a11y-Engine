// src/core/temporizador.cpp
#include "temporizador.h"

Temporizador::Temporizador() : horaInicio(std::clock()) {
}

float Temporizador::segundosTranscurridos() const {
	const std::clock_t ahora = std::clock();
	return static_cast<float>(ahora - horaInicio) /
		static_cast<float>(CLOCKS_PER_SEC);
}