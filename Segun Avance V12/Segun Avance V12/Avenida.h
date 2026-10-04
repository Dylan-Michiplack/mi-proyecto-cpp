#pragma once
#include <string>

//Edgar Kevin Serna Poma

class Avenida {
private:
    std::string nombre;
    std::string distrito;

public:
    Avenida(std::string n = "", std::string d = "");

    std::string getNombre() const;
    std::string getDistrito() const;
};
