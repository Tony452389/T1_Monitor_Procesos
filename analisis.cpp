#include "analisis.h"

#include <iostream>
#include <iomanip>
#include <algorithm>

void analizarBasico(std::vector<Proceso> procesos, int limite) {
	//Ordenar por memoria descendente
	std::sort(procesos.begin(), procesos.end(), 
		[](const Proceso& a, const Proceso& b) {
		return a.memoriaMB > b.memoriaMB;
		});
	
	std::cout << "\n------------------ Analisis Basico de Procesos ------------------\n";
					
	std::cout << std::left
		<< std::setw(10) << "PID"
		<< std::setw(40) << "Nombre del Proceso"
		<< std::setw(15) << "Memoria (MB)"
		<< "\n";
	std::cout << "-----------------------------------------------------------------\n";
	
	int mostrados = 0;
	int altoConsumo = 0;

	for (const auto& p : procesos) {
		if (mostrados < limite) {
			std::cout << std::left
				<< std::setw(10) << p.pid
				<< std::setw(40) << p.nombre
				<< std::setw(15) << p.memoriaMB
				<< "\n";
			mostrados++;
		}
		if (p.memoriaMB > 500) { // Umbral de 500 MB
			altoConsumo++;
		}
	}

	std::cout << "\nMostrando los " << limite 
			  << " procesos con mayor consumo de memoria.\n";

	std::cout << "\n-------------------- Resumen --------------------\n";
	std::cout << "Total de procesos: " << procesos.size() << "\n";
	std::cout << "Procesos con alto consumo de memoria (>500 MB): " << altoConsumo << "\n";
}