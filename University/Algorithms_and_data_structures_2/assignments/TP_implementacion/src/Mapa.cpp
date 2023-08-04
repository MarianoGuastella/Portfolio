#include "Mapa.h"

Mapa::Mapa() : _horizontales(Lista<int>()), _verticales(Lista<int>()) {}

void Mapa::agregarRio(Direccion d, Posicion p){
    if(d == Vertical){
        _verticales.agregarAtras(p);
    } else {
        _horizontales.agregarAtras(p);
    }
}

bool Mapa::hayRio(Casilla c) const {
    return _horizontales.pertenece(c.first) || _verticales.pertenece(c.second);
}

void Mapa::unirMapa(const Mapa& m){
    for ( int i = 0; i < m._verticales.longitud(); i++){
        if( !_verticales.pertenece(m._verticales.iesimo(i))){
            _verticales.agregarAtras(m._verticales.iesimo(i));
        }
    }
    for ( int i = 0; i < m._horizontales.longitud(); i++){
        if( !_horizontales.pertenece(m._horizontales.iesimo(i))){
            _horizontales.agregarAtras(m._horizontales.iesimo(i));
        }
    }
}