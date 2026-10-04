#pragma once
#include <string>
#include "Sede.h"
#include "EstadoRuta.h"
#include "TramoRuta.h"

// Edgar Kevin Serna Poma


class Ruta {
private:
    std::string nombre;
    Sede origen;                
    Sede destino;               
    EstadoRuta estado;         
    TramoRuta tramoPrincipal;   
    double distanciaKm;
    int tiempoMin;

public:
    Ruta(std::string n = "", std::string o = "", std::string d = "",
         double distancia = 0.0, int tiempo = 0);
    Ruta(std::string n, const Sede& o, const Sede& d,
         double distancia, int tiempo, const EstadoRuta& e,
         const TramoRuta& tramo);

    std::string getNombre() const;
    std::string getOrigen() const;
    std::string getDestino() const;
    double getDistanciaKm() const;
    int getTiempoMin() const;

    const Sede& getSedeOrigen() const;
    const Sede& getSedeDestino() const;
    const EstadoRuta& getEstado() const;
    const TramoRuta& getTramoPrincipal() const;

    void mostrarInfo() const;
};
