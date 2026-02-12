#pragma once

#include <string>
#include <vector>

struct Proceso {
	int pid;
	std::string nombre;
	int memoriaMB;

};

std::vector<Proceso> obtenerProcesos();