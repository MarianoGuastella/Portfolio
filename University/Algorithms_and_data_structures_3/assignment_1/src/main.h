
#ifndef TP1_MAIN_H
#define TP1_MAIN_H
#include <vector>

using namespace std;

int npm_fuerza_bruta(const vector<pair<int,int>> &L, const int &M, int i = 0, vector<int> negocios = {});

int npm_backtracking(const vector<pair<int,int>> &L, const int &M, int b_restante, int i = 0, int b = 0, int m = 0);

int npm_dinamica(const vector<pair<int,int>> &L, const int &M, int i = 0, int b = 0, int m = 0);

#endif //TP1_MAIN_H