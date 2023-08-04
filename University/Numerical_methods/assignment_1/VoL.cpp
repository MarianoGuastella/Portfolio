#include "VoL.h"


VoL::VoL(int x, int y) : n(x), m(y), vectorOfRows(vector<list<pair<int, double>>>(x, list<pair<int, double>>())) {}

int VoL::rows() {
  return n;
}

int VoL::columns() {
  return m;
}

const double VoL::EPS = 0.000000001;

double VoL::get(int i, int j) {
  list<pair<int, double>> row_i = vectorOfRows[i];
  
  for (list<pair<int, double>>::iterator it = row_i.begin(); it != row_i.end(); it++) {
    if (it->first == j) {
      return it->second;
    }
    else if (it->first > j) {
      break;
    }
  }
  return 0;
}


void VoL::set(int i, int j, double v) {
  if (i < n && j < m) {
    if (abs(v) > EPS) {
      if (vectorOfRows[i].empty()) {
        vectorOfRows[i].push_back(pair<int, double>(j, v));
      } 
      else {
        for (list<pair<int, double>>::iterator it = vectorOfRows[i].begin(); it != vectorOfRows[i].end(); it++) {
          if (it->first == j) {
            it->second = v;
            return;
          }
          else if (it->first > j) {
            vectorOfRows[i].insert(it, pair<int, double>(j, v));
            return;
          }
        }
      }
    }
    else {
      for (list<pair<int, double>>::iterator it = vectorOfRows[i].begin(); it != vectorOfRows[i].end(); it++) {
        if (it->first == j) {
          vectorOfRows[i].erase(it);
          return;
        }
      }
    }
  } else { cout << "Indices invalidos." << i << ' ' << j << endl; }
}

void VoL::view() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << get(i, j) << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

void VoL::gaussianElimination8000EXTREME() {
  for (int i = 0; i < n-1; i++) {
    for (int j = i + 1; j < n; j++) {
      double value = get(j, i);
      if (value != 0) {
        double factor = (value / get(i, i));
        list<pair<int, double>>::iterator itJ = vectorOfRows[j].begin();
        list<pair<int, double>>::iterator itI = vectorOfRows[i].begin();
        while (itJ != vectorOfRows[j].end()) {
          if (itJ->first > itI->first) {
            if (abs(-factor * itI->second) > EPS) {
              vectorOfRows[j].insert(itJ, pair<int,double>(itI->first, -factor * itI->second));
            }
            itI++;
          }
          else if (itJ->first < itI->first) {
            itJ++;
          }
          else {
            if (abs(itJ->second -(factor * itI->second)) > EPS) {
              itJ->second = itJ->second - (factor * itI->second);
              itJ++;
            }
            else {
              itJ = vectorOfRows[j].erase(itJ);
            }
            
            itI++;
          }
        }
      }
    }
    cout << "Columna: " << i << endl;
  }
}

VoL VoL::csr_to_VoL(Csr& csrMatrix) {
    int rows = csrMatrix.rows();
    int columns = csrMatrix.columns();
    VoL VoLMatrix = VoL(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double v = csrMatrix.get(i, j);
            if (v != 0) {
                VoLMatrix.vectorOfRows[i].push_back(pair<int, double>(j, v));
            }
        }
    }
    return VoLMatrix;


    //version naive
    /*
    int rows = csrMatrix.rows();
    int columns = csrMatrix.columns();
    VoL VoLMatrix = VoL(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
           double v = csrMatrix.get(i, j);
           VoLMatrix.set(i, j, v);
        }
    }
    return VoLMatrix;*/
}

vector<double> VoL::TriangulatedMatrixSolution() {
    vector<double> res = vector<double>(rows(), 0);
    for (int i = rows() - 1; i >= 0; i--) { // itero filas
        res[i] = (get(i, columns() - 1) - behindDiagonalRowSum(i, res)) / get(i, i);
    }
    return res;
}

double VoL::behindDiagonalRowSum(int index, vector<double> xs) {
    double sum = 0;
    for (int j = index + 1; j < rows(); j++) {
        sum += get(index, j) * xs[j];
    }
    return sum;
}
