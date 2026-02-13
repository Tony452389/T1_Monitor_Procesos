# Proyecto: Monitor de Procesos en C++

## Descripcion General
Aplicación desarrollada en C++ que permite analizar los procesos activos
del sistema, clasificarlos según su consumo de memoria y evaluar el
estado global del sistema mediante distintos criterios de riesgo.

El programa cuenta con dos modos de análisis:

1. Análisis Básico
2. Análisis Estricto

Los resultados se muestran en consola y se registran en un archivo
"Registro_Procesos.txt"

## Autor
- Josue Israel Castro Aguilar - https://github.com/Tony452389

## Instrucciones de compilacion y ejecucion

### Requisitos
Sistema operativo: Windows
IDE: Visual Studio
Librerias utilizadas: 
  - Manipulacion de datos y estructuras:
      #include <vector>
      #include <string>
      #include <utility>
      #include <unordered_map>
      
  - Entrada / Salida:
      #include <iostream>
      #include <fstream>
      #include <ionmanip>
      
  - Tiempo y Fecha:
      #include <chrono>
      #include <ctime>
      
  - Algoritmo
      #include <algorithm>
      
  - Manejo de Errores:
      #include <stdexcept>
      
  - Validacion de Entrada:
      #include <limits>
      
  - Libreria de Windows:
      #include <cstdio>

### Compilacion y Ejecucion
1.- Abrir la solución en Visual Studio
2.- Seleccionar "Recompilar Solucion."
3.- Ejecutar con "Ctrl + F5"

### Entrada Esperada
El programa recibe dos tipos de entrada:

1. Datos internos:
   - Lista de procesos activos del sistema.
   - Cada proceso debe contener:
     + PID válido (entero positivo).
     + Nombre no vacío.
     + Memoria en MB no negativa.

2. Entrada del usuario:
   - Selección del tipo de análisis (1 o 2).
   - Cantidad de procesos a visualizar (entero dentro del rango permitido).

El sistema valida las entradas y maneja errores mediante excepciones.

## Criterios de Clasificación de Procesos Sospechosos

Un proceso es considerado sospechoso si cumple alguno de los siguientes criterios:

- Consumo > 500 MB → MODERADO
- Consumo > 1000 MB → ALTO
- Consumo > 1500 MB → CRITICO
- Nombre > 25 caracteres → BAJO
- Más de 10 instancias → ALTO (modo estricto)
- Más de 50 instancias → CRITICO (modo estricto)

Un proceso puede tener múltiples razones de sospecha,
pero no se duplican entradas por la misma causa.

## Salida Generada

El programa genera:

1. Salida en consola:
   - Tabla ordenada de procesos.
   - Resumen estadístico.
   - Métricas avanzadas (modo estricto).

2. Archivo Registro_Procesos.txt:
   - Fecha y hora del análisis.
   - Lista completa de procesos.
   - Lista de procesos sospechosos.
   - Métricas avanzadas (modo estricto).
   - Detección de duplicados (modo estricto).
   - Distribución de riesgos (modo estricto).
   - Porcentaje de procesos sospechosos (modo estricto).
   - Índice Global de Riesgo (modo estricto).

## Referencias
- ISO/IEC 14882:2017 – Programming Languages — C++
- C++ Reference. https://en.cppreference.com
- Stroustrup, B. (2013). The C++ Programming Language (4th ed.).
- Microsoft Documentation. Windows API – Process Management.
