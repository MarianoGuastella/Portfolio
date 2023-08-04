#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

bool pertenece(const int& item, const vector<int>& lista) {
    /*
     * Devuelve true si el entero pertenece al vector, en caso contrario devuelve false
     */
    for(auto& x : lista){
        if (x == item) {
            return true;
        }
    }
    return false;
}

void mostrar_ciclo(const vector<int>& ciclo) {
    /*
     * Imprime un vector de enteros en la consola
     */
    for (auto& x : ciclo) {
        cout << x << " ";
    }
    cout << endl;
}



vector<int> vecino_cercano(const int& max, const vector<vector<int>>& C) {
    /*
     * Heuristica de vecino mas cercano que crea un ciclo Hamiltoniano y lo devuelve
     */
    vector<int> solucion;
    struct timeval tv{};
    mingw_gettimeofday(&tv, nullptr);
    srand(tv.tv_usec);
    int act = rand() % int(C.size());    // Genera un numero aleatorio
    solucion.push_back(act);            // Y ese es el primero, por eso lo inserta
    for (int i = 0; i < C.size() - 1; i++) {
        int min = max + 1;
        int sig = 0;
        for (int j = 0; j < C.size(); j++) {
            if (!pertenece(j, solucion) && C[act][j] < min && act != j) {
                min = C[act][j];
                sig = j;
            }
        }
        solucion.push_back(sig);
        act = sig;
    }
    solucion.push_back(solucion[0]);
    return solucion;
}

int minLlave(const vector<int>& llave, const vector<bool>& AGMConj){
    /*
     * Encuentra la llave con el minimo valor y devuelve el indice donde se encuentra ese minimo valor
     */
    int min = INT_MAX;
    int min_index;
    for (int v = 0; v < llave.size(); v++){
        if (!AGMConj[v] && llave[v] < min){
            min = llave[v];
            min_index = v;
        }
    }
    return min_index;
}

vector<int> primAGM(const vector<vector<int>>& grafo, const int& raiz){
    /*
     * Crea un arbol generador minimo en el que cada vertice dice cual es su padre
     */
    int n = int(grafo.size());
    vector<int> padres(n);
    vector<int> llave(n, INT_MAX); //Sirve para tener los pesos minimos de las aristas
    vector<bool> AGMConj(n, false); //Sirve para saber que vertices ya estan incluidos
    llave[raiz] = 0;
    padres[raiz] = -1;
    for (int i = 0; i < n - 1; i++){
        int u = minLlave(llave, AGMConj);
        AGMConj[u] = true;
        for (int v = 0; v < n; v++){
            if (grafo[u][v] && !AGMConj[v] && grafo[u][v] < llave[v]){
                padres[v] = u;
                llave[v] = grafo[u][v];
            }
        }
    }
    return padres;
}

vector<vector<int>> invertir(const vector<int>& AGMP){
    /*
     * Recibe un vector de padres y devuelve un vector de hijos
     */
    vector<vector<int>> AGMH(AGMP.size());
    for (int i = 0; i < AGMP.size(); ++i) {
        if (AGMP[i] != -1){ //El nodo raiz no tiene padre por lo tanto no hay que asignarlo como hijo de ninguno
            AGMH[AGMP[i]].push_back(i);
        }
    }
    return AGMH;
}

vector<int> DFS(const vector<vector<int>>& AGMH, const int& raiz){
    /*
     * Realiza DFS y devuelve el orden del mismo
     */
    stack<int> pila;
    pila.push(raiz);
    vector<int> orden;
    while (!pila.empty()){
        int nodo_actual = pila.top();   // Agarra el primero y lo pone como actual para meter sus hijos
        orden.push_back(nodo_actual);
        pila.pop();
        if(!AGMH[nodo_actual].empty()){ // Mientras tenga hijos, lo mete en la pila
            for (int hijo : AGMH[nodo_actual]){
                pila.push(hijo);
            }
        }
    }
    return orden;
}

vector<int> HeuristicaAGM(const vector<vector<int>>& grafo){
    /*
     * Heuristica de arbol generador minimo que crea un ciclo Hamiltoniano y lo devuelve
    */
    struct timeval tv{};
    mingw_gettimeofday(&tv, nullptr);
    srand(tv.tv_usec);
    int raiz = rand() % int(grafo.size()); // Numero aleatorio
    vector<int> AGMP = primAGM(grafo, raiz); // AGMpadres
    vector<vector<int>> AGMH = invertir(AGMP); // AGMhijos
    vector<int> recorridoDFS = DFS(AGMH, raiz);
    recorridoDFS.push_back(recorridoDFS[0]);  // Cierro el ciclo
    return recorridoDFS;
}

