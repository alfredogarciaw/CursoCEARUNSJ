# CursoCEARUNSJ
Trabajo Curso CEAR UNSJ Oscar y Alfredo 
# Trabajo Final para el Curso "Computación Evolutiva de Alto Rendimiento"

## Alumnos

- Oscar Flores
- Alfredo Garcia

## Introducción

La Computación Evolutiva de Alto Rendimiento representa un campo emergente y dinámico dentro de la ciencia de la computación. La complejidad y demanda de los problemas computacionales actuales requieren técnicas avanzadas, y este curso está diseñado para abordar estos desafíos.

## Descripción del Problema

En este trabajo final, se abordará un problema clásico y bien conocido en el ámbito de la optimización combinatoria, el problema del Viajante de Comercio (TSP). El enfoque de la solución se basará en la utilización de algoritmos genéticos, una técnica bioinspirada que emula el proceso de evolución natural.

## Metodología y Enfoque

El enfoque principal será realizar cambios al abordaje genérico de los algoritmos genéticos, personalizando y mejorando la técnica para el problema específico del TSP. La implementación implicará la utilización de operadores específicos, como Opt2 1*, y la estructura de datos conocida como satellite-list 2*, que se adapta de manera eficiente al problema del viajante.

Se utilizará un operador de cruce basado en EAX *3, altamente especializado para el problema del viajante y conocido por su buen rendimiento y capacidad de exploración.

## Fuentes de Datos y Casos de Prueba

Para validar y probar la eficacia del enfoque propuesto, se utilizarán archivos de casos de prueba disponibles públicamente en formato ".tsp". Específicamente, los archivos de casos de la Universidad de Waterloo serán la fuente principal de datos para la experimentación. Estos archivos, de libre acceso, ofrecen una oportunidad invaluable para evaluar el desempeño del algoritmo en una variedad de escenarios.

- [Universidad de Waterloo](https://www.math.uwaterloo.ca/tsp/data/index.html)
- [TSPLIB95](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/tsp/)
- [Óptimos Globales](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/STSP.html)

## Referencias

1. Guided local search and its application to the traveling salesman problem. Christos Voudouris, Edward P. K. Tsang: Eur. J. Oper. Res. 113(2): 469-499 (1999)
2. Osterman, Colin, Rego, Cesar, Gamboa, Dorabela, 2005. "The Satellite List". DOI: 10.1007/3-211-27389-1_131ER.
3. New EAX crossover for large TSP instances. DOI: 10.1007/11844297_38, ISBN: 978-3-540-38990-3.

## Requisitos

- Visual Studio con soporte para C++/CLR 2019

## Instalación

1. Clonar el repositorio: `git clone https://github.com/alfredogarciaw/CursoCEARUNSJ`
2. Abrir el proyecto en Visual Studio C++ 2019.
3. Agregar extension de visual studio 2019 C++/CLR windows forms

## Uso

El menu "Cargar" sirve para cargar el caso tsp (archivos .tsp euclideanos)
El menu "Evolucionar" permit ejecutar el algoritmo genetico para optimizar el caso tsp.

