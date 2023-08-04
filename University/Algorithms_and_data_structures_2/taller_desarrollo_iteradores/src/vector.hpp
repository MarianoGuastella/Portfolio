#include "vector.h"

template<typename T>
vector<T>::vector() : valores(new T[10]), tam(0), capacidad(10) {}

template<typename T>
vector<T>::vector(const vector<T>& o) : vector() {
  *this = o;
}

template<typename T>
vector<T>::~vector() {
  delete[] valores;
}

template<typename T>
const vector<T>& vector<T>::operator=(const vector& o) {
  delete[] valores;
  valores = new T[o.capacidad];
  tam = o.tam;
  capacidad = o.capacidad;

  for (int i = 0; i < tam; i++) {
    valores[i] = o.valores[i];
  }

  return *this;
}

template<typename T>
int vector<T>::size() const {
  return tam;
}

template<typename T>
typename vector<T>::iterator vector<T>::push_back(const T& t) {
  if (tam == capacidad) {
    capacidad = capacidad * 2;
    T* _v = valores;
    valores = new T[capacidad];

    for (int i = 0; i < tam; i++) {
      valores[i] = _v[i];
    }
    delete[] _v;
  }
  valores[tam] = t;
  tam++;
  return iterator(tam-1, valores);
}

template<typename T>
T& vector<T>::operator[](int i) {
  return valores[i];
}

template<typename T>
const T& vector<T>::operator[](int i) const {
  return valores[i];
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(0, valores);
}

template<typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(tam, valores);
}

template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return const_iterator(0, valores);
}

template<typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return const_iterator(tam, valores);
}

// iterator

template<typename T>
vector<T>::iterator::iterator(int pos, T* valores) : 
    pos(pos), valores(valores) {}

template<typename T>
T& vector<T>::iterator::operator*() const {
  return valores[pos];
}

template<typename T>
typename vector<T>::iterator&  vector<T>::iterator::operator=(
    const vector<T>::iterator& o) {
  valores = o.valores;
  pos = o.pos;
  return *this;
}

template<typename T>
bool vector<T>::iterator::operator==(const vector<T>::iterator& o) const {
  return pos == o.pos;
}

template<typename T>
bool vector<T>::iterator::operator!=(const vector<T>::iterator& o) const {
  return not (*this == o);
}

template<typename T>
typename vector<T>::iterator& vector<T>::iterator::operator++() {
  pos++;
  return *this;
}

// const_iterator

template<typename T>
vector<T>::const_iterator::const_iterator(int pos, const T* valores) : 
    pos(pos), valores(valores) {}

template<typename T>
const T& vector<T>::const_iterator::operator*() const {
  return valores[pos];
}

template<typename T>
typename vector<T>::const_iterator& vector<T>::const_iterator::operator=(
    const vector<T>::const_iterator& o) {
  valores = o.valores;
  pos = o.pos;
  return *this;
}

template<typename T>
bool vector<T>::const_iterator::operator==(const vector<T>::const_iterator& o) const {
  return pos == o.pos;
}

template<typename T>
bool vector<T>::const_iterator::operator!=(const vector<T>::const_iterator& o) const {
  return not (*this == o);
}

template<typename T>
typename vector<T>::const_iterator& vector<T>::const_iterator::operator++() {
  pos++;
  return *this;
}
