#include "RutaCombinada.h"

using namespace std;

RutaCombinada::RutaCombinada(string n) : nombre(n) {}

RutaCombinada::RutaCombinada(const RutaCombinada& otra) : nombre(otra.nombre) {
    otra.tramos.recorrerAdelante([this](const Ruta& r) {
        tramos.insertarFinal(r);
    });
}

RutaCombinada& RutaCombinada::operator=(const RutaCombinada& otra) {
    if (this != &otra) {
        nombre = otra.nombre;
        tramos.vaciar();
        otra.tramos.recorrerAdelante([this](const Ruta& r) {
            tramos.insertarFinal(r);
        });
    }
    return *this;
}

string RutaCombinada::getNombre() const { return nombre; }
int RutaCombinada::getCantidadTramos() const { return tramos.longitud(); }

string RutaCombinada::getOrigen() const {
    NodoDoble<Ruta>* primero = tramos.getCabeza();
    return (primero != nullptr) ? primero->dato.getOrigen() : "";
}

string RutaCombinada::getDestino() const {
    NodoDoble<Ruta>* ultimo = tramos.getCola();
    return (ultimo != nullptr) ? ultimo->dato.getDestino() : "";
}

double RutaCombinada::getDistanciaTotal() const {
    double total = 0.0;
    tramos.recorrerAdelante([&total](const Ruta& r) {
        total += r.getDistanciaKm();
    });
    return total;
}

int RutaCombinada::getTiempoTotal() const {
    int total = 0;
    tramos.recorrerAdelante([&total](const Ruta& r) {
        total += r.getTiempoMin();
    });
    return total;
}

bool RutaCombinada::agregarTramo(const Ruta& ruta) {
    NodoDoble<Ruta>* ultimo = tramos.getCola();
    if (ultimo != nullptr && ultimo->dato.getDestino() != ruta.getOrigen()) {
        return false;
    }
    tramos.insertarFinal(ruta);
    return true;
}

const ListaDoble<Ruta>& RutaCombinada::getTramos() const { return tramos; }
