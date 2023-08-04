#include "Lista.h"

Lista::Lista() : long_(0), prim_(nullptr), ult_(nullptr) {

};

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    Nodo* nodo_actual = prim_;
    while (nodo_actual != nullptr and nodo_actual->siguiente != nullptr) {
        nodo_actual = nodo_actual->siguiente;
        delete nodo_actual->anterior;
    }
    delete nodo_actual;
}

Lista& Lista::operator=(const Lista& aCopiar) {
    Nodo* n_actual = prim_;
    while(n_actual != nullptr){
        n_actual = n_actual->siguiente;
        eliminar(0);
    }
    Nodo* nodo_actual = aCopiar.prim_;
    while(nodo_actual != nullptr){
        this->agregarAtras(nodo_actual->dato);
        nodo_actual = nodo_actual->siguiente;
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* n = new Nodo();
    n->dato = elem;
    if (long_ == 0){
        ult_ = n;
    }
    else{
        n->siguiente = prim_;
        prim_->anterior = n;
    }
    prim_ = n;
    long_ = long_ + 1;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* n = new Nodo();
    n->dato = elem;
    if (long_ == 0){
        prim_ = n;
    }
    else{
        n->anterior = ult_;
        ult_->siguiente = n;
    }
    ult_ = n;
    long_ = long_ + 1;
}

void Lista::eliminar(Nat i) {
    Nodo* n_actual = prim_;
    for (int j = 0 ; n_actual != nullptr and j <= i; j++){
        if (j == i){
            if (n_actual->anterior == nullptr){
                prim_ = n_actual->siguiente;
                if(n_actual->siguiente != nullptr){
                    n_actual->siguiente->anterior = nullptr;
                }
            }
            if (n_actual->siguiente == nullptr){
                ult_ = n_actual->anterior;
                if(n_actual->anterior != nullptr){
                    n_actual->anterior->siguiente = nullptr;
                }
            }
            if (n_actual->anterior != nullptr and n_actual->siguiente != nullptr){
                n_actual->anterior->siguiente = n_actual->siguiente;
                n_actual->siguiente->anterior = n_actual->anterior;
            }
            delete n_actual;
            long_ = long_ - 1;
        }
        else{
            n_actual = n_actual->siguiente;
        }
    }
}

int Lista::longitud() const {
    return long_;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* n_actual = prim_;
    while (i > 0){
        n_actual = n_actual->siguiente;
        i = i - 1;
    }
    return n_actual->dato;
    assert(false);
}

int& Lista::iesimo(Nat i) {
    Nodo* n_actual = prim_;
    while (i > 0){
        n_actual = n_actual->siguiente;
        i = i - 1;
    }
    return n_actual->dato;
    assert(false);
}

void Lista::mostrar(ostream& o) {
    Nodo* n_actual = prim_;
    o << "[";
    while (n_actual != nullptr){
        o << " " << n_actual->dato << ",";
        n_actual = n_actual->siguiente;
    }
    o << "]";
}
