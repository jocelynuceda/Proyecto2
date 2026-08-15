#include "Game.h"
#include <cstdlib>
#include <ctime>

Game::Game() {
    this->mapa = nullptr;
    this->camara = nullptr;
    this->dinero = 300;
    this->iniciado = false;
    this->huboOleada = false;
}

Game::~Game() { limpiar(); }

void Game::limpiar() {
    delete mapa; mapa = nullptr;
    delete camara; camara = nullptr;
    for (int i = 0; i < (int)enemigos.size(); i++) delete enemigos[i];
    enemigos.clear();
    for (int i = 0; i < (int)torres.size(); i++) delete torres[i];
    torres.clear();
}

string Game::restaurarCelda(int filaInt, int colInt) const {
    if (filaInt == 0 && colInt == 0) return "I";
    if (filaInt == 78 && colInt == 78) return "B";
    return "+";
}

void Game::mostrarVentana_impl() const {
    int r0 = camara->get_fila_inicio();
    int c0 = camara->get_columna_inicio();

    cout << "    ";
    for (int c = c0 + 1; c <= c0 + camara->tam_ventana; c++) {
        if (c < 10) cout << " " << c << " ";
        else cout << c << " ";
    }
    cout << endl;

    for (int f = r0 + 1; f <= r0 + camara->tam_ventana; f++) {
        if (f < 10) cout << " " << f << "  ";
        else cout << f << "  ";

        for (int c = c0 + 1; c <= c0 + camara->tam_ventana; c++) {
            int fi = (f - 1) * 2;
            int ci = (c - 1) * 2;
            string s = mapa->getCell(fi, ci);
            if (s.length() == 1) cout << " " << s << " ";
            else cout << " " << s;
        }
        cout << endl;
    }
}

void Game::mostrarBienvenida() const {
    cout << "Welcome to the world of tower defense xyz" << endl;
}

bool Game::iniciarJuego(const string& archivoMapa) {
    limpiar();
    this->dinero = 300;
    this->mapa = new Map();
    this->mapa->init(archivoMapa);
    this->camara = new Camera();
    this->iniciado = true;
    this->huboOleada = false;

    mostrarBienvenida();
    mostrarEstado();
    return true;
}

void Game::mostrarVentana() {
    mostrarVentana_impl();
}

void Game::moverCamara(const string& direccion, int n) {
    if (direccion == "up") camara->moverArriba(n);
    else if (direccion == "down") camara->moverAbajo(n);
    else if (direccion == "left") camara->moverIzquierda(n);
    else if (direccion == "right") camara->moverDerecha(n);
}

void Game::colocarTorre(int x, int y, int danio, int disparos) {
    if (!mapa->esPosicionValida(x, y)) {
        cout << "Posicion invalida" << endl;
        return;
    }
    if (dinero < COSTO_TORRE) {
        cout << "Dinero insuficiente" << endl;
        return;
    }

    int fi = (x - 1) * 2;
    int ci = (y - 1) * 2;

    int df[] = {-2, 2, 0, 0};
    int dc[] = {0, 0, -2, 2};
    bool adyacente = false;
    for (int k = 0; k < 4; k++) {
        int nf = fi + df[k], nc = ci + dc[k];
        if (nf >= 0 && nf < tamanio_real && nc >= 0 && nc < tamanio_real) {
            string s = mapa->getCell(nf, nc);
            if (s == "#" || s == "I" || s == "B") { adyacente = true; break; }
        }
    }
    if (!adyacente) {
        cout << "Posicion invalida" << endl;
        return;
    }

    Tower* t = new Tower(x, y, danio, 2, disparos);
    torres.push_back(t);
    mapa->setCell(fi, ci, "T" + to_string(t->numero));
    dinero -= COSTO_TORRE;

    cout << "Torre colocada" << endl;
    cout << "Dinero: " << dinero << endl;
}

void Game::generarEnemigos(int vida) {
    if (!enemigos.empty()) {
        cout << "Ya hay enemigos en el mapa" << endl;
        return;
    }
    srand(time(0));
    int cantidad = rand() % 4 + 3;
    huboOleada = true;

    for (int i = 0; i < cantidad; i++) {
        enemigos.push_back(new Enemy(i, vida));
        mapa->setCell(mapa->getRutaFila(i), mapa->getRutaCol(i), "E");
    }

    mostrarEstado();
}

void Game::moverEnemigos() {
    if (enemigos.empty()) return;

    for (int i = 0; i < (int)enemigos.size() - 1; i++) {
        for (int j = i + 1; j < (int)enemigos.size(); j++) {
            if (enemigos[j]->posRuta > enemigos[i]->posRuta) {
                Enemy* tmp = enemigos[i];
                enemigos[i] = enemigos[j];
                enemigos[j] = tmp;
            }
        }
    }

    for (int i = 0; i < (int)enemigos.size(); i++) {
        int pos = enemigos[i]->posRuta;
        int fi = mapa->getRutaFila(pos);
        int ci = mapa->getRutaCol(pos);

        bool compartida = false;
        for (int j = 0; j < (int)enemigos.size(); j++) {
            if (j == i) continue;
            if (enemigos[j]->posRuta == pos) { compartida = true; break; }
        }
        if (!compartida)
            mapa->setCell(fi, ci, restaurarCelda(fi, ci));

        if (enemigos[i]->posRuta < mapa->getCeldasRuta() - 1)
            enemigos[i]->posRuta++;

        int nf = mapa->getRutaFila(enemigos[i]->posRuta);
        int nc = mapa->getRutaCol(enemigos[i]->posRuta);
        mapa->setCell(nf, nc, "E");
    }
    cout << "Enemigos avanzaron" << endl;
}

