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
	archivo << "Fecha y Hora: "
		<< std::put_time(&tiempoLocal, "%Y-%m-%d %H:%M:%S") 
		<< "\n\n";
	
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
	archivo << "-----------------------------------------------------------------\n";
	archivo << "\n-----------------------------------------------------------------\n";
	archivo << "PROCESOS SOSPECHOSOS:\n";
	
	bool sonSospechosos = false;
	
	for (const auto& s : resultado.sospechosos) {
		if (!s.razon.empty()) {
			sonSospechosos = true;
			const auto& p = s.proceso;
			archivo << "\n-------------------------------------------------------\n";
			archivo << "PID: " << p.pid << "\n";
			archivo << "Nombre del Proceso: " << p.nombre << "\n";
			archivo << "Memoria Utilizada: " << p.memoriaMB << " MB\n";
			archivo << "Nivel de Sospecha: " << s.nivel << "\n";
			archivo << "Razon: " << s.razon << "\n";
		}
	}

}