#include "registro.h"

#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>

void registrarProcesos(const ResultadoAnalisis& resultado) {

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

	archivo << "Fecha :"
			<< std::put_time(&tiempoLocal, "%Y-%m-%d")
			<< "   Hora: "
			<< std::put_time(&tiempoLocal, "%H:%M:%S")
			<< "\n";
	
	archivo << "-----------------------------------------------------------------------\n";

	archivo << "\n\n----------------- Tabla de Procesos del Sistema -----------------\n";
	archivo << "-----------------------------------------------------------------\n";
	archivo << std::left
			<< std::setw(10) << "PID"
			<< std::setw(40) << "Nombre del Proceso"
			<< std::setw(15) << "Memoria (MB)"
			<< "\n";
	archivo << "-----------------------------------------------------------------\n";

	for (const auto& p : resultado.procesosOrdenados) {
		archivo << std::left
				<< std::setw(10) << p.pid
				<< std::setw(40) << p.nombre
				<< std::setw(15) << p.memoriaMB
				<< "\n";
	}

	archivo << "\nTotal de procesos: " << resultado.totalProcesos << "\n";
	archivo << "----------------------------------------------------------------- \n";
	
	archivo << "\n\n------------------- Procesos Sospechosos -------------------\n";
	archivo << "------------------------------------------------------------\n";

	bool sonSospechosos = false;

	for (const auto& s : resultado.sospechosos) {
		if (!s.razon.empty()) {
			sonSospechosos = true;
			const auto& p = s.proceso;

			archivo << "PID: " << p.pid << "\n";
			archivo << "Nombre del Proceso: " << p.nombre << "\n";
			archivo << "Memoria Utilizada: " << p.memoriaMB << " MB\n";
			archivo << "Nivel de Sospecha: " << s.nivel << "\n";
			archivo << "Razon: " << s.razon << "\n";
			archivo << "------------------------------------------------------------\n";
		}
	}

	if (resultado.memoriaTotal > 0) {
		archivo << "\n\n---------------------------- Metricas avanzadas ---------------------------\n";
		archivo << "---------------------------------------------------------------------------\n";
		archivo << "Memoria Total Utilizada: "
				<< resultado.memoriaTotal << " MB\n";

		archivo << "Memoria Promedio por Proceso: "
				<< std::fixed << std::setprecision(2)
				<< resultado.memoriaPromedio << " MB\n";

		archivo << "---------------------------------------------------------------------------\n";
		archivo << "Proceso con Mayor Consumo de Memoria: \n";
		archivo << "PID: "
				<< resultado.procesoMayorMemoria.pid << "\n";
		archivo << "Nombre: "
				<< resultado.procesoMayorMemoria.nombre << "\n";
		archivo << "Memoria Utilizada: "
				<< resultado.procesoMayorMemoria.memoriaMB << " MB\n";

		archivo << "---------------------------------------------------------------------------\n";
		archivo << "Top 5 Procesos por Consumo de Memoria:\n";

		for (const auto& p : resultado.top5Memoria) {
			archivo << std::left
					<< std::setw(10) << p.pid << " - "
					<< std::setw(40) << p.nombre << " - "
					<< std::setw(15) << p.memoriaMB << " MB"
					<< "\n";

		}
		archivo << "---------------------------------------------------------------------------\n";
	}
}