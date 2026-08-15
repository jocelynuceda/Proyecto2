#ifndef CAMERA_H
#define CAMERA_H

#include <ostream>
using namespace std;

class Camera {
private:
    int startRow;
    int startCol;

    void mover(int& eje, int n);

public:
    int tam_map = 40;
    int tam_ventana = 20;

    Camera();
    ~Camera();

    void moverArriba(int n);
    void moverAbajo(int n);
    void moverIzquierda(int n);
    void moverDerecha(int n);

    int get_fila_inicio() const;
    int get_columna_inicio() const;

    Camera operator+(const Camera& other) const;
    friend ostream& operator<<(ostream& os, const Camera& c);

    friend class Map;
    friend class Game;
};

#endif
