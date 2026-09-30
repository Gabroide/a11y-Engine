// Prueba aislada de una fuga de memoria. Este fichero no forma parte del build.bat.
#include <array>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

constexpr std::size_t TAMANO_BLOQUE = 256 * 1024;
constexpr int NUMERO_DE_REPETICIONES = 1000;

struct Bloque {
	std::array<unsigned char, TAMANO_BLOQUE> datos;
};

void reservarConFuga() {
	Bloque* bloque = new Bloque();
	std::memset(bloque->datos.data(), 0xA5, bloque->datos.size());
	// Fuga intencionada: falta delete bloque.
}

void reservarCorregido() {
	std::unique_ptr<Bloque> bloque = std::make_unique<Bloque>();
	std::memset(bloque->datos.data(), 0xA5, bloque->datos.size());
}

int main(int argc, char* argv[]) {
	bool ejecutarFuga = argc > 1 && std::string(argv[1]) == "fuga";
	printf("Modo: %s\n", ejecutarFuga ? "fuga" : "corregida");
	printf("Revisa la memoria del proceso en el Administrador de tareas.\n");

	for (int i = 0; i < NUMERO_DE_REPETICIONES; i++) {
		if (ejecutarFuga) {
			reservarConFuga();
		} else {
			reservarCorregido();
		}

		if ((i + 1) % 100 == 0) {
			printf("Repeticiones: %d/%d\n", i + 1, NUMERO_DE_REPETICIONES);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	printf("Prueba terminada.\n");
	return 0;
}
