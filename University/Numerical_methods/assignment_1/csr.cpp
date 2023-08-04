#include "csr.h"

Csr::Csr(int x, int y): n(x), m(y), a(vector<double>()), ja(vector<int>()), ia(vector<int>(x + 1, 0)) {}

int Csr::rows() {
  return n;
}

int Csr::columns() {
  return m;
}

double Csr::get(int i, int j) {
  int start = ia[i];
  int end = ia[i+1];
  for (int k = start; k < end; k++) {
    if (j == ja[k]) {
      return a[k];
    }
  }
  return 0;
}

void Csr::ia_inc(int i) {
  for (int k = i + 1; k < n + 1; k++) {
    ia[k] += 1;
  }
}

void Csr::ia_dec(int i) {
  for (int k = i + 1; k < n + 1; k++) {
    ia[k] -= 1;
  }
}

void Csr::set(int i, int j, double v) {
  if (i < n && j < m) {
    int index = ia[i];
    int col = -1;
    for (; index < ia[i+1]; index++) {
      col = ja[index];
      if (col >= j) {
        break;
      }
    }
    if (col != j) {
      if (v != 0) { // contemplar abs(v) mayor a un epsilon?
        insert(index, i, j, v);
      }
    } else if (v == 0) {
      erase(index, i);
    } else {
      a[index] = v;
    }
  } else {
    cout << "Indices invalidos." << i << ' ' << j << endl;
  }
}

void Csr::insert(int index, int i, int j, double v) {
  if (a.empty()) {
    a.push_back(v);
    ja.push_back(j);
  } else {
    a.insert(a.begin() + index, v);
    ja.insert(ja.begin() + index, j);
  }
  ia_inc(i);
}

void Csr::erase(int index, int i) {
  a.erase(a.begin() + index);
  ja.erase(ja.begin() + index);
  ia_dec(i);
}

void Csr::scalar(double p) {
  for (int l = 0; l < (int) a.size(); l++) {
    a[l] = a[l]*p;
  }
}

void Csr::view() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << get(i, j) << ' ';
    }
    cout << endl;
  }
}
