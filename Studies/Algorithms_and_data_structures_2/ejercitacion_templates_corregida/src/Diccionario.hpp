
#ifndef SOLUCION_DICCIONARIO_HPP
#define SOLUCION_DICCIONARIO_HPP

#include <cassert>
#include <vector>
using namespace std;

template<class Clave, class Valor>
class Diccionario {
public:
    Diccionario();
    void definir(Clave k, Valor v);
    bool def(Clave k) const;
    Valor obtener(Clave k) const;
    vector<Clave> claves() const;
private:

    struct Asociacion {
        Asociacion(Clave k, Valor v);
        Clave clave;
        Valor valor;
    };
    vector<Asociacion> _asociaciones;
};

template<class Clave, class Valor>
Diccionario<Clave, Valor>::Diccionario() {
}

template<class Clave, class Valor>
Diccionario<Clave, Valor>::Asociacion::Asociacion(Clave k, Valor v) : clave(k), valor(v) {
}

template<class Clave, class Valor>
void Diccionario<Clave, Valor>::definir(Clave k, Valor v) {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            _asociaciones[i].valor = v;
            return;
        }
    }
    _asociaciones.push_back(Asociacion(k, v));
}

template<class Clave, class Valor>
bool Diccionario<Clave, Valor>::def(Clave k) const {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return true;
        }
    }
    return false;
}

template<class Clave, class Valor>
Valor Diccionario<Clave, Valor>::obtener(Clave k) const {
    for (unsigned int i = 0; i < _asociaciones.size(); i++) {
        if (_asociaciones[i].clave == k) {
            return _asociaciones[i].valor;
        }
    }
    assert(false);
}

template<class Clave, class Valor>
vector<Clave> Diccionario<Clave, Valor>::claves() const{
    vector<Clave> t1;
    vector<Clave> t2;
    for (int i = 0 ; i<_asociaciones.size(); i++){
        t1.push_back(_asociaciones[i].clave);
    }
  while (t1.size()>0){
      Clave min = t1[0];
      int pos = 0;
      for (int i = 1; i<t1.size() ; i++){
          if ( t1[i] < min){
              min = t1[i];
              pos = i;
          }
      }
      t2.push_back(min);
      t1.erase(t1.begin() + pos);
  }
    return t2;
}

#endif //SOLUCION_DICCIONARIO_HPP