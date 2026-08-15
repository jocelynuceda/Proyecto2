#ifndef TOWER_H
#define TOWER_H

#include <iostream>
using namespace std;

class Tower {
private:
    int fila;
    int columna;
    int danio;
    int rango;
    int cantidadDisparos;
    int disparosUsados;
    bool activa;
    int numero;

    static int contador;

public:
    Tower(int fila, int columna);
    Tower(int fila, int columna, int danio);
    Tower(int fila, int columna, int danio, int rango, int disparosMax);
    ~Tower();

    bool puedeDisparar() const;
    void disparar();
    void configurar(int danio, int rango, int disparosMax);

    int getFila() const;
    int getColumna() const;
    int getRango() const;
    int getDanio() const;
    int getDisparosUsados() const;
    int getCantidadDisparos() const;
    int getNumero() const;
    bool getActiva() const;

    bool operator==(const Tower& otra) const;
    friend ostream& operator<<(ostream& os, const Tower& t);

    friend class Game;
};

#endif
