#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
using namespace std;

class Enemy {
private:
    int salud;
    int posRuta;
    bool vivo;

public:
    Enemy(int posInicio = 0, int hp = 1);
    ~Enemy();

    int get_salud() const;
    int get_pos_ruta() const;
    bool get_vivo() const;

    bool operator==(const Enemy& other) const;
    friend ostream& operator<<(ostream& os, const Enemy& e);

    friend class Game;
};

#endif