int sumaCiclo(const vector<int>& res, const vector<vector<int>>& C){
    /*
     * Suma todas las aristas que conforman el ciclo res y devuelve la suma
     */
    int suma = 0;
    for (int  i = 1; i < res.size(); i++) {
        suma += C[res[i-1]][res[i]];
    }
    return suma;
}

vector<int> Swap(const vector<int>& circuito, const int& i, const int& j){
    /*
     * Intercambia dos vertices, dejando todo como estaba hasta el i, invierte el orden
     * entre i y j, y despues pone todo como estaba hasta el final
     */
    vector<int> res;
    res.reserve(circuito.size());
    for(int n = 0; n < i; n++){
        res.push_back(circuito[n]);
    }
    for(int m = j; m >= i; m--){
        res.push_back(circuito[m]);
    }
    for(int c = j + 1; c < circuito.size(); c++){
        res.push_back(circuito[c]);
    }
    res.pop_back();
    res.push_back(res[0]);  // Saca el ultimo y pone el primero para cerrar el ciclo
    return res;
}

vector<int> busquedaLocal(const vector<vector<int>>& grafo, const vector<int>& circuito) {
    /*
     * Heuristica de busqueda local que crea un ciclo Hamiltoniano, busca como mejorarlo localmente y lo devuelve
     */
    vector<int> mejor_circuito = circuito;
    bool improved = true;
    while(improved){
        improved = false;   // Hace 2opt mientras encuentre una mejora
        for(int i = 0; i < mejor_circuito.size() - 2; i++){
            for(int j = i + 1; j < mejor_circuito.size() - 1; j++){
                vector<int> nuevo_circuito = Swap(circuito, i, j);
                if(sumaCiclo(nuevo_circuito, grafo) < sumaCiclo(mejor_circuito, grafo)){
                    mejor_circuito = nuevo_circuito;
                    improved = true;
                }
            }
        }
    }
    return mejor_circuito;
}

vector<int> obtenerMejor(const vector<vector<int>>& vecinos, const list<vector<int>>& memoria, const vector<vector<int>>& grafo){
    /*
     * Busca el mejor de los vecinos siempre y cuando no este en la memoria como ciclo ya visto y lo devuelve
     */
    vector<int> mejor;
    int costoMejor = INT_MAX;
    for (auto &x : vecinos) {
        if (sumaCiclo(x, grafo) < costoMejor) {
            bool esta = false;
            for (auto& y : memoria){
                if (y == x) {
                    esta = true;
                }
            }
            if (!esta) {
                mejor = x;
                costoMejor = sumaCiclo(x, grafo);
            }
        }
    }
    return mejor;
}

