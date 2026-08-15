#include "Camera.h"

Camera::Camera() {
    this->startRow = 0;
    this->startCol = 0;
}

Camera::~Camera() {}

void Camera::moverArriba(int n) {
    this->startRow -= n;
    if (this->startRow < 0) this->startRow = 0; //validar
}

void Camera::moverAbajo(int n) {
    this->startRow += n;
    if (this->startRow > tam_map - tam_ventana) // >20 ?
        this->startRow = tam_map - tam_ventana;
}

void Camera::moverIzquierda(int n) {
    this->startCol -= n;
    if (this->startCol < 0) this->startCol = 0;
}

void Camera::moverDerecha(int n) {
    this->startCol += n;
    if (this->startCol > tam_map - tam_ventana)
        this->startCol = tam_map - tam_ventana;
}

int Camera::get_fila_inicio() const {
    return startRow;
}

int Camera::get_columna_inicio() const {
    return startCol;
}

Camera Camera::operator+(const Camera& other) const {
    Camera resultado;
    resultado.startRow = this->startRow + other.startRow;
    resultado.startCol = this->startCol + other.startCol;
    return resultado;
} //p.e

ostream& operator<<(ostream& os, const Camera& c) {
    os << c.startRow << " " << c.startCol;
    return os;
}
