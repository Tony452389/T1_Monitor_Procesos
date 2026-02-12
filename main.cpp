#include "procesos.h"
#include "analisis.h"
#include "registro.h"

#include <iostream>
#include <iomanip>
#include <limits>

// Monitor_Procesos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
int main(){
    try {
		auto procesos = obtenerProcesos();
		
		//-------------------------- Menu ------------------------------------------------
		int opcion;
		bool opcionValida = false;

		while (!opcionValida) {
			std::cout << "Seleccione el tipo de analisis que desea realizar: \n";
			std::cout << "1. Analisis Basico\n";
			std::cout << "2. Analisis Estricto\n";

			std::cin >> opcion;

			if (std::cin.fail() || (opcion != 1 && opcion != 2)) {
				std::cin.clear(); // Limpia el estado de error
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora la entrada no válida
				std::cout << "Opcion invalida. Por favor, ingrese 1 o 2.\n";
			} else {
				opcionValida = true;
			}
		}

		if(opcionValida){
			system("cls"); // Limpiar la pantalla
		}

		//------------------------- Analisis Basico ------------------------------------------------
		if (opcion == 1) {
			ResultadoAnalisis resultado = analisisBasico(procesos);
			registrarProcesos(resultado);
			
			//Solicitar limite de procesos a mostrar
			int limite;
			bool entradaValida = false;

			while (!entradaValida) {
				std::cout << "Ingrese el numero de procesos a mostrar (1-" << resultado.totalProcesos << "): ";
				std::cin >> limite;

				if (std::cin.fail() || limite < 1 || limite > resultado.totalProcesos) {
					std::cin.clear(); // Limpia el estado de error
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora la entrada no válida
					std::cout << "Entrada invalida. Por favor, ingrese un numero entre 1 y " << resultado.totalProcesos << ".\n";
				}
				else {
					entradaValida = true;
				}
			}

			if(entradaValida){
				system("cls"); // Limpiar la pantalla
			}

			std::cout << "\n------------------ Analisis Basico de Procesos ------------------\n";

			std::cout << std::left
				<< std::setw(10) << "PID"
				<< std::setw(40) << "Nombre del Proceso"
				<< std::setw(15) << "Memoria (MB)"
				<< "\n";

			std::cout << "-----------------------------------------------------------------\n";

			for (int i = 0; i < limite; ++i) {
				const auto& p = resultado.procesosOrdenados[i];

				std::cout << std::left
					<< std::setw(10) << p.pid
					<< std::setw(40) << p.nombre
					<< std::setw(15) << p.memoriaMB
					<< "\n";
			}

			std::cout << "\nTotal de Procesos "
				<< resultado.totalProcesos << "\n";
			std::cout << "-----------------------------------------------------------------\n\n";

			std::cout << "Procesos con alto consumo de memoria (>500 MB): "
				<< resultado.altoConsumo << "\n";
		}
		//------------------------- Analisis Estricto ------------------------------------------------
		else if (opcion == 2) {
			std::cout << "Analisis Estricto no implementado en esta version.\n";
		}
				
    }
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
	}

	return 0;
}

