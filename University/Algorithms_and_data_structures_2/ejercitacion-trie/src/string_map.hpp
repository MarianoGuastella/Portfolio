
#include "string_map.h"

template <typename T>
string_map<T>::string_map(){
   _raiz = nullptr;
   _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    destructorAux(_raiz);
    _raiz = nullptr;
    _size = 0;
    set<pair<string, T>> claves;
    if(d._raiz != nullptr) {
        _claves(d._raiz, "", claves);
        for (pair<string, T> clave : claves) {
            insert(clave);
        }
    }
    return *this;
}

template <typename T>
void string_map<T>::_claves(Nodo * n, string prefijo, set<pair<string, T>>& claves){
    for(int i = 0; i < 256; i++){
        Nodo* actual = n->siguientes[i];
        prefijo.push_back(char(i));
        if(actual != nullptr){
            if(actual->definicion != nullptr){
                claves.insert(make_pair(prefijo, *(actual->definicion)));
            }
            _claves(n->siguientes[i], prefijo, claves);
        }
       prefijo.pop_back();
    }
}

template <typename T>
string_map<T>::~string_map(){
    destructorAux(_raiz);
}

template <typename T>
void string_map<T>::destructorAux(Nodo * nodo){
    if(nodo != nullptr){
        for(Nodo* hijo : nodo->siguientes){
            destructorAux(hijo);
        }
        delete nodo->definicion;
    }
    delete nodo;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    stack<Nodo *> pila;
    _size--;
    Nodo * nodo_actual = _raiz;
    for (int i = 0; i < clave.size(); i++){
        pila.push(nodo_actual);
        nodo_actual = nodo_actual->siguientes[int(clave[i])];
        }
    delete nodo_actual->definicion;
    nodo_actual->definicion = nullptr;
    int i =clave.length() -1;
    while(pila.size() > 0){
        if(nodo_actual->definicion == nullptr && todosNullptr(nodo_actual->siguientes)){
            pila.pop();
            nodo_actual = pila.top();
            delete nodo_actual->siguientes[int(clave[i])];
            nodo_actual->siguientes[int(clave[i])] = nullptr;
            i--;
        }
        else{
            break;
        }
    }
}

template<typename T>
bool string_map<T>::todosNullptr(vector<Nodo*> siguientes){
    for (Nodo* nodo :siguientes){
        if (nodo != nullptr){
            return false;
        }
    }
    return true;
}

template<typename T>
void string_map<T>::insert(const pair<string, T>& par) {
    bool seCreoNodo = false;
    if(_raiz == nullptr){
        Nodo * nodoNuevo = new Nodo();
        _raiz = nodoNuevo;
    }
    Nodo * nodo_actual = _raiz;
    for (int i = 0; i < par.first.size(); i++) {
        if (nodo_actual->siguientes[int(par.first[i])] == nullptr) {
            Nodo *nodo = new Nodo();
            nodo_actual->siguientes[int(par.first[i])] = nodo;
            nodo_actual = nodo;
            seCreoNodo = true;
        }
        else{
            nodo_actual = nodo_actual->siguientes[int(par.first[i])];
        }
    }
    if (seCreoNodo){
        _size++;
    }
    else {
        delete nodo_actual->definicion;
    }
    nodo_actual->definicion = new T(par.second);

}

template <typename T>
int string_map<T>::count(const string& clave) const{
    if(_raiz == nullptr){
        return 0;
    }
    Nodo* nodo_actual = _raiz;
    for (int i = 0; i < clave.size(); i++){
        if(nodo_actual->siguientes[int(clave[i])] == nullptr){
            return 0;
        }
        nodo_actual = nodo_actual->siguientes[int(clave[i])];
    }
    if (nodo_actual->definicion != nullptr){
        return 1;
    }
    return 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* nodo_actual = _raiz;
    for (int i = 0; i < clave.size(); i++){
        nodo_actual = nodo_actual->siguientes[int(clave[i])];
    }
    return *nodo_actual->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* nodo_actual = _raiz;
    for (int i = 0; i < clave.size(); i++){
        nodo_actual = nodo_actual->siguientes[int(clave[i])];
    }
    return *nodo_actual->definicion;
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return _size == 0;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}
