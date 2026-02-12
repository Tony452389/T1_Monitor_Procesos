#include "analisis.h"

#include <iostream>

void analizarProcesos(const std::vector<Proceso>& procesos) {
	int total = procesos.size();
	int altoConsumo = 0;

	for (const auto& p : procesos) {
		if (p.memoriaMB > 500) { // Umbral de 500 MB
			altoConsumo++;
		}
	}

	std::cout << "\n----- Analisis de Procesos -----\n";
	std::cout << "Total de procesos: " << total << std::endl;
	std::cout << "Procesos con alto consumo de memoria (>500 MB): " << altoConsumo << std::endl;
}