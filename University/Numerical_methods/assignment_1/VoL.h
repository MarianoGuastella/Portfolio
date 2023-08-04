#ifndef VOL_H
#define VOL_H

#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include "csr.h"

using namespace std;

class VoL {
  private:
    int n;
    int m;
    vector<list<pair<int, double>>> vectorOfRows;
    static const double EPS;
    double behindDiagonalRowSum(int index, vector<double> xs);

  public:
    VoL(int x, int y);
    int rows();
    int columns();
    double get(int i, int j);
    void set(int i, int j, double v);
    void view();
    void gaussianElimination8000EXTREME();
    VoL static csr_to_VoL(Csr& csrMatrix);
    vector<double> TriangulatedMatrixSolution();
};

#endif