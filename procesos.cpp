#include "procesos.h"

#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <algorithm>

std::vector<Proceso> obtenerProcesos() {
	std::vector<Proceso> lista;

	FILE* pipe = _popen("tasklist /FO CSV /NH", "r");

	if (!pipe) {
		throw std::runtime_error("No se pudo ejecutar el comando tasklist.");
	}

	char buffer[512];

	while (fgets(buffer, sizeof(buffer), pipe)) {
		std::string linea(buffer);
		std::stringstream ss(linea);
		std::string campo;
		Proceso p;

		//Nombre del proceso
		std::getline(ss, campo, ',');
		p.nombre = campo.substr(1, campo.size() - 2);

		//PID
		std::getline(ss, campo, ',');
		p.pid = std::stoi(campo.substr(1, campo.size() - 2));

		//Sesion (ignorar)
		std::getline(ss, campo, ',');
		std::getline(ss, campo, ',');

		//Uso de memoria
		std::getline(ss, campo, ',');
		campo = campo.substr(1, campo.size() - 2);

		//Linpiar el texto
		campo.erase(remove(campo.begin(), campo.end(), 'K'), campo.end());
		campo.erase(remove(campo.begin(), campo.end(), ' '), campo.end());
		campo.erase(remove(campo.begin(), campo.end(), ','), campo.end());

		//validacion antes de conversion
		if (campo.empty() || !isdigit(campo[0])) {
			p.memoriaMB = 0;
		}
		else {
			p.memoriaMB = std::stoi(campo) / 1024; // Convertir KB a MB

			lista.push_back(p);
		}
	
	}

	_pclose(pipe);
	return lista;
}