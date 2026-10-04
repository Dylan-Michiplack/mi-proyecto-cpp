#pragma once
#include <string>

//Dylan Jean Pierre Ybanez Mejia

class EstadoRuta {
private:
    std::string nombreRuta;
    int nivelCongestion;
    bool disponible;

public:
    EstadoRuta(std::string ruta = "", int congestion = 0, bool disp = true);

    std::string getNombreRuta() const;
    int getNivelCongestion() const;
    bool estaDisponible() const;
    void setNivelCongestion(int congestion);
    void setDisponible(bool disponible);
};
