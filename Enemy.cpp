#include "Enemy.h"

Enemy::Enemy(int posInicio, int hp) {
    this->salud = hp;
    this->posRuta = posInicio;
    this->vivo = true;
}

Enemy::~Enemy() {}

int Enemy::get_salud() const { return salud; }
int Enemy::get_pos_ruta() const { return posRuta; }
bool Enemy::get_vivo() const { return vivo; }

bool Enemy::operator==(const Enemy& other) const {
    return posRuta == other.posRuta;
}

ostream& operator<<(ostream& os, const Enemy& e) {
    os << e.posRuta << " " << e.salud << " " << (e.vivo ? 1 : 0);
    return os;
}
