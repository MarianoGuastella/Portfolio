#include "aed2_SimCity.h"

aed2_SimCity::aed2_SimCity(aed2_Mapa m) : _simcity(m.mapa()) {}

void aed2_SimCity::agregarCasa(Casilla c) {
    _simcity.agregarCasa(c);
}

void aed2_SimCity::agregarComercio(Casilla c) {
    _simcity.agregarComercio(c);
}

void aed2_SimCity::avanzarTurno() {
    _simcity.avanzarTurno();
}

void aed2_SimCity::unir(aed2_SimCity sc) {
    _simcity.unir(sc._simcity);
}

aed2_Mapa aed2_SimCity::mapa() {
    return aed2_Mapa(_simcity.actualizarMapa());
}

set<Casilla> aed2_SimCity::casas() {
    set<Casilla> res;
    Lista<tuple<Casilla, Nivel>> casas = _simcity.actualizarCasas();
    for (int i = 0; i < casas.longitud(); i++) {
        res.insert(get<0>(casas.iesimo(i)));
    }
    return res;
}

set<Casilla> aed2_SimCity::comercios() {
    set<Casilla> res;
    Lista<tuple<Casilla, Nivel>> comercios = _simcity.actualizarComercios();
    for (int i = 0; i < comercios.longitud(); i++) {
        res.insert(get<0>(comercios.iesimo(i)));
    }
    return res;
}

Nat aed2_SimCity::nivel(Casilla c) {
    return _simcity.nivel(c);
}

bool aed2_SimCity::huboConstruccion() const {
    return _simcity.huboConstruccion();
}

Nat aed2_SimCity::popularidad() const {
    return _simcity.popularidad();
}

Nat aed2_SimCity::antiguedad() const {
    return _simcity.antiguedad();
}

SimCity aed2_SimCity::simCity() {
    return _simcity;
}