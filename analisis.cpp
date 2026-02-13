#include "analisis.h"

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>

// Función para verificar si un proceso sospechoso ya ha sido registrado con la misma razón
bool yaExisteSospechoso(const std::vector<ProcesoSospechoso>& lista, int pid, const std::string& razon) {
	for (const auto& s : lista) {
		if (s.proceso.pid == pid && s.razon == razon) {
			return true;
		}
	}
	return false;
}

ResultadoAnalisis analisisBasico(std::vector<Proceso> procesos) {
	
	//Proteccion contra entradas vacias
	if (procesos.empty()) {
		throw std::runtime_error("No se encontraron procesos para analizar.");
	}

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
		//Proteccion contra entradas con memoria negativa
		if (p.memoriaMB < 0) {
			throw std::runtime_error("Proceso con memoria negativa detectado. PID: " + std::to_string(p.pid));
		}
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
			sospechoso.nivel = "MODERADO";
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
			if (!yaExisteSospechoso(resultado.sospechosos, sospechoso.proceso.pid, sospechoso.razon)) {
				resultado.sospechosos.push_back(sospechoso);
			}
		}
	}
	return resultado;
}

ResultadoAnalisis analisisEstricto(std::vector<Proceso> procesos) {
	ResultadoAnalisis resultado = analisisBasico(procesos);

	//Calcular memoria total
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

	std::unordered_map<std::string, int> contadorNombres;
	for (const auto& p : resultado.procesosOrdenados) {
		contadorNombres[p.nombre]++;
	}

	//Definir umbral para considerar un proceso como duplicado (3 o más procesos con el mismo nombre)
	int umbralDuplicados = 3;

	for (const auto& par : contadorNombres) {
		if (par.second >= umbralDuplicados) {
			resultado.procesosDuplicados.emplace_back(par);
		}
	}

	//Definir un proceso duplicado como sospechoso
	for (const auto& par : contadorNombres) {
		std::string nivel;
		std::string razon;

		if (par.second >= 50) {
			nivel = "CRITICO";
			razon = "Cantidad excesiva de procesos con el mismo nombre. (" + std::to_string(par.second) + " ocurrencias)";
		}
		else if (par.second >= 10) {
			nivel = "ALTA";
			razon = "Demasiados procesos con el mismo nombre. (" + std::to_string(par.second) + " ocurrencias)";
		}

		if (!nivel.empty()) {
			//Busca una instancia del proceso para agregarlo a la lista de sospechosos
			for (const auto& p : resultado.procesosOrdenados) {
				if(p.nombre == par.first) {
					ProcesoSospechoso sospechoso;
					
					sospechoso.proceso = p;
					sospechoso.nivel = nivel;
					sospechoso.razon = razon;
					
					if (!yaExisteSospechoso(resultado.sospechosos, sospechoso.proceso.pid, sospechoso.razon)) {
						resultado.sospechosos.push_back(sospechoso);
					}

					break;
				}
			}	
		}
	}

	//Calcular distriubucion de riesgos
	for (const auto& s : resultado.sospechosos) {
		if (s.nivel == "CRITICO") {
			resultado.listaCriticos.push_back(s.proceso.nombre);
		}
		else if (s.nivel == "ALTO") {
			resultado.listaAltos.push_back(s.proceso.nombre);
		}
		else if (s.nivel == "MODERADO") {
			resultado.listaModerados.push_back(s.proceso.nombre);
		}
		else if (s.nivel == "BAJO") {
			resultado.listaBajos.push_back(s.proceso.nombre);
		}
	}

	//Calcular porcentaje de procesos sospechosos
	if (resultado.totalProcesos > 0) {
		resultado.porcentajeSospechosos = (resultado.sospechosos.size() * 100.0) / resultado.totalProcesos;
	}

	//Calcular indice global de riesgo
	if(!resultado.listaCriticos.empty() || resultado.porcentajeSospechosos > 20.0) {
		resultado.indiceGlobalRiesgo = "CRITICO";
	}
	else if (!resultado.listaAltos.size() > 3 || resultado.porcentajeSospechosos > 10.0) {
		resultado.indiceGlobalRiesgo = "ALTO";
	}
	else if (!resultado.listaModerados.size() > 5 || resultado.porcentajeSospechosos > 5.0) {
		resultado.indiceGlobalRiesgo = "MODERADO";
	}
	else {
		resultado.indiceGlobalRiesgo = "BAJO";
	}

	return resultado;
}