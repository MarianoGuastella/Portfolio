#include "aed2_Mapa.h"

aed2_Mapa::aed2_Mapa() : _mapa(Mapa()) {}

aed2_Mapa::aed2_Mapa(Mapa m) : _mapa(m) {}

void aed2_Mapa::agregarRio(Direccion d, int p) {
    _mapa.agregarRio(d, p);
}

bool aed2_Mapa::hayRio(Casilla c) const {
    return _mapa.hayRio(c);
}

void aed2_Mapa::unirMapa(aed2_Mapa m2) {
    _mapa.unirMapa(m2._mapa);
}

Mapa aed2_Mapa::mapa() {
    return _mapa;
}