vector<vector<int>> obtenerSubVecindad(const vector<int>& circuito, const int& porcentaje) {
    /*
     * Genera soluciones cercanas al circuito que se le pasa a traves del 2opt, se queda con un porcentaje de ellas
     * y las devuelve
     */
    vector<vector<int>> subVecindad;
    vector<pair<int,int>> vecindad;
    for (int i = 0 ; i < circuito.size() - 2 ; i++) {
        for (int j = i + 1 ; j < circuito.size() - 1 ; j++) {
            pair<int,int> vecino = make_pair(i, j);  // Necesitamos los pares para el Swap de 2opt
            vecindad.push_back(vecino);
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(vecindad.begin(), vecindad.end(), std::default_random_engine(seed));     // Mezclamos los vecinos y nos quedamos
    int cantVecinos = (int)vecindad.size() * porcentaje / 100;                      // una pequeña parte
    for (int i = 0; i < cantVecinos; i++) {
        pair<int, int> vecino = vecindad[i];
        subVecindad.push_back(Swap(circuito, vecino.first, vecino.second));
    }
    return subVecindad;
}

vector<int> tabuSearch(const vector<vector<int>>& grafo, const int& memoria_max, const int& porcentaje, const int& cant_iter){
    /*
     * Metaheuristica de busqueda tabu que crea un ciclo Hamiltoniano, explora soluciones cercanas y devuelve la mejor
     */
    vector<int> ciclo = HeuristicaAGM(grafo);
    vector<int> mejorCiclo = ciclo;
    list<vector<int>> memoria;
    int intentos = 0;
    while (intentos < cant_iter) {  // Cantidad maxima de iteraciones si no hay mejora
        vector<vector<int>> vecinos = obtenerSubVecindad(ciclo, porcentaje);
        ciclo = obtenerMejor(vecinos, memoria, grafo);
        if (ciclo.empty()) {
            ciclo = mejorCiclo;  // Si el ciclo esta vacio nos quedamos con el que tenemos
        }
        if (memoria.size() == memoria_max) {
            memoria.pop_front();        // Si se llena la memoria sacamos el primer elemento guardado
        }
        memoria.push_back(ciclo);
        if (sumaCiclo(ciclo, grafo) < sumaCiclo(mejorCiclo, grafo)){
            mejorCiclo = ciclo;
            intentos = 0;
        }
        intentos++;
    }
    return mejorCiclo;
}


pair<vector<int>, pair<pair<int, int>, pair<int, int>>> obtenerMejorS(const vector<int>& circuito, const vector<pair<pair<int, int>, pair<int, int>>>& vecinos, const list<pair<pair<int, int>, pair<int, int>>>& memoria, const vector<vector<int>>& grafo){
    /*
     * Busca el mejor de los vecinos siempre y cuando no este en la memoria como ciclo ya visto y lo devuelve junto al par de aristas que cambia. La variante es que en la memoria almacenamos los inversos de los pares de
     * aristas de los ciclos que hacemos, por eso tenemos que saber que aristas se cambian en el ciclo.
     */
    pair<vector<int>, pair<pair<int, int>, pair<int, int>>> mejor;
    int costoMejor = INT_MAX;
    for (auto &x : vecinos) {
        if (sumaCiclo(Swap(circuito, x.first.second, x.second.first), grafo) < costoMejor) {
            bool esta = false;
            for (auto& y : memoria){ // original (1,2),(4,5) (en vecinos),  inverso (1,4), (2,5) (en memoria)
                if (y.first.first == x.first.first && y.first.second == x.second.first && y.second.first == x.first.second && y.second.second == x.second.second) {
                    esta = true;
                }
            }
            if (!esta) {
                mejor = make_pair(Swap(circuito, x.first.second, x.second.first), x);
                costoMejor = sumaCiclo(Swap(circuito, x.first.second, x.second.first), grafo);
            }
        }
    }
    return mejor;
}

vector<pair<pair<int, int>, pair<int, int>>> obtenerSubVecindadS(const vector<int>& circuito, const int& porcentaje) {
    /*
     * Genera soluciones cercanas al circuito que se le pasa a traves del 2opt, se queda con un porcentaje de ellas
     * y las devuelve. La variante es que tenemos que devolver las aristas a intercambiar y no los ciclos.
     */
    vector<pair<pair<int, int>, pair<int, int>>> subVecindad;
    vector<pair<pair<int, int>, pair<int, int>>> vecindad;
    for (int i = 0; i < circuito.size() - 2; i++) {
        for (int j = i + 1; j < circuito.size() - 1; j++) {
            if (i == 0 && j != circuito.size() - 2){ //Casos bordes de aristas
                pair<pair<int, int>, pair<int, int>> vecino = make_pair(make_pair(circuito.size() - 2, i), make_pair(j, j + 1));
                vecindad.push_back(vecino);
            }
            if (i == 0 && j == circuito.size() - 2){
                pair<pair<int, int>, pair<int, int>> vecino = make_pair(make_pair(circuito.size() - 2, i), make_pair(j, 0));
                vecindad.push_back(vecino);
            }
            if (i != 0 && j == circuito.size() - 2){
                pair<pair<int, int>, pair<int, int>> vecino = make_pair(make_pair(i - 1, i), make_pair(j, 0));
                vecindad.push_back(vecino);
            }
            if (i != 0 && j != circuito.size() - 2){
                pair<pair<int, int>, pair<int, int>> vecino = make_pair(make_pair(i - 1, i), make_pair(j, j + 1));
                vecindad.push_back(vecino);

            }
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(vecindad.begin(), vecindad.end(), std::default_random_engine(seed));    // Mezclamos y nos quedamos con unos pocos vecinos
    int cantVecinos = (int) vecindad.size() * porcentaje / 100;
    for (int i = 0; i < cantVecinos; i++) {
        pair<pair<int, int>, pair<int, int>> vecino = vecindad[i];
        subVecindad.push_back(vecino);
    }
    return subVecindad;
}

vector<int> tabuSearchS(const vector<vector<int>>& grafo, const int& memoria_max, const int& porcentaje, const int& cant_iter){
    /*
     * Metaheuristica de busqueda tabu que crea un ciclo Hamiltoniano, explora soluciones cercanas y devuelve la mejor. La variante es que la memoria
     * ahora se guarda la inversa de el intercambio de aristas que genera el nuevo ciclo.
     */
    vector<int> mejorCiclo = HeuristicaAGM(grafo);
    pair<vector<int>, pair<pair<int, int>, pair<int, int>>> ciclo;  //ciclo y aristas que intercambias
    ciclo.first = mejorCiclo;
    list<pair<pair<int, int>, pair<int, int>>> memoria;            //lista de las inversas de las aristas intercambiadas
    int intentos = 0;
    while (intentos < cant_iter) {
        vector<pair<pair<int, int>, pair<int, int>>> vecinos = obtenerSubVecindadS(mejorCiclo, porcentaje); //vector de intercambios
        ciclo = obtenerMejorS(ciclo.first, vecinos, memoria, grafo);  //el ciclo resultante del mejor intercambio con el intercambio
        if (ciclo.first.empty()) {
            ciclo.first = mejorCiclo;
        }
        if (memoria.size() == memoria_max) {
            memoria.pop_front();
        }                                                            // original (1,2),(4,5) (en ciclo),  inverso (1,4), (2,5) (para memoria)
        pair<pair<int, int>, pair<int, int>> intercambioInvAristas = make_pair(make_pair(ciclo.second.first.first, ciclo.second.second.first), make_pair(ciclo.second.first.second, ciclo.second.second.second));
        memoria.push_back(intercambioInvAristas);
        if (sumaCiclo(ciclo.first, grafo) < sumaCiclo(mejorCiclo, grafo)){
            mejorCiclo = ciclo.first;
            intentos = 0;
        }
        intentos++;
    }
    return mejorCiclo;
}

int main(int argc, char** argv) {
    /*
     * Ejecuta el algoritmo pedido de entre los que estan a disposicion para encontrar un ciclo Hamiltoniano "optimo". Se le debe especificar el algoritmo, la cantidad de vertices, aristas y los pesos de cada arista
     * en formato v1 v2 peso ; y devuelve la cantidad de vertices, el peso del ciclo y el orden del ciclo. Tambien devuelve el tiempo para usos varios como la experimentacion.
     */
    map<string, string> algoritmos_implementados = {
            {"VMC", "Vecino mas cercano"},
            {"AGM", "Arbol generador minimo"},
            {"BL", "Busqueda local"},
            {"BT", "Busqueda Tabu"},
            {"BTS", "Busqueda Tabu Swap"}
    };

    if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& alg_desc: algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    int n, m;
    cin >> n >> m;
    vector<vector<int>> C = vector<vector<int>>(n, vector<int>(n, 0));
    int max = 0;
    int lineas= (n * (n - 1)) / 2;  // Pasamos las entradas a una matriz de adyacencia
    for (int i = 0; i < lineas; i++) {
        int x, y, c;
        cin >> x >> y >> c;

        C[x-1][y-1] = c;
        C[y-1][x-1] = c;
        if (c > max) {
            max = c;
        }
    }
    vector<int> res = vector<int>();
    auto start = chrono::steady_clock::now();
    if (algoritmo == "VMC") {
        res = vecino_cercano(max, C);
    }
    if (algoritmo == "AGM") {
        res = HeuristicaAGM(C);
    }
    if (algoritmo == "BL") {
        res = busquedaLocal(C, HeuristicaAGM(C));
    }
    if (algoritmo == "BT") {
        res = tabuSearch(C, 10, 20, 20);
    }
    if (algoritmo == "BTS") {
        res = tabuSearchS(C, 10, 20, 20);
    }
    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double, milli>(end - start).count();
    clog << total_time << endl;

    int suma = sumaCiclo(res, C);
    res.pop_back();
    cout << res.size() << " " << suma << endl;
    for (auto& x : res) {
        cout << x + 1 << " ";
    }
    return 0;
}
