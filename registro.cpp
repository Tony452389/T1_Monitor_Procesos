#include "registro.h"

#include <fstream>
#include <iostream>

void registrarProcesos(const std::vector<Proceso>& procesos) {
	std::ofstream archivo("registro_procesos.txt");

	if (!archivo.is_open()) {
		std::cerr << "No se pudo abrir el archivo de registro.\n";
		return;
	}

	int altoConsumo = 0;

	for (const auto& p : procesos) {
		if(p.memoriaMB > 500) {
			altoConsumo++;
		}
	}

	archivo << "Registro de Procesos del Sistema\n";
	archivo << "--------------------------------\n";
	archivo << "\nTotal de procesos: " << procesos.size() << "\n";
	archivo << "Procesos con alto consumo (>500 MB): " << altoConsumo << "\n";

	archivo.close();
}