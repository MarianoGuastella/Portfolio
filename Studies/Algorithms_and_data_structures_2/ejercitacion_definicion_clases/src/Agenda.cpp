
#include "Agenda.h"
#include <vector>
#include <iostream>

using uint = unsigned int;


uint dias_en_mes(uint mes) {
    uint dias[] = {
            // ene, feb, mar, abr, may, jun
            31, 28, 31, 30, 31, 30,
            // jul, ago, sep, oct, nov, dic
            31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia() and this->mes() == o.mes();
    return igual_dia;
}

Fecha::Fecha(int mes, int dia) : mes_(mes), dia_(dia) {

}

int Fecha::mes() {
    return mes_;
}

int Fecha::dia() {
    return dia_;
}

void Fecha::incrementar_dia() {
    if (dia_ < dias_en_mes(mes_)) {
        dia_ += 1;
    }
    else {
        dia_ = 1;
        mes_ += 1;
    }
}

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia() << "/" << f.mes();
    return os;
}


Horario::Horario(uint hora, uint min) : hora_(hora), min_(min){

};

uint Horario::hora() {
    return hora_;
}

uint Horario::min() {
    return min_;
}

bool Horario::operator==(Horario o) {
    bool mismo_horario = hora() == o.hora() and min() == o.min();
    return mismo_horario;
}

ostream& operator<<(ostream& os, Horario h){
    os << h.hora() << ":" << h.min();
    return os;
}

bool Horario::operator<(Horario o) {
    if (hora() <= o.hora()){
        if (hora() == o.hora()){
            return min() < o.min();
        }
        return true;
    }
    return false;
}


Recordatorio::Recordatorio(Fecha f, Horario h, string mensaje) : fecha_(f), horario_(h), mensaje_(mensaje) {

};

string Recordatorio::mensaje() {
    return mensaje_;
}

Fecha Recordatorio::fecha() {
    return fecha_;
}

Horario Recordatorio::horario() {
    return horario_;
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.mensaje() << " @ " << r.fecha() << " "<< r.horario();
    return os;
}


Agenda::Agenda(Fecha fecha_inicial) : hoy_(Fecha(fecha_inicial)), agenda_(vector<Recordatorio>()){

}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    agenda_.push_back(rec);
}

void Agenda::incrementar_dia() {
    hoy_.incrementar_dia();
}

Fecha Agenda::hoy() {
    return hoy_;
}

vector<Recordatorio> Agenda::recordatorios_de_hoy() {
    vector<Recordatorio> res;
    for (Recordatorio rec : agenda_) {
        if (hoy_ == rec.fecha()) {
            res.push_back(rec);
        }
    }
    if (res.size() == 0){
        return vector<Recordatorio>();
    }
    vector<Recordatorio> aux;
    Horario h(23,59);
    for (int i = 0 ; i < res.size() ; i++){
        int posicion = 0;
        for (int j = 0 ; j < res.size(); j++){
            if (res[j].horario() < h){
                h = Horario(res[j].horario());
                posicion = j;
            }
        }
        aux.push_back(res[posicion]);
        res.erase(res.begin() + posicion);
    }
    aux.push_back(res[0]);
    return aux;
}

ostream& operator<<(ostream& os, Agenda a) {
    os << a.hoy() << endl << "=====" << endl;
    for (Recordatorio r : a.recordatorios_de_hoy()){
        os << r << endl;
    }
    return os;
}