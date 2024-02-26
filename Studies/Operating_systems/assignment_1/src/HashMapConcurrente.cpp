#ifndef CHM_CPP
#define CHM_CPP

#include <iostream>
#include <fstream>
#include <pthread.h>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    int bucket = hashIndex(clave);
    mutexBucket[bucket].lock();
    ListaAtomica<hashMapPair> *items = tabla[bucket];
    ListaAtomica<hashMapPair>::Iterador iteradorLista = items->crearIt();
    while (iteradorLista.haySiguiente()) {
        if (iteradorLista.siguiente().first == clave) {
            iteradorLista.siguiente().second += 1;
            mutexBucket[bucket].unlock();
            return;
        }
        iteradorLista.avanzar();
    }
    items->insertar(*(new hashMapPair(clave, 1)));
    mutexBucket[bucket].unlock();
}

std::vector<std::string> HashMapConcurrente::claves() {
    std::vector<std::string> claves;
    std::string actual;
    mutexClaves.lock();
    for(unsigned int i = 0; i < cantLetras; i++) { mutexBucket[i].lock(); }
    for(unsigned int i = 0; i < cantLetras; i++){
        ListaAtomica<hashMapPair> *items = tabla[i];
        ListaAtomica<hashMapPair>::Iterador iteradorLista = items->crearIt();
        while (iteradorLista.haySiguiente()) {
            actual = iteradorLista.siguiente().first;
            claves.push_back(actual);
            iteradorLista.avanzar();
        }
        mutexBucket[i].unlock();
    }
    mutexClaves.unlock();
    return claves;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    int bucket = hashIndex(clave);
    mutexBucket[bucket].lock();
    ListaAtomica<hashMapPair> *items = tabla[bucket];
    for (auto it = items->crearIt(); it.haySiguiente(); it.avanzar()) {
        if(it.siguiente().first == clave) {
            int valor = it.siguiente().second;
            mutexBucket[bucket].unlock();
            return valor;
        }
    }
    return 0;
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;
    mutexMaximo.lock();
    for(unsigned int i = 0; i < cantLetras; i++) { mutexBucket[i].lock(); }
    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (
            auto it = tabla[index]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ) {
            if (it.siguiente().second > max->second) {
                max->first = it.siguiente().first;
                max->second = it.siguiente().second;
            }
        }
        mutexBucket[index].unlock();
    }
    mutexMaximo.unlock();
    return *max;
}

struct args_struct {
    int bucketActual;
    ListaAtomica<hashMapPair> *maximosBuckets;
    HashMapConcurrente *context;
};

hashMapPair maximoLista(ListaAtomica<hashMapPair> *lista) {
    hashMapPair *max = new hashMapPair();
    max->second = 0;
    for (auto it = lista->crearIt(); it.haySiguiente(); it.avanzar()) {
        if (it.siguiente().second > max->second) {
            max->first = it.siguiente().first;
            max->second = it.siguiente().second;
        }
    }
    return *max;
}

void *HashMapConcurrente::maximoThread(void* arguments) {
    struct args_struct *args = (struct args_struct *)arguments;
    while(args->bucketActual < 26) {
        args->context->mutexMaxCounter.lock();
        int miBucket = args->bucketActual;
        args->bucketActual++;
        args->context->mutexMaxCounter.unlock();
        if (!(miBucket < 26)) { break; }

        ListaAtomica<hashMapPair> *bucket = args->context->tabla[miBucket];
        hashMapPair max = maximoLista(bucket);
        args->context->mutexBucket[miBucket].unlock();
        if (!max.first.empty()) {
            args->maximosBuckets->insertar(max);
        }
    }
    return nullptr;
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {
    // Completar (Ejercicio 3)
    mutexMaximo.lock();

    ListaAtomica<hashMapPair> *maximosBuckets = new ListaAtomica<hashMapPair>;
    struct args_struct *args = new args_struct;
    args->bucketActual = 0;
    args->maximosBuckets = maximosBuckets;
    args->context = this;

    std::vector<pthread_t> threads;

    for(unsigned int i = 0; i < cantLetras; i++) { mutexBucket[i].lock(); }

    int pthread_create_retry = 0;

    while(threads.size() < cantThreads) {
        if (pthread_create_retry > 3) { break; }

        pthread_t ptid;
        if (pthread_create(&ptid, NULL, maximoThread, (void *)args) == 0) {
            threads.push_back(ptid);
            pthread_create_retry = 0;
        } else {
            pthread_create_retry++;
        }
    }

    for (pthread_t thread : threads) {
        pthread_join(thread, NULL); // SEGMENTATION FAULT ACA
    }

    hashMapPair max = maximoLista(maximosBuckets);
    mutexMaximo.unlock();
    // !!!!!! hay que borrar cada PAR dentro de maximosBuckets tambien
    delete maximosBuckets;
    delete args;
    return max;
}

#endif


