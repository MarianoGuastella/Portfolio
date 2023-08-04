#ifndef LISTA_H_
#define LISTA_H_

#include <string>
#include <ostream>

using namespace std;

typedef unsigned int Nat;

template<class T>
class Lista {
public:

    /**
     * Constructor por defecto de la clase Lista.
     */
    Lista();

    /**
     * Constructor por copia de la clase Lista.
     */
    Lista(const Lista& l);

    /**
     * Destructor de la clase Lista.
     */
    ~Lista();

    /**
     * Operador asignacion
     * @param aCopiar
     * @return
     */
    Lista& operator=(const Lista<T>& aCopiar);

    /**
     * Agrega un elemento al principio de la Lista.
     * @param elem elemento a agregar
     */
    void agregarAdelante(const T& elem);

    /**
     * Agrega un elemento al final de la Lista.
     * @param elem elemento a agregar
     */
    void agregarAtras(const T& elem);

    /**
     * Elimina el i-ésimo elemento de la Lista.
     * @param i posición del elemento a eliminar
     */
    void eliminar(Nat i);

    /**
     * Devuelve la cantidad de elementos que contiene la Lista.
     * @return
     */
    int longitud() const;

    /**
     * Devuelve el elemento en la i-ésima posición de la Lista.
     * @param i posición del elemento a devolver.
     * @return referencia no modificable
     */
    const T& iesimo(Nat i) const;
    /**
     * Devuelve el elemento en la i-ésima posición de la Lista.
     * @param i posición del elemento a devolver.
     * @return referencia modificable
     */
    T& iesimo(Nat i);

    /**
     * Muestra la lista en un ostream
     * formato de salida: [a_0, a_1, a_2, ...]
     * @param o
     */
    void mostrar(ostream& o);

    void unirListas(Lista<T> otra);

    bool pertenece(T n) const;

    /**
     * Utiliza el método mostrar(os) para sobrecargar el operador <<
     */
    friend ostream& operator<<(ostream& os, Lista<T>& l) {
        l.mostrar(os);
        return os;
    }

private:

    struct Nodo {
        Nodo* anterior = nullptr;
        Nodo* siguiente = nullptr;
        T dato;
    };

    Nodo* prim_;
    Nodo* ult_;
    int long_;
};

template <class T>
Lista<T>::Lista() : long_(0), prim_(nullptr), ult_(nullptr) {

};

template <class T>
Lista<T>::Lista(const Lista<T>& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    long_ = 0;
    *this = l;
}
template <class T>
Lista<T>::~Lista() {
    Nodo* nodo_actual = prim_;
    while (nodo_actual != nullptr and nodo_actual->siguiente != nullptr) {
        nodo_actual = nodo_actual->siguiente;
        delete nodo_actual->anterior;
    }
    delete nodo_actual;
}

template<class T>
Lista<T>& Lista<T>::operator=(const Lista<T>& aCopiar) {
    while(long_ > 0){
        eliminar(0);
    }
    Nodo* nodo_actual = aCopiar.prim_;
    while(nodo_actual != nullptr){
        agregarAtras(nodo_actual->dato);
        nodo_actual = nodo_actual->siguiente;
    }
    return *this;
}

template<class T>
void Lista<T>::agregarAdelante(const T& elem) {
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

template<class T>
void Lista<T>::agregarAtras(const T& elem) {
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

template<class T>
void Lista<T>::eliminar(Nat i) {
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

template<class T>
int Lista<T>::longitud() const {
    return long_;
}

template<class T>
const T& Lista<T>::iesimo(Nat i) const {
    Nodo* n_actual = prim_;
    while (i > 0){
        n_actual = n_actual->siguiente;
        i = i - 1;
    }
    return n_actual->dato;
}

template<class T>
T& Lista<T>::iesimo(Nat i) {
    Nodo* n_actual = prim_;
    while (i > 0){
        n_actual = n_actual->siguiente;
        i = i - 1;
    }
    return n_actual->dato;
}

template<class T>
void Lista<T>::mostrar(ostream& o) {
    Nodo* n_actual = prim_;
    o << "[";
    while (n_actual != nullptr){
        o << " " << n_actual->dato << ",";
        n_actual = n_actual->siguiente;
    }
    o << "]";
}

template<class T>
void Lista<T>::unirListas(Lista<T> otra) {
    otra.prim_->anterior = ult_;
    ult_->siguiente = otra.prim_;
    ult_ = otra.ult_;
    long_ = long_ + otra.long_;
}

template<class T>
bool Lista<T>::pertenece(T n) const{
    bool res=false;
    Nodo* nodoActual=prim_;
    for(int i=0; i<long_ && !res; i++){
        if(nodoActual->dato==n){
            res=true;
        } else{
            nodoActual=nodoActual->siguiente;
        }
    }
    return res;
}


#endif
