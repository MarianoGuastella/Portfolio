#include "Diccionario.hpp"
#ifndef SOLUCION_MULTICONJUNTO_HPP
#define SOLUCION_MULTICONJUNTO_HPP

template<class T>
class Multiconjunto {
public:
    Multiconjunto();
    void agregar(T x);
    int ocurrencias(T x) const;
    bool operator<=(Multiconjunto<T> otro) const;

private:
    Diccionario<T, int> dic_;
};

template<class T>
Multiconjunto<T>::Multiconjunto()  : dic_(Diccionario<T, int>()) {

}

template<class T>
void Multiconjunto<T>::agregar(T x){
    if (!dic_.def(x)){
        dic_.definir(x, 1);
    }
    else{
        int cant = dic_.obtener(x);
        dic_.definir(x, cant+1);
    }
}

template<class T>
int Multiconjunto<T>::ocurrencias(T x) const{
    if (!dic_.def(x)){
        return 0;
    }
    return dic_.obtener(x);
}

template<class T>
bool Multiconjunto<T>::operator<=(Multiconjunto<T> otro) const {
    vector<T> claves = dic_.claves();
    for(T clave : claves){
        if(ocurrencias(clave) > otro.ocurrencias(clave)){
            return false;
        }
    }
    return true;
}

#endif //SOLUCION_MULTICONJUNTO_HPP
