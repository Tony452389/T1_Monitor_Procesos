#pragma once

#include "procesos.h"

#include <vector>
#include <string>
#include <utility>

struct ProcesoSospechoso {
	Proceso proceso;
	std::string nivel;
	std::string razon;
	
};

struct ResultadoAnalisis {
	std::vector<Proceso> procesosOrdenados;
	std::vector<ProcesoSospechoso> sospechosos;
	
	int totalProcesos = 0;
	int altoConsumo = 0;

	//------------ Metricas para el analisis estricto ----------------
	Proceso procesoMayorMemoria;
	std::vector<Proceso> top5Memoria;
	std::vector<std::pair<std::string, int >> procesosDuplicados;
	
	int memoriaTotal = 0;
	double memoriaPromedio = 0.0;
	
	// ----------------- Distribucion de Riesgos ----------------
	std::vector<std::string> listaCriticos;
	std::vector<std::string> listaAltos;
	std::vector<std::string> listaModerados;
	std::vector<std::string> listaBajos;

	std::string indiceGlobalRiesgo;
	double porcentajeSospechosos = 0.0;
};

ResultadoAnalisis analisisBasico(std::vector<Proceso> procesos);

ResultadoAnalisis analisisEstricto(std::vector<Proceso> procesos);

