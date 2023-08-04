#include "SimCity.h"

SimCity::SimCity(Mapa m){
    _mapa = m;
    _casas = Lista<tuple<Casilla, Nivel>>();
    _comercios = Lista<tuple<Casilla, Nivel>>();
    _turno = 0;
    _popularidad = 0;
    _huboConstruccion = false;
    _uniones = vector<SimCity>();

}

void SimCity::agregarCasa(Casilla c){
    _casas.agregarAtras(tuple<Casilla, Nivel>(c, 0));
    _huboConstruccion = true;
}

void SimCity::agregarComercio(Casilla c){
    _comercios.agregarAtras(tuple<Casilla, Nivel>(c, 0));
    _huboConstruccion = true;
}

void SimCity::avanzarTurno() {
    _turno++;
    actualizarCasas();
    actualizarComercios();
    for (int i = 0; i < _casas.longitud(); i++) {
        get<1>(_casas.iesimo(i)) = get<1>(_casas.iesimo(i)) + 1;
    }
    for (int i = 0; i < _comercios.longitud(); i++) {
        get<1>(_comercios.iesimo(i)) = get<1>(_comercios.iesimo(i)) + 1;
    }
}

void SimCity::unir(SimCity s){
    _turno = max(_turno,s._turno);
    _popularidad = _popularidad + s._popularidad + 1;
    _uniones.push_back(s);

}

Mapa SimCity::actualizarMapa() {
    Mapa res = _mapa;
    for(SimCity s : _uniones) {
        res.unirMapa(s._mapa);
    }
    _mapa = res;
    return res;
}

Lista<tuple<Casilla, Nivel>> SimCity::actualizarCasas(){
    for(SimCity s : _uniones){
        _casas.unirListas(s._casas);
    }
    Lista<tuple<Casilla,Nivel>> res;
    for( int i = 0; i < _casas.longitud(); i++){
        int j = 0;
        bool encontrado = false;
        for(j; j < res.longitud(); j++){
            if( get<0>(_casas.iesimo(i)) == get<0>(res.iesimo(j))){
                encontrado = true;
                break;
            }
        }
        if (encontrado) {
            get<1>(res.iesimo(j)) = max(get<1>(res.iesimo(j)), get<1>(_casas.iesimo(i)));
        } else {
            res.agregarAtras(_casas.iesimo(i));
        }
    }
    _casas=res;
    return res;
}

Lista<tuple<Casilla, Nivel>> SimCity::actualizarComercios() {
    Lista<tuple<Casilla, Nivel>> todos = _comercios;
    for(SimCity s: _uniones) {
        todos.unirListas(s._comercios);
    }
    Lista<tuple<Casilla, Nivel>> sinRepe;
    for(int i = 0; i < todos.longitud(); i++) {
        int j = 0;
        bool encontrado = false;
        for(j; j < sinRepe.longitud(); j++) {
            if (get<0>(todos.iesimo(i)) == get<0>(sinRepe.iesimo(j))) {
                encontrado = true;
                break;
            }
        }
        if (encontrado) {
            get<1>(sinRepe.iesimo(j)) = max(get<1>(sinRepe.iesimo(j)), get<1>(todos.iesimo(i)));
        } else {
            sinRepe.agregarAtras(todos.iesimo(i));
        }
    }
    Lista<tuple<Casilla, Nivel>> res;
    for(int j = 0; j < sinRepe.longitud(); j++) {
        bool encontrado = false;
        for (int i = 0; i < actualizarCasas().longitud(); i++) {
            if (get<0>(sinRepe.iesimo(j)) == get<0>(_casas.iesimo(i))) {
                encontrado = true;
            }
        }
        if (!encontrado) {
            res.agregarAtras(sinRepe.iesimo(j));
        }
    }
    for (int i = 0; i < res.longitud(); i++) {
        get<1>(res.iesimo(i)) = darNivelAComercio(get<0>(res.iesimo(i)));
    }
    _comercios = res;
    return res;
}

int SimCity::nivel(Casilla c){
    int res = 0;
    actualizarCasas();
    for(int i = 0; i<_casas.longitud(); i++){
        if(get<0>(_casas.iesimo(i)) == c){
            res = get<1>(_casas.iesimo(i));
        }
    }
    actualizarComercios();
    for(int i = 0; i< _comercios.longitud(); i++){
        if(get<0>(_comercios.iesimo(i)) == c){
            res = get<1>(_comercios.iesimo(i));
        }
    }
    return res;
}

bool SimCity::huboConstruccion() const{
    return _huboConstruccion;
}

int SimCity::popularidad() const{
    return _popularidad;
}

int SimCity::antiguedad() const{
    return _turno;
}

Lista<tuple<Casilla, Nivel>> SimCity::construcciones(){
    Lista<tuple<Casilla, Nivel>> cas = actualizarCasas();
    Lista<tuple<Casilla, Nivel>> com = actualizarComercios();
    cas.unirListas(com);
    return cas;
}

bool SimCity::hayConstruccion(Casilla c){
    Lista<tuple<Casilla, Nivel>> constr = construcciones();
    for (int i = 0; i < constr.longitud() ; i++) {
        if(get<0>(constr.iesimo(i)) == c){
            return true;
        }
    }
    return false;
}

bool SimCity::sePuedeConstruir(Casilla c){
    return !hayConstruccion(c) && !_mapa.hayRio(c);
}

bool SimCity::esCasillaDeMaximoNivel(Casilla c){
    return  nivel(c) == maximoNivel();
}

int SimCity::maximoNivel() const{
    return _turno;
}

int SimCity::darNivelAComercio(Casilla c){
    int res = 0;
    actualizarCasas();
    for(int i = 0; i < _casas.longitud(); i++){
        if((distanciaManhattan(get<0>(_casas.iesimo(i)),c)) <= 3 && get<1>(_casas.iesimo(i))>res){
            res=get<1>(_casas.iesimo(i));
        }
    }
    return res;
}

int SimCity::distanciaManhattan(Casilla x, Casilla y){
    return abs(get<0>(x) - get<0>(y)) + abs(get<1>(x) - get<1>(y)) ;
}