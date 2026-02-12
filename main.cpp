#include <iostream>

#include "procesos.h"
#include "analisis.h"
#include "registro.h"

// Monitor_Procesos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
int main(){
    try {
		auto procesos = obtenerProcesos();
		
		int limite;
		bool entradaValida = false;

		while(!entradaValida) {
			std::cout << "Ingrese el numero de procesos a mostrar (1-" << procesos.size() << "): ";
			std::cin >> limite;
			if (std::cin.fail() || limite < 1 || limite > procesos.size()) {
				std::cin.clear(); // Limpia el estado de error
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora la entrada no válida
				std::cout << "Entrada invalida. Por favor, ingrese un numero entre 1 y " << procesos.size() << ".\n";
			} else {
				entradaValida = true;
			}
		}
		
		analizarBasico(procesos, limite);
		registrarProcesos(procesos, limite);
    }
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
	}
	return 0;
}

