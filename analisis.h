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
};

ResultadoAnalisis analisisBasico(std::vector<Proceso> procesos);

