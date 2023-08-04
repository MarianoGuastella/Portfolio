#ifndef CSR_H
#define CSR_H

#include <iostream>
#include <vector>
using namespace std;

class Csr {
  private:
    int n;
    int m;
    vector<double> a;
    vector<int> ja;
    vector<int> ia;

    void ia_inc(int i);
    void ia_dec(int i);
    void insert(int index, int i, int j, double v);
    void erase(int index, int i);
  public:
    Csr(int x, int y);
    int rows();
    int columns();
    double get(int i, int j);
    void set(int i, int j, double v);
    void scalar(double p);
    void view();
};

#endif