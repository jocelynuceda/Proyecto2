#include "Tower.h"

int Tower::contador = 0;

Tower::Tower(int fila, int columna) {
    this->fila = fila;
    this->columna = columna;
    this->danio = 1;
    this->rango = 2;
    this->cantidadDisparos = 1;
    this->disparosUsados = 0;
    this->activa = true;
    this->numero = ++contador;
}

Tower::Tower(int fila, int columna, int danio) {
    this->fila = fila;
    this->columna = columna;
    this->danio = danio;
    this->rango = 2;
    this->cantidadDisparos = 1;
    this->disparosUsados = 0;
    this->activa = true;
    this->numero = ++contador;
}

Tower::Tower(int fila, int columna, int danio, int rango, int disparosMax) {
    this->fila = fila;
    this->columna = columna;
    this->danio = danio;
    this->rango = rango;
    this->cantidadDisparos = disparosMax;
    this->disparosUsados = 0;
    this->activa = true;
    this->numero = ++contador;
}

Tower::~Tower() {}

bool Tower::puedeDisparar() const {
    return activa && disparosUsados < cantidadDisparos;
}

void Tower::disparar() {
    if (puedeDisparar()) disparosUsados++;
}

void Tower::configurar(int danio, int rango, int disparosMax) {
    this->danio = danio;
    this->rango = rango;
    this->cantidadDisparos = disparosMax;
}

int Tower::getFila() const { return fila; }
int Tower::getColumna() const { return columna; }
int Tower::getRango() const { return rango; }
int Tower::getDanio() const { return danio; }
int Tower::getDisparosUsados() const { return disparosUsados; }
int Tower::getCantidadDisparos() const { return cantidadDisparos; }
int Tower::getNumero() const { return numero; }
bool Tower::getActiva() const { return activa; }

bool Tower::operator==(const Tower& otra) const {
    return fila == otra.fila && columna == otra.columna;
}

ostream& operator<<(ostream& os, const Tower& t) {
    os << t.fila << " " << t.columna << " " << t.numero << " " << t.disparosUsados;
    return os;
}
