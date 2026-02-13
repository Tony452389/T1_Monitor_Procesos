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

		if (p.memoriaMB > 1500) {
			sospechoso.nivel = "CRITICO";
			sospechoso.razon = "Consumo de memoria excesivo.";
			esSospechoso = true;
		}
		else if (p.memoriaMB > 1000) {
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

ResultadoAnalisis analisisEstricto(std::vector<Proceso> procesos) {
	ResultadoAnalisis resultado = analisisBasico(procesos);

	//Calcular memooria total
	resultado.memoriaTotal = 0;

	for (const auto& p : resultado.procesosOrdenados) {
		resultado.memoriaTotal += p.memoriaMB;
	}

	//Calcular memoria promedio
	if (resultado.totalProcesos > 0) {
		resultado.memoriaPromedio = static_cast<double>(resultado.memoriaTotal) / resultado.totalProcesos;
	}

	//Identificar proceso con mayor consumo de memoria
	if (!resultado.procesosOrdenados.empty()) {
		resultado.procesoMayorMemoria = resultado.procesosOrdenados[0];
	}

	//Obtener top 5 procesos por consumo de memoria
	int limite = std::min(5, resultado.totalProcesos);
	for (int i = 0; i < limite; ++i) {
		resultado.top5Memoria.push_back(resultado.procesosOrdenados[i]);
	}

	return resultado;
}