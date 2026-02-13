#pragma once

#include "procesos.h"

#include <vector>
#include <string>

struct ProcesoSospechoso {
	Proceso proceso;
	std::string nivel;
	std::string razon;
	
};

struct ResultadoAnalisis {
	std::vector<Proceso> procesosOrdenados;
	std::vector<ProcesoSospechoso> sospechosos;
	
	int totalProcesos;
	int altoConsumo;

	//------------ Metricas para el analisis estricto ----------------
	Proceso procesoMayorMemoria;
	std::vector<Proceso> top5Memoria; 
	
	int memoriaTotal = 0;
	double memoriaPromedio = 0.0;
	

};

ResultadoAnalisis analisisBasico(std::vector<Proceso> procesos);

ResultadoAnalisis analisisEstricto(std::vector<Proceso> procesos);

