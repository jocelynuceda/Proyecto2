#include "Map.h"
#include <iostream>
#include <fstream>
using namespace std;

Map::Map() {
}

Map::~Map() {
}

void Map::init(const string& archivo) {
    (void)archivo;

    mapa.assign(tamanio_real, vector<string>(tamanio_real));
    for (int i = 0; i < tamanio_real; i++) {
        for (int j = 0; j < tamanio_real; j++) {
            if (i % 2 == 0 and j % 2 == 0)
                mapa[i][j] = "+";
            else
                mapa[i][j] = " ";
        }
    }

    vector<int> camino_fila = { 1, 2, 2, 9, 9, 9, 9, 18, 18, 27, 27, 40, 40 };
    vector<int> camino_col  = { 1, 1, 4, 4, 7, 9, 25, 25, 5, 5, 37, 37, 40 };
    buildPath(camino_fila, camino_col);

    vector<int> enem_fila = { 1, 1, 8, 8, 19, 19, 26, 26, 39, 39 };
    vector<int> enem_col  = { 2, 5, 5, 26, 26, 6, 6, 38, 38, 40 };
    buildEnemyRoute(enem_fila, enem_col);

    mapa[0][0] = "I";
    mapa[78][78] = "B";
}

void Map::saveGrid(ofstream& out) const {
    for (int i = 0; i < tamanio_real; i++) {
        for (int j = 0; j < tamanio_real; j++) {
            out << mapa[i][j];
            if (j < tamanio_real - 1) out << "|";
        }
        out << "\n";
    }
}

void Map::cargarMapa(ifstream& in) {
    mapa.assign(tamanio_real, vector<string>(tamanio_real));

    string linea;
    int i = 0;
    while (i < tamanio_real and getline(in, linea)) {
        if (linea.empty()) continue;
        int j = 0; string celda;
        for (char ch : linea) {
            if (ch == '|') { mapa[i][j++] = celda; celda.clear(); }
            else { celda += ch; }
        }
        if (j < tamanio_real) mapa[i][j] = celda;
        i++;
    }
}

void Map::loadFromFile(const string& archivo) {
    ifstream in(archivo);
    if (!in.is_open()) { cout << "operacion no valida" << endl; return; }
    cargarMapa(in);
    in.close();
}

void Map::recorrerSegmento(int fi, int fj, int ti, int tj, const function<void(int, int)>& visitar) {
    int di = 0;
    if (ti > fi) di = 1;
    else if (ti < fi) di = -1;

    int dj = 0;
    if (tj > fj) dj = 1;
    else if (tj < fj) dj = -1;

    int i = fi, j = fj;
    while (i != ti or j != tj) {
        visitar(i, j);
        i += di; j += dj;
    }
}

void Map::buildPath(const vector<int>& wpFila, const vector<int>& wpCol) {
    int n = wpFila.size();

    for (int k = 0; k < n - 1; k++) {
        int fi = (wpFila[k] - 1) * 2, fj = (wpCol[k] - 1) * 2;
        int ti = (wpFila[k+1] - 1) * 2, tj = (wpCol[k+1] - 1) * 2;
        recorrerSegmento(fi, fj, ti, tj, [this](int i, int j) { mapa[i][j] = "#"; });
    }
    mapa[(wpFila[n-1] - 1) * 2][(wpCol[n-1] - 1) * 2] = "#";
}

void Map::buildEnemyRoute(const vector<int>& wpFila, const vector<int>& wpCol) {
    int n = wpFila.size();
    ruta_fila.clear();
    ruta_col.clear();

    for (int k = 0; k < n - 1; k++) {
        recorrerSegmento(wpFila[k], wpCol[k], wpFila[k+1], wpCol[k+1], [this](int i, int j) {
            ruta_fila.push_back((i - 1) * 2);
            ruta_col.push_back((j - 1) * 2);
        });
    }
    ruta_fila.push_back((wpFila[n-1] - 1) * 2);
    ruta_col.push_back((wpCol[n-1] - 1) * 2);
}

string Map::getCell(int fila, int col) {
    return mapa[fila][col];
}

void Map::setCell(int fila, int col, const string& v) {
    mapa[fila][col] = v;
}

int Map::getCeldasRuta() {
    return ruta_fila.size();
}
int Map::getRutaFila(int idx) {
    return ruta_fila[idx];
}
int Map::getRutaCol(int idx) {
    return ruta_col[idx];
}

bool Map::esPosicionValida(int x, int y) const {
    if (x < 1 or x > tamanio_visual or y < 1 or y > tamanio_visual)
        return false;

    int fi = (x - 1) * 2, fj = (y - 1) * 2;
    string c = mapa[fi][fj];
    if (c == "#" or c == "I" or c == "B") return false;
    if (!c.empty() and (c[0] == 'T' or c[0] == 'E')) return false;
    return true;
}

string Map::celdaVacia(int fila, int col) {
    if (fila % 2 == 0 and col % 2 == 0)
        return "+";
    return " ";
}
