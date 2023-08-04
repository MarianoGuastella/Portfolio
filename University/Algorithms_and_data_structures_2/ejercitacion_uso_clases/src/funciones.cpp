#include <vector>
#include "algobot.h"

using namespace std;

// Ejercicio 1
vector<int> quitar_repetidos(vector<int> s) {
    if (s.size() == 0) {
        return s;
    }
    vector<int> res;
    res.push_back(s[0]);
    for (int i = 1; i < s.size(); i++) {
        int repetido = 0;
        for (int j = 0; j < res.size(); j++) {
            if (s[i] == res[j]) {
                repetido = 1;
            }
        }
        if (repetido == 0) {
            res.push_back(s[i]);
        }
    }
    return res;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    if (s.size() == 0){
        return s;
    }
    set<int> aux;
    vector<int> res;
    for (int i = 0; i < s.size(); i++){
        if ( aux.count( s[i] ) == 0 ) {
            aux.insert(s[i]);
        }
    }
    for (int n : aux) {
        res.push_back(n);
    }
    return res;
}


// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    for (int n : a){
        bool encontrado = false;
        for (int m : b){
            if (n == m) {
                encontrado = true;
            }
        }
        if (!encontrado){
            return false;
        }
    }
    for(int n : b){
        bool encontrado = false;
        for (int m : a) {
            if (n == m){
                encontrado = true;
            }
        }
    if (!encontrado){
        return false;
        }
    }
    return true;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    vector<int> a_aux = quitar_repetidos_v2(a);
    vector<int> b_aux = quitar_repetidos_v2(b);
    if (a_aux.size() != b_aux.size()){
        return false;
    }
    set<int> s;
    for( int n : b_aux){
        s.insert(n);
    }
    for ( int n : b_aux ){
        if (s.count(n) == 0){
            return false;
        }
    }
    return true;
}

// Ejercicio 5
map<int, int> contar_apariciones(vector<int> s) {
    map<int, int> res;
    for (int n : s ) {
        if ( res.count(n) == 0) {
            res[n] = 1;
        }
        else {
            res[n] += 1;
        }
    }
    return res;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {
    map<int, int> dic = contar_apariciones(s);
    vector<int> res;
    for (int n : s){
        if (dic[n] == 1) {
            res.push_back(n);
        }
    }
    return res;
}

// Ejercicio 7
set<int> interseccion(set<int> a, set<int> b) {
    set<int> res;
    for (int n : a) {
        if ( b.count(n) == 1 ) {
            if (res.count(n) == 0) {
                res.insert(n);
            }
        }
    }
    return res;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int, set<int>> res;
    for ( int n : s ) {
        int x = n % 10;
        if ( res.count(x) == 0 ){
            set<int> conjunto;
            conjunto.insert(n);
            res[x] = conjunto;
        }
        else {
            if ( res[x].count(n) == 0){
                res[x].insert(n);
            }
        }
    }
    return res;
}

// Ejercicio 9
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector<char> res;
    for (char c : str) {
        bool encontrado = false;
        for (pair<char, char> tupla : tr){
            if (c == tupla.first){
                res.push_back(tupla.second);
                encontrado = true;
            }
        }
        if ( !encontrado ) {
            res.push_back(c);
        }
    }
    return res;
}

// Ejercicio 10
bool integrantes_repetidos(vector<Mail> s) {
    for (Mail m : s) {
        for (Mail n : s) {
            if (m.libretas() != n.libretas()) {
                for (LU l1 : m.libretas()){
                    for (LU l2 : n.libretas()){
                        if (l1 == l2){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Ejercicio 11
map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map<set<LU>, Mail> res;
    for (Mail m : s){
        if ( m.adjunto() ){
            if ( res.count(m.libretas()) == 0 ){
                res[m.libretas()] = m;
            }
            else if (m.fecha() > res[m.libretas()].fecha()){
                res[m.libretas()] = m;
            }
        }
    }
  return res;
}
