#include <utility>

using namespace std;

using uint = unsigned int;

// Ejercicio 15

// Juego

using Pos = pair<int, int>;

char ARRIBA = '^';
char ABAJO = 'v'; 
char DERECHA = '<';
char IZQUIERDA = '>';

class Juego {
  // Completar
public:
    Juego(uint casilleros, Pos pos_inicial);
    Pos posicion_jugador();
    uint turno_actual();
    void mover_jugador(char dir);
    void ingerir_pocion(uint movimientos, uint turnos);
private:
    int casilleros_;
    int turno_;
    Pos posicion_;
    int movimientos_pocion_;
    vector<pair<uint, uint>> turnos_pocion_;
};

Juego::Juego(uint casilleros, Pos pos_inicial) : casilleros_(casilleros), turno_(0), posicion_(pos_inicial), movimientos_pocion_(1), turnos_pocion_() {

};

Pos Juego::posicion_jugador() {
    return posicion_;
}

uint Juego::turno_actual() {
    return turno_;

}

void Juego::mover_jugador(char dir) {

}

void Juego::ingerir_pocion(uint movimientos, uint turnos) {
    movimientos_pocion_ += movimientos;
    turnos_pocion_.push_back(make_pair(movimientos, turnos));
};
