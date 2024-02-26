
#ifndef AGENDA_H
#define AGENDA_H

#include <iostream>
#include <vector>

using namespace std;

using uint = unsigned int;

class Fecha {
public:
    Fecha(int mes, int dia);
    int mes();
    int dia();
    bool operator==(Fecha o);
    void incrementar_dia();
private:
    int mes_;
    int dia_;
};

class Horario{
public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator==(Horario o);
    bool operator<(Horario o);
private:
    uint hora_;
    uint min_;
};

class Recordatorio{
public:
    Recordatorio(Fecha f, Horario h, string mensaje);
    string mensaje();
    Fecha fecha();
    Horario horario();

private:
    string mensaje_;
    Fecha fecha_;
    Horario horario_;
};

class Agenda {
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    vector<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();
private:
    vector<Recordatorio> agenda_;
    Fecha hoy_;
};

#endif
