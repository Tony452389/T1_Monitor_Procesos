#include "registro.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>

void registrarProcesos(std::vector<Proceso> procesos, int limite) {
	std::ofstream archivo("Registro_Procesos.txt");

	if (!archivo.is_open()) {
		return;
	}

	//Mostrar fecha y hora actual
	auto ahora = std::chrono::system_clock::now();
	std::time_t tiempo = std::chrono::system_clock::to_time_t(ahora);

	std::tm tiempoLocal;
	localtime_s(&tiempoLocal, &tiempo);

	archivo << "\n\n--------------- Analisis Basico de Procesos del Sistema ---------------\n";
	archivo << "Fecha y Hora: "
		<< std::put_time(&tiempoLocal, "%Y-%m-%d %H:%M:%S") 
		<< "\n\n";

	//Ordenar por memoria descendente
	std::sort(procesos.begin(), procesos.end(), 
		[](const Proceso& a, const Proceso& b) {
			return a.memoriaMB > b.memoriaMB;
		});

	archivo << "-----------------------------------------------------------------\n"; 
	archivo << std::left
			<< std::setw(10) << "PID"
			<< std::setw(40) << "Nombre del Proceso"
			<< std::setw(15) << "Memoria (MB)"
			<< "\n";
	archivo << "-----------------------------------------------------------------\n";

	for (const auto& p : procesos) {
		archivo << std::left
				<< std::setw(10) << p.pid
				<< std::setw(40) << p.nombre
				<< std::setw(15) << p.memoriaMB
				<< "\n";
	}

	archivo << "\nTotal de procesos: " << procesos.size() << "\n";
	archivo << "-----------------------------------------------------------------\n";

	archivo << "\n-----------------------------------------------------------------\n";
	archivo << "PROCESOS SOSPECHOSOS:\n";

	bool sonSospechosos = false;
	for(const auto& p : procesos) {
		std::string razon;
		std::string nivel;
		
		if (p.memoriaMB > 1000) {
			razon = "Consumo de memoria demasiado alto";
			nivel = "ALTO";
		}
		else if (p.memoriaMB > 500) {
			razon = "Consumo de memoria elevado";
			nivel = "MEDIO";
		}
		else if (p.nombre.length() > 25) {
			razon = "Nombre de proceso inusualmente largo";
			nivel = "BAJO";
		}

		if (!razon.empty()) {
			sonSospechosos = true;

			archivo << "\n-------------------------------------------------------\n";
			archivo << "PID: " << p.pid << "\n";
			archivo << "Nombre del Proceso: " << p.nombre << "\n";
			archivo << "Memoria Utilizada: " << p.memoriaMB << " MB\n";
			archivo << "Nivel de Sospecha: " << nivel << "\n"; 
			archivo << "Razon: " << razon << "\n"; 
			archivo << "-------------------------------------------------------\n\n";
		}
	}

	if (!sonSospechosos) {
		archivo << "No se encontraron procesos sospechosos basados en los criterios definidos.\n";
	}

	archivo.close();
}