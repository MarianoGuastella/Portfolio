#include <iostream>
#include <vector>
#include <map>
#include <chrono>


using namespace std;

int npm_fuerza_bruta(const vector<pair<int,int>> &L, const int &M, int i = 0, vector<int> negocios = {}) {
    /*
     * Resuelve el problema Negocios Por Medio utilizando Fuerza Bruta.
     * Recibe un vector de negocios, cada uno definido como un par (beneficio, contagio) y el maximo posible contagio.
     * i indica el negocio que se evalua en cada instancia.
     * negocios es el vector de negocios de la solucion.
     */
    if (i == L.size()) { // #Caso base
        if (negocios.size() > 1) { // #Si tengo mas de un negocio, chequeo que no sean adyacentes.
            for (int j = 0; j < negocios.size() - 1; j++) {
                if (negocios[j] + 1 == negocios[j + 1]) {
                    return 0;
                }
            }
        }
        int b = 0; // #Beneficio parcial
        int m = 0; // #Contagio parcial
        for (auto &negocio : negocios) { // #Sumo el beneficio y contagio de la solucion
            b += L[negocio].first;
            m += L[negocio].second;
        }
        if (m > M) { // #Si m es mayor a M, la solucion no es valida, devuelvo 0
            return 0;
        }
        return b;
    }
    int caso_no_elijo = npm_fuerza_bruta(L, M, i + 1, negocios); // #Calculo el caso en que no agrego el negocio i
    negocios.push_back(i); // #Agrego el negocio i a la solucion
    int caso_elijo = npm_fuerza_bruta(L, M, i + 1, negocios); // #Calculo el caso en que agrego el negocio i
    return max(caso_no_elijo, caso_elijo); // #Devuelvo el maximo de ambos
}

bool poda_optimalidad = true; // #Valores booleanos para saber que podas utilizar en el algoritmo de Backtracking
bool poda_factibilidad = true;
int B_bt = 0; // #Beneficio maximo encontrado usando Backtracking
int npm_backtracking(const vector<pair<int,int>> &L, const int &M, int b_restante, int i = 0, int b = 0, int m = 0, vector<int> negocios = {}) {
    /*
     * Resuelve el problema Negocios Por Medio utilizando Backtracking.
     * Recibe un vector de negocios, cada uno definido como un par (beneficio, contagio) y el maximo posible contagio.
     * i indica el negocio que se evalua en cada instancia.
     * b_restante es el beneficio acumulado de los negocios desde i hasta n.
     * b es el beneficio parcial.
     * m es el contagio parcial.
     * negocios es el vector de negocios de la solución (Solo se usa si poda_factibilidad).
     */
    if (poda_factibilidad && (m > M)) { // #Si quiero incluir poda de factibilidad
        return 0;
    }
    if (i >= L.size()) { // #Caso base
        if (negocios.size() > 1) { // #Si tengo mas de un negocio, chequeo que no sean adyacentes. (para poda_factibilidad = false)
            for (int j = 0; j < negocios.size() - 1; j++) {
                if (negocios[j] + 1 == negocios[j + 1]) {
                    return 0;
                }
            }
        }
        if (m > M) {
            return 0;
        }
        B_bt = max(B_bt, b);
        return b;
    }
    if (poda_optimalidad && (b + b_restante <= B_bt)) { // #Si quiero incluir poda de optimalidad
        return 0;
    }
    if (poda_factibilidad) { // #Calculo el caso en que agrego el negocio i
        int caso_elijo = npm_backtracking(L, M, b_restante - L[i].first, i + 2, b + L[i].first, m + L[i].second, negocios);
        int caso_no_elijo = npm_backtracking(L, M, b_restante, i + 1, b, m, negocios); // #Calculo el caso en que no agrego el negocio i
        return max(caso_no_elijo, caso_elijo); // #Me quedo con el maximo valor de ambos caminos
    } else { // Si poda_factibilidad = false, tengo que hacer como en fuerza bruta
        vector<int> negocios_sin_i = negocios;
        negocios.push_back(i);
        int caso_elijo = npm_backtracking(L, M, b_restante - L[i].first, i + 1, b + L[i].first, m + L[i].second, negocios);
        int caso_no_elijo = npm_backtracking(L, M, b_restante, i + 1, b, m, negocios_sin_i); // #Calculo el caso en que no agrego el negocio i
        return max(caso_no_elijo, caso_elijo); // #Me quedo con el maximo valor de ambos caminos
    }
}

