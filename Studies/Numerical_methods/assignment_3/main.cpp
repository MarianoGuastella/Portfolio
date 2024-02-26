#include <iostream>
#include "eigen/Eigen/Dense"
#include "eigen/Eigen/Sparse"
#include <fstream>
#include <string>
#include <stdexcept>
#include <chrono>

using namespace std;

using Eigen::MatrixXd;
using Eigen::SparseMatrix;
using Eigen::VectorXd;
typedef SparseMatrix<double> MatrixXdLOL;

// Operaciones para SparseMatrix
// GET: matrix.coeff(i, j)
// SET: matrix.insert(i, j) = value

VectorXd ones(int size) {
  VectorXd res(size);
  for (int i = 0; i < size; i++) {
    res(i) = 1;
  }
  return res;
}

VectorXd jacobi(MatrixXdLOL &matrix, int niter=10000, double eps=1e-6){
  VectorXd b = ones(matrix.rows());
  MatrixXd D = matrix.triangularView<Eigen::Lower>() - matrix.triangularView<Eigen::StrictlyLower>();
  MatrixXdLOL L = -matrix.triangularView<Eigen::StrictlyLower>();
  MatrixXdLOL U = -matrix.triangularView<Eigen::StrictlyUpper>();
  MatrixXdLOL DMinus1= (D.inverse()).sparseView();
  MatrixXdLOL LplusU = L + U;

  VectorXd x = VectorXd::Random(matrix.cols());
  for(int i = 0; i< niter; i++){
    VectorXd x_ant = x;
    x = DMinus1 * ((LplusU) * (x)) + (DMinus1 * b);
    if ((x - x_ant).norm() < eps) {
      return x / x.sum();
    }
  }

  return x / x.sum();
}

VectorXd gaussSeidel(SparseMatrix<double> &matrix, int niter=10000, double eps=1e-6) {
  int n = matrix.cols();
  VectorXd b = ones(matrix.rows());
  VectorXd x = VectorXd::Random(n);
  for (int iter = 0; iter < niter; iter++) {
    VectorXd x_ant = x;
    for (int i = 0; i < n; i++) {
      double sum = 0;
      for (int j = 0; j < n; j++) {
        if (j == i) { continue; }

        sum += matrix.coeff(i, j) * x(j);
      }
      x(i) = (b(i) - sum) / matrix.coeff(i, i);
    }
    if ((x - x_ant).norm() < eps) {
      return x / x.sum();
    }
  }
  return x / x.sum();
}

VectorXd gaussianElimination(SparseMatrix<double>& matrix) {
    VectorXd b = ones(matrix.rows());
    Eigen::SparseLU<SparseMatrix<double>, Eigen::COLAMDOrdering<int>> LU;
    LU.compute(matrix);
    LU.factorize(matrix);
    VectorXd x = LU.solve(b);
    return x / x.sum();
}


// SparseMatrix<double> densifyDouble(SparseMatrix<double> matrix){
//   int n= matrix.nonZeros();

//   if(matrix.nonZeros() * 2 > availableCells(matrix)){
//     for(int n=0; n< matrix.nonZeros(); n++){
//       bool success= false;
//       while(!success){
//         int i = rand() % matrix.rows();
//         int j = rand() % matrix.rows();
//         if(i==j){
//         continue;
//         }
//         if(matrix.coeff(i,j) == 0){
//           matrix.insert(i,j) = 1;
//           matrix.insert(j,i) = 1;
//           success=true;
//         }
//       }
//     }
//   }
// }

// SparseMatrix<double> densifyLinear(SparseMatrix<double> matrix){
//   int n= matrix.nonZeros();

//   if(matrix.rows() > availableCells(matrix)){
//     for(int n=0; n< matrix.rows(); n++){
//       bool success= false;
//       while(!success){
//         int i = rand() % matrix.rows();
//         int j = rand() % matrix.rows();
//         if(i==j){
//         continue;
//         }
//         if(matrix.coeff(i,j) == 0){
//           matrix.insert(i,j) = 1;
//           matrix.insert(j,i) = 1;
//           success=true;
//         }
//       }
//     }
//   }
   
// }


