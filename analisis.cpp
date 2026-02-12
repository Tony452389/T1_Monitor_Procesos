#include "analisis.h"

#include <iostream>
#include <algorithm>

ResultadoAnalisis analisisBasico(std::vector<Proceso> procesos) {
	
	ResultadoAnalisis resultado;
	
	// Ordenar por memoria descendente
	std::sort(procesos.begin(), procesos.end(), 
		[](const Proceso& a, const Proceso& b) {
		return a.memoriaMB > b.memoriaMB;
		});
	
	resultado.procesosOrdenados = procesos;
	resultado.totalProcesos = procesos.size();
	resultado.altoConsumo = 0;
	
	for (const auto& p : procesos) {
		if (p.memoriaMB > 500) { // Umbral de 500 MB
			resultado.altoConsumo++;
		}

		ProcesoSospechoso sospechoso;
		bool esSospechoso = false;

		if (p.memoriaMB > 1000) {
			sospechoso.nivel = "ALTO";
			sospechoso.razon = "Consumo de memoria demasiado alto.";
			esSospechoso = true;
		}
		else if (p.memoriaMB > 500) {
			sospechoso.nivel = "MEDIO";
			sospechoso.razon = "Consumo de memoria elevado.";
			esSospechoso = true;
		}
		else if (p.nombre.length() > 25) {
			sospechoso.nivel = "BAJO";
			sospechoso.razon = "Nombre del proceso inusualmente largo.";
			esSospechoso = true;
		}

		if(esSospechoso) {
			sospechoso.proceso = p;
			resultado.sospechosos.push_back(sospechoso);
		}
	}
	return resultado;
}