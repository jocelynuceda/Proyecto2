#include "Camera.h"

Camera::Camera() {
    this->startRow = 0;
    this->startCol = 0;
}

Camera::~Camera() {}

void Camera::mover(int& eje, int n) {
    eje += n;
    if (eje < 0) eje = 0;
    if (eje > tam_map - tam_ventana) eje = tam_map - tam_ventana;
}

void Camera::moverArriba(int n) { mover(startRow, -n); }
void Camera::moverAbajo(int n) { mover(startRow, n); }
void Camera::moverIzquierda(int n) { mover(startCol, -n); }
void Camera::moverDerecha(int n) { mover(startCol, n); }

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
}

ostream& operator<<(ostream& os, const Camera& c) {
    os << c.startRow << " " << c.startCol;
    return os;
}