SparseMatrix<double> readMatrix(string file) {
    fstream fs;
    fs.open(file);
    char a[256];
    int n;
    int m;
    fs.getline(a, 256, '\n');
    n = stoi(a);
    fs.getline(a, 256, '\n');
    m = stoi(a);
    SparseMatrix<double> matrix(n, n);
    for (int k = 0; k < m; k++) {
        fs.getline(a, 256, '\n');
        string b = string(a);
        string j_s = b.substr(0, b.find(' '));
        b.erase(0, b.find(' ') + 1);
        string i_s = b.substr(0, b.find(' '));
        int i = stoi(i_s) - 1;
        int j = stoi(j_s) - 1;
        matrix.insert(i, j) = 1;
    }
    fs.close();
    return matrix;
}

vector<double> buildDMatrix(MatrixXdLOL& W) {
    vector<double> D(W.rows());
    for (int j = 0; j < W.rows(); j++) // iterador de columnas
    {
        double dsubj = 0;
        for (int i = 0; i < W.rows(); i++) { // iterador de filas
            dsubj += W.coeff(i,j);
        }
        if (dsubj == 0) {
          D[j] = 0;
        } else {
          D[j] = 1.0 / dsubj;
        }
    }
    return D;
}

MatrixXdLOL WxD(MatrixXdLOL& W, vector<double> &D) {
    MatrixXdLOL res(W.rows(), W.cols());
    for (int j = 0; j < W.rows(); j++) {
        for (int i = 0; i < W.rows(); i++) {
            res.insert(i, j) =  W.coeff(i, j) * D[j];
        }
    }
    return res;
}

MatrixXdLOL createMMatrix(string input_file, double p) {
    MatrixXdLOL W = readMatrix(input_file);
    vector<double> D = buildDMatrix(W);
    MatrixXdLOL I(W.rows(), W.cols());
    I.setIdentity();
    return I - p * WxD(W, D);
}

void writeFile(VectorXd& res, double p, string input_file){
    // Crea un archivo, pone la primera linea la probabilidad y luego
    // pone los n valores, uno por linea
    int n = res.size();
    string res_file = input_file + ".out";
    ofstream resultado(res_file);
    resultado << p << endl;
    for (int i = 0; i < n; i++){
        resultado << res[i] << endl;
    }
    resultado.close();
}

std::map<string, int> ALGORITHMS = {{"EG", 1}, {"eg", 1}, {"JA", 2}, {"ja", 2}, {"GS", 3}, {"gs", 3}};

static const string AVAILABLE_ALGORITHMS_MESSAGE = "Algorithms:\nEG (alias eg): Eliminacion Gaussiana\nJA (alias ja): Jacobi\nGS (alias gs): Gauss-Seidel";

int main(int argc, char* argv[]) {
  if (argc >= 4) {
    int algorithm;
    if (ALGORITHMS.count(argv[1])) {
      algorithm = ALGORITHMS[argv[1]];
    } else {
      cout << "Unknown algorithm '" << argv[1] << "'" << endl << AVAILABLE_ALGORITHMS_MESSAGE << endl;
      return 1;
    }
    string input_file = argv[2];
    double p = stod(argv[3]);
    int niter = 10000;
    double eps = 1e-6;
    if (argc >= 5) {
      niter = stoi(argv[4]);
    }
    if (argc >= 6) {
      eps = stod(argv[5]);
    }
    // cout << algorithm << endl;
    // cout << input_file << endl;
    // cout << p << endl;
    // cout << niter << endl;
    // cout << eps << endl;
    MatrixXdLOL M = createMMatrix(input_file, p);
    VectorXd x;

    auto start = chrono::steady_clock::now(); // Tiempo de inicio

    switch(algorithm) {
        case 1: {
            // Eliminacion Gaussiana
            x = gaussianElimination(M);
        break;
        }
        case 2: {
            //Jacobi
            x = jacobi(M, niter, eps);
        break;
        }
        case 3: {
            //Gauss-Seidel
            x = gaussSeidel(M, niter, eps);
        break;
        }
    }

    auto end = chrono::steady_clock::now(); // Tiempo de fin
    double total_time = chrono::duration<double, milli>(end - start).count();
    clog << total_time << " milliseconds." << endl;

    writeFile(x, p, input_file);
  } else {
    cout << "Not enough arguments.\nUsage: $ ./main <algorithm> <input file> <p> <(opt)niter> <(opt)eps>" << endl;
  }
  return 0;
}
