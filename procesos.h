#pragma once

#include <string>
#include <vector>

struct Proceso {
	int pid = 0;
	int memoriaMB = 0; 
	
	std::string nombre;
};

std::vector<Proceso> obtenerProcesos();