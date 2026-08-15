#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Map.h"
#include "Camera.h"
#include "Enemy.h"
#include "Tower.h"
using namespace std;

class Game {
private:
    Map* mapa;
    Camera* camara;
    vector<Enemy*> enemigos;
    vector<Tower*> torres;
    int dinero;
    bool iniciado;
    bool huboOleada;

    static const int COSTO_TORRE = 100;
    static const int RECOMPENSA = 50;

    void limpiar();
    string restaurarCelda(int filaInt, int colInt) const;
    void mostrarVentana_impl() const;

public:
    Game();
    ~Game();

    bool iniciarJuego(const string& archivoMapa = "mapa.txt");
    void mostrarVentana();
    void moverCamara(const string& direccion, int n);
    void colocarTorre(int x, int y, int danio = 1, int disparos = 1);
    void generarEnemigos(int vida = 1);
    void moverEnemigos();
    void atacarEnemigos();
    void mostrarEstado();
    void guardarJuego(const string& archivo);
    bool cargarJuego(const string& archivo);

    bool estaIniciado() const;
    bool baseDestruida() const;
    bool todosEnemigosEliminados() const;
};

#endif