void Game::atacarEnemigos() {
    int offsetF[] = {-4, -4, -4, -2, -2, 0, 0, 2, 2, 4, 4, 4};
    int offsetC[] = {-2, 0, 2, -4, 4, -4, 4, -4, 4, -2, 0, 2};

    bool huboDisparo = false;

    for (int t = 0; t < (int)torres.size(); t++) {
        if (!torres[t]->puedeDisparar()) continue;

        int tF = (torres[t]->fila - 1) * 2;
        int tC = (torres[t]->columna - 1) * 2;

        int mejorEnemigo = -1;
        int mejorPos = -1;

        for (int k = 0; k < 12; k++) {
            int ef = tF + offsetF[k];
            int ec = tC + offsetC[k];
            if (ef < 0 || ef >= tamanio_real || ec < 0 || ec >= tamanio_real) continue;
            if (mapa->getCell(ef, ec) != "E") continue;

            for (int e = 0; e < (int)enemigos.size(); e++) {
                int pos = enemigos[e]->posRuta;
                if (mapa->getRutaFila(pos) == ef && mapa->getRutaCol(pos) == ec) {
                    if (pos > mejorPos) {
                        mejorPos = pos;
                        mejorEnemigo = e;
                    }
                }
            }
        }

        if (mejorEnemigo != -1) {
            enemigos[mejorEnemigo]->salud -= torres[t]->danio;
            torres[t]->disparar();
            huboDisparo = true;

            if (enemigos[mejorEnemigo]->salud <= 0) {
                int pos = enemigos[mejorEnemigo]->posRuta;
                int ef = mapa->getRutaFila(pos);
                int ec = mapa->getRutaCol(pos);
                mapa->setCell(ef, ec, restaurarCelda(ef, ec));

                delete enemigos[mejorEnemigo];
                enemigos.erase(enemigos.begin() + mejorEnemigo);

                dinero += RECOMPENSA;
            }
        }
    }
    if (huboDisparo) cout << "Torres atacaron" << endl;
}

void Game::mostrarEstado() {
    cout << "Dinero: " << dinero << endl;
    cout << "Torres: " << torres.size() << endl;
    cout << "Enemigos: " << enemigos.size() << endl;
}

bool Game::estaIniciado() const { return iniciado; }
bool Game::todosEnemigosEliminados() const { return huboOleada && enemigos.empty(); }

bool Game::baseDestruida() const {
    for (int i = 0; i < (int)enemigos.size(); i++) {
        if (enemigos[i]->posRuta == mapa->getCeldasRuta() - 1) return true;
    }
    return false;
}

void Game::guardarJuego(const string& archivo) {
    ofstream f(archivo);
    if (!f.is_open()) { cout << "Error al guardar" << endl; return; }

    f << dinero << "\n";
    f << torres.size() << "\n";
    for (int i = 0; i < (int)torres.size(); i++)
        f << *torres[i] << "\n";
    f << enemigos.size() << "\n";
    for (int i = 0; i < (int)enemigos.size(); i++)
        f << *enemigos[i] << "\n";
    f << *camara << "\n";
    mapa->saveGrid(f);
    f.close();
    cout << "Juego guardado" << endl;
}

bool Game::cargarJuego(const string& archivo) {
    ifstream f(archivo);
    if (!f.is_open()) { cout << "operacion no valida" << endl; return false; }

    limpiar();
    this->mapa = new Map();
    this->camara = new Camera();

    f >> dinero;

    int nt;
    f >> nt;
    for (int i = 0; i < nt; i++) {
        int lf, lc, num, disp;
        f >> lf >> lc >> num >> disp;
        Tower* t = new Tower(lf, lc);
        t->numero = num;
        t->disparosUsados = disp;
        torres.push_back(t);
    }
    Tower::contador = nt;

    int ne;
    f >> ne;
    huboOleada = (ne > 0);
    for (int i = 0; i < ne; i++) {
        int pos, hp, vivo;
        f >> pos >> hp >> vivo;
        Enemy* e = new Enemy(pos, hp);
        e->vivo = (vivo == 1);
        enemigos.push_back(e);
    }

    int cr, cc;
    f >> cr >> cc;
    camara->startRow = cr;
    camara->startCol = cc;

    mapa->cargarMapa(f);
    f.close();

    this->iniciado = true;
    mostrarBienvenida();
    mostrarEstado();
    mostrarVentana_impl();
    return true;
}
