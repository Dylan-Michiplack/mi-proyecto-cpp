#pragma once
#include "Ruta.h"
#include "Usuario.h"
#include "ListaSimple.h"

// Edgar Kevin Serna Poma - QuickSort: rutas por tiempo
int particionRutas(Ruta** arreglo, int low, int high);
void quickSortRutas(Ruta** arreglo, int low, int high);
void mostrarRutasOrdenadas(ListaSimple<Ruta>& rutas);

// Mathias Raul Grovas Ormachea - Counting Sort: usuarios por anio de nacimiento
void countingSortUsuariosPorAnio(Usuario** arreglo, int n);
void mostrarUsuariosOrdenadosPorAnio(ListaSimple<Usuario>& usuarios);

// Dylan Jean Pierre Ybanez Mejia - Merge Sort: rutas por distancia
void mergeRutasPorDistancia(Ruta** arreglo, int izquierda, int medio, int derecha);
void mergeSortRutasPorDistancia(Ruta** arreglo, int izquierda, int derecha);
void mostrarRutasOrdenadasPorDistancia(ListaSimple<Ruta>& rutas);