const int UNDEFINED = -1;  // #Constante arbitraria
vector<vector<int>> Beneficios; // #Matriz de memoria dinamica
int npm_dinamica(const vector<pair<int,int>> &L, const int &M, int i = 0, int b = 0, int m = 0) {
    /*
     * Resuelve el problema Negocios Por Medio utilizando Programacion Dinamica.
     * La funcion recibe el vector de negocios con (beneficio, contagio) y el contagio maximo.
     * i indica el negocio que se evalua en cada instancia.
     * b es el beneficio parcial.
     * m es el contagio parcial.
     * Devuelve el maximo beneficio posible.
     */
    if (m > M) { //Evito que se pase de M porque la matriz es {0, ..., n - 1} x {0, ..., M}
        return 0;
    }
    if (i >= L.size()){  // #Caso Base final del vector de negocios
        return b;
    }
    if (Beneficios[i][m] == UNDEFINED) {  // #Si no esta definido en la matriz lo definimos
        int caso_no_elijo = npm_dinamica(L, M, i + 1, b, m);  // #Calculo el caso en que no agrego el negocio i
        int caso_elijo = npm_dinamica(L, M, i + 2, b + L[i].first, m + L[i].second); // #Calculo el caso en que agrego el negocio i
        Beneficios[i][m] = max(caso_no_elijo, caso_elijo); // #Me quedo con el maximo de ambos caminos
    }
    return Beneficios[i][m];
}

int main(int argc, char** argv){
    /*
     * Resuelve el problema Negocios Por Medio utilizando alguna de las tecnicas algoritmicas implementadas.
     * Devuelve el beneficio maximo al usuario.
    */
    map<string, string> algoritmos_implementados = {
            {"FB", "Fuerza Bruta"},
            {"BT", "Backtracking con podas"},
            {"BT-F", "Backtracking con poda por factibilidad"},
            {"BT-O", "Backtracking con poda por optimalidad"},
            {"DP", "Programacion dinamica"} };

    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    int n, M; // #Cantidad de negocios y contagio maximo
    vector<pair<int,int>> L; // #Vector de Negocios con (beneficio, contagio)

    cin >> n >> M;
    L.assign(n, pair<int,int>(0,0));
    for (int i = 0; i < n; i++) {
        cin >> L[i].first >> L[i].second;
    }

    int ben = 0; // #Beneficio a devolver al usuario

    auto start = chrono::steady_clock::now();
    if (algoritmo == "FB"){ // #Elijo el algoritmo segun corresponda
        ben = npm_fuerza_bruta(L, M);
    }
    if (algoritmo == "BT"){
        poda_factibilidad = true;
        poda_optimalidad = true;
        B_bt = 0;
        int b_total = 0;
        for (auto &negocio : L) {
            b_total += negocio.first;
        }
        ben = npm_backtracking(L, M, b_total);
    }
    if (algoritmo == "BT-F"){
        poda_factibilidad = true;
        poda_optimalidad = false;
        B_bt = 0;
        int b_total = 0;
        for (auto &negocio : L) {
            b_total += negocio.first;
        }
        ben = npm_backtracking(L, M, b_total);
    }
    if (algoritmo == "BT-O"){
        poda_factibilidad = false;
        poda_optimalidad = true;
        B_bt = 0;
        int b_total = 0;
        for (auto &negocio : L) {
            b_total += negocio.first;
        }
        ben = npm_backtracking(L, M, b_total);
    }
    if (algoritmo == "DP"){
        Beneficios = vector<vector<int>>(n, vector<int>(M, UNDEFINED));
        ben = npm_dinamica(L, M);
    }
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();
    clog << total_time << endl;
    cout << ben << "\n";
    return 0;
}
