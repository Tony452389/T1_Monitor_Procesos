#include "procesos.h"

#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

std::vector<Proceso> obtenerProcesos() {
	std::vector<Proceso> lista;

	FILE* pipe = _popen("tasklist /FO CSV /NH", "r");

	if (!pipe) {
		throw std::runtime_error("No se pudo ejecutar el comando tasklist.");
	}

	char buffer[512];
	
	while (fgets(buffer, sizeof(buffer), pipe)) {
		std::string linea(buffer);

		std::vector<std::string> campos;
		std::string campo;
		bool dentroComillas = false;
		for (char c : linea) {
			if (c == '"') {
				dentroComillas = !dentroComillas;
				continue;
			}

			if (c == ',' && !dentroComillas) {
				campos.push_back(campo);
				campo.clear();
			}
			else {
				campo += c;
			}
		}
		
		if (!campo.empty()) {
			campos.push_back(campo);
		}

		if (campos.size() < 5) {
			continue; // Salta líneas mal formateadas
		}

		Proceso p;

		p.nombre = campos[0];
		p.pid = std::stoi(campos[1]);

		std::string memoria = campos[4];

		/*
		Impresion de depuración para verificar el formato del campo de memoria
		std::cout << "Memoria original: ['" << memoria << "] \n";
		*/

		std::string soloNumeros;

		// Extraer solo los dígitos del campo de memoria
		for (char c : memoria) {
			if (std::isdigit(static_cast<unsigned char>(c))) {
				soloNumeros += c; // Solo agregar dígitos
			}
		
		}

		try {
			if (!soloNumeros.empty()) {
				p.memoriaMB = std::stoi(soloNumeros) / 1024; // Convertir KB a MB
			}
			else {
				p.memoriaMB = 0; // Si no hay números, asignar 0
			}
		}
		catch (const std::exception& ex) {
			p.memoriaMB = 0; // Si no se puede convertir, asignar 0
		}

		lista.push_back(p);

	}
	_pclose(pipe);
	return lista;
}