#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include "CargarArchivos.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        hashMap.incrementar(palabraActual);
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

struct args_struct {
    std::vector<std::string> filePaths;
    HashMapConcurrente *hashMap;
    std::mutex *mutexFiles;
    int fileActual;
};

void* cargarArchivoStruct(void* argumentos){
    struct args_struct *args = (struct args_struct *)argumentos;
    while(args->fileActual < (int)(args->filePaths.size())) {
        args->mutexFiles->lock();
        int file = args->fileActual;
        args->fileActual++;
        args->mutexFiles->unlock();
        std::string filePath = args->filePaths[file];
        cargarArchivo(*(args->hashMap), filePath);
    }
    return nullptr;
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    std::vector<pthread_t> threads;
    std::mutex mutexFiles;
    struct args_struct *args = new struct args_struct;
    args->mutexFiles = &mutexFiles;
    args->fileActual= 0;
    args->filePaths = filePaths;
    args->hashMap = &hashMap;

    int pthread_create_retry = 0;

    while(threads.size() < cantThreads) {
        if (pthread_create_retry > 3) { break; }

        pthread_t ptid;
        if (pthread_create(&ptid, NULL, cargarArchivoStruct, (void *)args) == 0) {
            threads.push_back(ptid);
            pthread_create_retry = 0;
        } else {
            pthread_create_retry++;
        }
    }
    for (pthread_t thread : threads) {
        pthread_join(thread, NULL); // SEGMENTATION FAULT ACA
    }
}

#endif
