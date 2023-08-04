#ifndef VECTOR_H
#define VECTOR_H

/**
 * Esta implementación asume que el tipo T tiene constructor por defecto
 * y operador de asignación.
 */
template<typename T>
class vector {
 public:

  using value_type = T;

  class iterator;
  class const_iterator;

  vector();
  vector(const vector& o);
  const vector& operator=(const vector&);
  ~vector();

  int size() const;

  T& operator[](const int);
  const T& operator[](const int) const;

  iterator push_back(const T&);

  iterator begin();
  const_iterator begin() const;
  
  iterator end();
  const_iterator end() const;

  class iterator {
   public:

    using value_type = T;
    
    iterator(const iterator&);
    iterator& operator=(const iterator&);

    value_type& operator*() const;

    iterator& operator++();
    
    bool operator==(const iterator&) const;
    bool operator!=(const iterator&) const;

    friend class vector;

   private:
    int pos;
    T* valores;

    iterator(int, T*);
  };


  class const_iterator {
   public:

    const_iterator(const const_iterator&);
    const_iterator& operator=(const const_iterator&);

    const value_type& operator*() const;

    const_iterator& operator++();
    
    bool operator==(const const_iterator&) const;
    bool operator!=(const const_iterator&) const;

    friend class vector;

   private:
    int pos;
    const T* valores;
    
    const_iterator(int, const T*);
  };

 private:
  T* valores;
  int tam;
  int capacidad;
   
};

#include "vector.hpp"

#endif
