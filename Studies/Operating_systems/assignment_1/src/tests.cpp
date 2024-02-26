#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "../src/ListaAtomica.hpp"
#include "../src/HashMapConcurrente.hpp"
#include "../src/CargarArchivos.hpp"

using namespace std;

const int REPEAT = 100;

double ms_max(HashMapConcurrente &hM) {
    double sum = 0.0;

    for (int i = 0; i < REPEAT; i++) {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        hM.maximo();
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    }
    return sum/REPEAT;
}

double ms_maxP(HashMapConcurrente &hM, int cantThreads) {
    double sum = 0.0;

    for (int i = 0; i < REPEAT; i++) {
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        hM.maximoParalelo(cantThreads);
        clock_gettime(CLOCK_MONOTONIC, &end);
        sum += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    }
    return sum/REPEAT;
}

int main(int argc, char* argv[]){
    if (argc> 5){
        // Argument parsing
        string loadFunc(argv[1]);
        int loadThreads = atoi(argv[2]);
        string maxFunc(argv[3]);
        int maxThreads = atoi(argv[4]);
        vector<string> filePaths = {};
        for (int i = 5; i < argc; i++) {
          string filePath(argv[i]);
          filePaths.push_back(filePath);
        }

        struct timespec start, end;
        HashMapConcurrente hM;

        if (loadFunc == "cargarArchivo"){
            clock_gettime(CLOCK_MONOTONIC, &start);
            cargarArchivo(hM, filePaths[0]);
            clock_gettime(CLOCK_MONOTONIC, &end);
            double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            cout << "Tiempo de carga: " << elapsedTime << endl;
        }
        else {
            clock_gettime(CLOCK_MONOTONIC, &start);
            cargarMultiplesArchivos(hM, loadThreads , filePaths); 
            clock_gettime(CLOCK_MONOTONIC, &end);
            double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
            cout << "Tiempo de carga: " << elapsedTime << endl;
        }
        if (maxFunc == "maximo"){
            double time_avg = ms_max(hM);
            cout <<"Tiempo de procesamiento: " << time_avg << endl;
        }
        else {
            if (maxThreads == 0) {
                for (int i = 1; i < 30; i++) {
                    cout << "Thread count: " << i << endl;
                    double time_avg = ms_maxP(hM, i);
                    cout <<"Tiempo de procesamiento: " << time_avg << endl << endl;
                }
            } else {
                double time_avg = ms_maxP(hM, maxThreads);
                cout <<"Tiempo de procesamiento: " << time_avg << endl;
            }
        }
    }
    else{
        cout << "Not enough arguments: cargarArchivo or cargarMultiplesArchivos, threads(0 if no threads xD), maximo or maximoParalelo, threads (0 if no threads xD), data file/s\nSee README!" << endl;
    }
    return 0;
}
