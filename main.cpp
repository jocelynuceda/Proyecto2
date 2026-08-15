#include <iostream>
#include <sstream>
#include "Game.h"

int main() {
    Game juego;
    string comando;
    bool juegoTerminado = false;

    while (!juegoTerminado) {
        cout << "$ ";
        if (!(cin >> comando)) break;

        if (comando == "init") {
            juego.iniciarJuego("mapa.txt");
        }
        else if (comando == "load") {
            string archivo;
            cin >> archivo;
            juego.cargarJuego(archivo);
        }
        else if (comando == "exit") {
            juegoTerminado = true;
        }
        else if (!juego.estaIniciado()) {
            cout << "Primero debes iniciar el juego con: init" << endl;
        }
        else if (comando == "map") {
            juego.mostrarVentana();
            cout << endl;
        }
        else if (comando == "up" || comando == "down" ||
                 comando == "left" || comando == "right") {
            int n;
            cin >> n;
            juego.moverCamara(comando, n);
        }
        else if (comando == "place") {
            int x = 0, y = 0, danio = 1, disparos = 1;
            string linea;
            getline(cin, linea);
            istringstream ss(linea);
            int vals[4], leidos = 0;
            while (leidos < 4 && ss >> vals[leidos]) leidos++;
            if (leidos >= 2) { x = vals[0]; y = vals[1]; }
            if (leidos >= 3) danio = vals[2];
            if (leidos >= 4) disparos = vals[3];
            juego.colocarTorre(x, y, danio, disparos);
        }
        else if (comando == "wave") {
            int vida = 1;
            string linea;
            getline(cin, linea);
            istringstream ss(linea);
            ss >> vida;
            juego.generarEnemigos(vida);
        }
        else if (comando == "status") {
            juego.mostrarEstado();
        }
        else if (comando == "next") {
            juego.moverEnemigos();
            juego.atacarEnemigos();

            if (juego.baseDestruida()) {
                cout << "Estado actualizado" << endl;
                juego.mostrarEstado();
                cout << "Game over - La base fue destruida" << endl;
                juegoTerminado = true;
            }
            else if (juego.todosEnemigosEliminados()) {
                cout << "Estado actualizado" << endl;
                juego.mostrarEstado();
                cout << "Ganaste - Todos los enemigos fueron eliminados" << endl;
                juegoTerminado = true;
            }
            else {
                cout << "Estado actualizado" << endl;
                juego.mostrarEstado();
            }
        }
        else if (comando == "save") {
            string archivo;
            cin>>archivo;
            juego.guardarJuego("../" + archivo + ".txt");
            juegoTerminado=true;
        }
        else {
            cout<<"Comando no reconocido" << endl;
        }
    }

    return 0;
}