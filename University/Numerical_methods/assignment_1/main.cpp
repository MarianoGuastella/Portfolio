#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "csr.h"
#include "VoL.h"

using namespace std;

void printVector(vector<double>& vec) {
    cout << "\n Printing Vector : \n";
    for (double j : vec)
        cout << (vec[j]) << " ";
    cout << endl;
}

void printMatrix(Csr& matrix) { // imprime cuadrada, sin el vector de los resultados.
    cout << "\n Printing Matrix : \n";
    for (int i = 0; i < matrix.rows(); i++) {
        for (int j = 0; j < matrix.rows(); j++)
            cout << (matrix.get(i,j)) << " ";
        cout << endl;
    }
    cout << endl;
}

vector<double> BuildDMatrix(Csr& matrix) {
    vector<double> D =  vector<double>(matrix.rows());
    for (int j = 0; j < matrix.rows(); j++) // iterador de columnas
    {
        double dsubj = 0;
        for (int i = 0; i < matrix.rows(); i++) { // iterador de filas
            dsubj += matrix.get(i,j);
        }
        if (dsubj == 0) {
          D[j] = 0;
        } else {
          D[j] = 1.0 / dsubj;
        }
    }
    return D;
}

void DxWMatrixProduct(Csr& Wmatrix, vector<double> Dmatrix) {
    for (int j = 0; j < Wmatrix.rows(); j++) {
        for (int i = 0; i < Wmatrix.rows(); i++) {
            Wmatrix.set(i, j, Wmatrix.get(i, j) * Dmatrix[j]);
        }
    }
}

void IdentityMinusPMatrix(Csr& Matrix, double p) { // hace I-p(matriz)
    Matrix.scalar(p);
    for (int i = 0; i < Matrix.rows(); i++) {
        for (int j = 0; j < Matrix.rows(); j++) {
            if (j == i) {
                Matrix.set(i, j, 1 - Matrix.get(i, j));
            }
            else {
                Matrix.set(i, j, - Matrix.get(i, j));
            }
        }
    }
}

void Load1InLastColumn(Csr& Matrix) { // esto para poner los 1 en la ultima columna, la de los resultados del sistema.
    for (int i = 0; i < Matrix.rows(); i++) {
        Matrix.set(i, Matrix.columns() - 1, 1);
    }
}

Csr ReadFile(string file) {
    fstream fs;
    fs.open(file);
    char a[256];
    string b;
    int n;
    int m;
    fs.getline(a, 256, '\n');
    n = stoi(a);
    fs.getline(a, 256, '\n');
    m = stoi(a);
    Csr w = Csr(n, n + 1);
    for (int k = 0; k < m; k++) {
        fs.getline(a, 256, '\n');
        b = string(a);
        string i_s;
        string j_s;
        bool space = false;

        for (char c : b) {
            if (c == ' ') {
                space = true;
            }
            else {
                if (space) {
                    j_s += c;
                }
                else {
                    i_s += c;
                }
            }
        }
        int i = stoi(i_s) - 1;
        int j = stoi(j_s) - 1;
        w.set(j, i, 1);
    }
    fs.close();
    return w;
}

void WriteFile(vector<double>& res, double p, string test_file){
    // Crea un archivo, pone la primera linea la probabilidad y luego
    // pone los n valores, uno por linea
    int n = res.size();
    string res_file = test_file + ".out";
    ofstream Resultado(res_file);
    Resultado << p << endl;
    for (int i = 0; i < n; i++){
        Resultado << res[i] << endl;
    }
    Resultado.close();
}

void Normalizer3000(vector<double>& res){
    // Normaliza el vector, importante notar que solo funciona
    // para positivos, que es el caso actual.
    double total = 0;
    int n = res.size();
    for (int i = 0; i < n; i++){
        total = total + res[i];
    }
    for (int j = 0; j < n; j++){
        res[j] = res[j] / total;
    }
}

int main(int argc, char *argv[]){
    // Crea la matriz W a partir del archivo y guarda el p del mismo archivo
    // Crea la matriz D a partir de la W y la multiplica con la W y p y se la resta
    // a la identidad. Luego agrega una columna y hace la eliminacion gaussiana.
    // Finalmente pasa los resultados a un vector el cual despues guarda en un archivo.
    string test_file = argv[1];
    Csr W = ReadFile(test_file);
    double p = stod(argv[2]);
    vector<double> D = BuildDMatrix(W);

    DxWMatrixProduct(W, D);
    IdentityMinusPMatrix(W, p);
    Load1InLastColumn(W);

    VoL W_VoL = VoL::csr_to_VoL(W);

    W_VoL.gaussianElimination8000EXTREME();

    vector<double> res = W_VoL.TriangulatedMatrixSolution();
    Normalizer3000(res);
    WriteFile(res, p, test_file);

    return 0;
}



