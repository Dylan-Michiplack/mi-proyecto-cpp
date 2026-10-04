#pragma once
#include <string>
#include "ListaDoble.h"
#include "Ruta.h"

// Una ruta combinada esta formada por dos o mas tramos Ruta consecutivos.
// La ListaDoble permite recorrer el trayecto hacia adelante y hacia atras.
class RutaCombinada {
private:
    std::string nombre;
    ListaDoble<Ruta> tramos;

public:
    RutaCombinada(std::string n = "");
    RutaCombinada(const RutaCombinada& otra);
    RutaCombinada& operator=(const RutaCombinada& otra);

    std::string getNombre() const;
    int getCantidadTramos() const;
    std::string getOrigen() const;
    std::string getDestino() const;
    double getDistanciaTotal() const;
    int getTiempoTotal() const;

    bool agregarTramo(const Ruta& ruta);
    const ListaDoble<Ruta>& getTramos() const;
};
