#ifndef MAPA_H
#define MAPA_H

#include "Lista.h"
#include <string>
#include "Tipos.h"

using namespace std;

class Mapa {
public:
    Mapa();

    void agregarRio(Direccion d, Posicion p);

    bool hayRio(Casilla c) const;

    void unirMapa(const Mapa& m);

private:
    Lista<int> _horizontales;
    Lista<int> _verticales;
};

#endif
