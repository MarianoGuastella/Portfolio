
#include "ColaPrior.h"

template<class T>
ColaPrior<T>::ColaPrior() : tam_(0){

}

template<class T>
int ColaPrior<T>::tam() const {
	return tam_;
}

template<class T>
void ColaPrior<T>::encolar(const T& elem) {
	tam_++;
	heap_.push_back(elem);
	siftUp(heap_, tam_ - 1);
}

template<class T>
const T& ColaPrior<T>::proximo() const {
	return heap_[0];
}

template<class T>
void ColaPrior<T>::desencolar() {
	swap(heap_[0], heap_[tam_ - 1]);
	heap_.pop_back();
    tam_--;
	siftDown(heap_, 0);
}

template<class T>
ColaPrior<T>::ColaPrior(const vector<T>& elems) {
    heap_ = elems;
    for(int i = (int)elems.size()/2 ; i >= 0; i--){
        siftDown(heap_, i);
    }
}

template<class T>
void ColaPrior<T>::siftUp(vector<T>& v, int i){
    int padre = (int)(i - 1)/2;
    if (i != 0 && v[i] > v[padre]){
        swap(v[i], v[padre]);
        siftUp(v, padre);
    }
}

template<class T>
void ColaPrior<T>::siftDown(vector<T>& v, int i){
    if(i*2 + 1 < tam_){
        if(i*2 + 2 < tam_){
            int hijo_izq = i*2 + 1;
            int hijo_der = i*2 + 2;
            T m = max(v[hijo_izq], v[hijo_der]);
            int ind_m;
            if (v[hijo_izq] < v[hijo_der]){
                ind_m = i*2 + 2;
            }
            else {
                ind_m = i*2 + 1;
            }
            if(m > v[i]){
                swap(v[i], v[ind_m]);
                siftDown(v, ind_m);
            }
        }
        else {
            int hijo_izq = i*2 + 1;
            T m = hijo_izq;
            int ind_m = hijo_izq;
            if(m > v[i]) {
                swap(v[i], v[ind_m]);
                siftDown(v, ind_m);
            }
        }
    }
}