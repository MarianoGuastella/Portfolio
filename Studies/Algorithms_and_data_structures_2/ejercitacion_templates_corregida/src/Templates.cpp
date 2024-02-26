#include<string>

using namespace std;

// Ejercicio 1: Pasar a templates
template <class T>
T cuadrado(T t) {
  return t * t;
}

// Ejercicio 2: Pasar a templates
template<class Contenedor, class Elem>
bool contiene(Contenedor c, Elem e) {
  for (int i = 0; i < c.size(); i++) {
    if (c[i] == e) {
      return true;
    }
  }
  return false;
}

// Ejercicio 3: Funcion es prefijo con un template contenedor
template<class Contenedor>
bool esPrefijo(Contenedor a, Contenedor b){
    if (a.size()<b.size()){
        bool iguales;
        for (int i = 0; i< a.size() ; i++){
            if (a[i] == b[i]){
                iguales = true;
            }
            else{
                return false;
            }
        }
        return iguales;
    }
    return false;
}
// Ejercicio 4: Función maximo con un template contenedor y uno elemento
template<class Contenedor, class Elem>
Elem maximo(Contenedor c){
    Elem max = c[0];
    for(int i = 1; i<c.size(); i++){
        if (c[i]> max){
            max = c[i];
        }
    }
    return max;
}
