#include <iostream>

#include "procesos.h"
#include "analisis.h"
#include "registro.h"

// Monitor_Procesos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
int main(){
    try {
		auto procesos = obtenerProcesos();
		
		std::cout << "Procesos encontrados: " 
				  << procesos.size() << "\n";

		analizarProcesos(procesos);
		
    }
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
	}
	return 0;
}

