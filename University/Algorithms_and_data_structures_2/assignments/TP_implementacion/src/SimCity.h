#ifndef SIMCITY_H
#define SIMCITY_H

#include "Mapa.h"
#include "Lista.h"
#include "Tipos.h"
#include <set>
#include <tuple>
#include <vector>

using namespace std;

using Nivel = int;

class SimCity{
public:
    explicit SimCity(Mapa m);

    void agregarCasa(Casilla c);

    void agregarComercio(Casilla c);

    void avanzarTurno();

    void unir (SimCity s);

    Mapa actualizarMapa();

    Lista<tuple<Casilla, Nivel>> actualizarCasas();

    Lista<tuple<Casilla, Nivel>> actualizarComercios();

    int nivel( Casilla c);

    bool huboConstruccion() const;

    int popularidad() const;

    int antiguedad() const;

    Lista<tuple<Casilla, Nivel>> construcciones();

    bool hayConstruccion(Casilla c);

    bool sePuedeConstruir(Casilla c);

    bool esCasillaDeMaximoNivel(Casilla c);

    int maximoNivel() const;

    int darNivelAComercio(Casilla c);

    int distanciaManhattan(Casilla x, Casilla y);
private:

    Mapa _mapa;
    Lista<tuple<Casilla,Nivel>> _casas;
    Lista<tuple<Casilla,Nivel>> _comercios;
    int _turno;
    int _popularidad;
    bool _huboConstruccion;
    vector<SimCity> _uniones;

};

#endif
