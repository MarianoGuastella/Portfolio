#ifndef AED2_SIMCITY_H
#define AED2_SIMCITY_H

#include <iostream>
#include <set>
#include "aed2_Mapa.h"
#include "SimCity.h"


using namespace std;

class aed2_SimCity {
public:

    // Generadores:

    explicit aed2_SimCity(aed2_Mapa m);

    // Precondicion: Se puede construir en la Casilla c
    void agregarCasa(Casilla c);

    // Precondicion: Se puede construir en la Casilla c
    void agregarComercio(Casilla c);

    // Precondicion: Hubo construccion en el turno actual
    void avanzarTurno();

    // Precondicion: No se solapan las construcciones con los rios
    //  ni las construcciones de nivel maximo de ambas partidas
    void unir(aed2_SimCity sc);

    // Observadores:

    aed2_Mapa mapa();

    set<Casilla> casas();

    set<Casilla> comercios();

    // Precondicion: Hay construccion en la Casilla p
    Nat nivel(Casilla c);

    bool huboConstruccion() const;

    Nat popularidad() const;

    Nat antiguedad() const;

    // Conversiones
    
    // Esta función sirve para convertir del SimCity de la cátedra al SimCity
    // implementado por ustedes
    SimCity simCity();

private:
    SimCity _simcity;
};

#endif // AED2_SIMCITY_H
