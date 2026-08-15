#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include <functional>

using namespace std;

const int tamanio_real = 80;
const int tamanio_visual = 40;

class Map {
private:
    vector<vector<string>> mapa;
    vector<int> ruta_fila;
    vector<int> ruta_col;

    static void recorrerSegmento(int fi, int fj, int ti, int tj, const function<void(int, int)>& visitar);

    void buildPath(const vector<int>& wpFila, const vector<int>& wpCol);
    void buildEnemyRoute(const vector<int>& wpFila, const vector<int>& wpCol);

public:
    Map();
    ~Map();

    void init(const string& archivo);

    void saveGrid(ofstream& out) const;
    void cargarMapa(ifstream& in);
    void loadFromFile(const string& archivo);

    string getCell(int fila, int col);
    void setCell(int fila, int col, const string& valor);

    int getCeldasRuta();
    int getRutaFila(int idx);
    int getRutaCol(int idx);

    string celdaVacia(int fila, int col);

    bool esPosicionValida(int x, int y) const;
};

#endif
