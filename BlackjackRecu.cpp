#include <iostream>
using namespace std;

//Variables juego
int cartaTipoPica[13];
int cartaTipoTrebol[13];
int cartaTipoCorazon[13];
int cartaTipoDiamante[13];
bool finPartida = false;

//Jugador
string nombreJugador;
int puntosJugador = 0;
bool jugadorSeRinde = false;
bool jugadorGana = false;
bool jugadorPierde = false;

//Croupier
string banca = "Croupier";
int puntosCroupier = 0;
bool croupierSeRinde = false;
bool croupierGana = false;
bool croupierPierde = false;



void gameStart() {
    cout << "Bienvenido al BlackJack\n";
    cout << "Como te llamas?:\n";
    cin >> nombreJugador;
    cout << "Empecemos a jugar " + nombreJugador + "!\n";
}


void arrayCartas(int(&cArray)[13]) {
    for (int i = 0; i < 13; i++) {
        cArray[i] = 1;
    }
}

void repartocartas(string name, int& totalPoints) {
    string palo;
    int valorCarta = 0;
    int valorPalo = 0;
    bool reparto = false;
    int opcion = 0;
    while (!reparto) {
        valorCarta = rand() % 13;
        valorPalo = rand() % 4;
        if ((valorPalo) == 0) {
            if (cartaTipoPica[valorCarta] == 1) {
                cartaTipoPica[valorCarta] = 0;
                reparto = true;
                palo = "picas";
            }
        }
        else if ((valorPalo) == 1) {
            if (cartaTipoTrebol[valorCarta] == 1) {
                cartaTipoTrebol[valorCarta] = 0;
                reparto = true;
                palo = "treboles";
            }
        }
        else if ((valorPalo) == 2) {
            if (cartaTipoCorazon[valorCarta] == 1) {
                cartaTipoCorazon[valorCarta] = 0;
                reparto = true;
                palo = "corazones";
            }
        }
        else {
            if (cartaTipoDiamante[valorCarta] == 1) {
                cartaTipoDiamante[valorCarta] = 0;
                reparto = true;
                palo = "diamantes";
            }
        }

        if (valorCarta > 0 && valorCarta < 10) {
            valorCarta = valorCarta + 1;
        }
        else if (valorCarta >= 10 && valorCarta <= 13) {
            valorCarta = 10;
        }
        else if (valorCarta == 0) {
            if (name == nombreJugador) {
                cout << "Te ha salido un as!\n";
                cout << "Que valor quieres darle. 1 o 11?\n";
                while (opcion != 1 && opcion != 11) {
                    cin >> opcion;
                    if (opcion == 1) {
                        valorCarta = 1;
                    }
                    else if (opcion == 11) {
                        valorCarta = 11;
                    }
                    else {
                        cout << "Esa no es una opcion valida\n";
                    }
                }
            }
            else if (name == banca) {
                cout << "A la banca le ha salido un As\n";
                if (totalPoints + 11 <= 21) {
                    valorCarta = 11;
                }
                else { valorCarta = 1; }
            }
        }
        totalPoints += valorCarta;
        cout << "El jugador " << name << " ha sacado un " << valorCarta << " de " << palo << " y tiene un total de " << totalPoints << " puntos" << endl;
    }
}
bool checkPuntos(int& puntos, bool& ganador, bool& perdedor) {
    if (puntos == 21) {
        ganador = true;
        return true;
    }
    else if (puntos > 21) {
        perdedor = true;
        return true;
    }
    return false;
}
bool checkGanador(int puntos1, int puntos2, bool& ganador2) {
    if (puntos2 > puntos1) {
        ganador2 = true;
        return true;
    }
    else {
        return false;
    }
}
int main() {
    gameStart();
    arrayCartas(cartaTipoPica);
    arrayCartas(cartaTipoTrebol);
    arrayCartas(cartaTipoCorazon);
    arrayCartas(cartaTipoDiamante);
    srand(time(NULL));
    repartocartas(nombreJugador, puntosJugador);
    repartocartas(nombreJugador, puntosJugador);
    jugadorSeRinde = checkPuntos(puntosJugador, jugadorGana, jugadorPierde);
    repartocartas(banca, puntosCroupier);
    while (!jugadorSeRinde) {
        int opcion = 0;
        while (opcion != 1 && opcion != 2) {
            cout << "Tienes " << puntosJugador << ", quieres pedir carta?" << endl;
            cout << "1. Si" << endl;
            cout << "2. No" << endl;
            cin >> opcion;
            if (opcion != 1 && opcion != 2) {
                cout << "Escoge una opción válida." << endl;
            }
        }
        if (opcion == 1) {
            repartocartas(nombreJugador, puntosJugador);
            jugadorSeRinde = checkPuntos(puntosJugador, jugadorGana, jugadorPierde);
        }

        else {

            jugadorSeRinde = true;
        }

    }
    if (jugadorGana) {
        cout << "El jugador " << nombreJugador << " gana y la banca pierde" << endl;
    }
    else if (jugadorPierde) {
        cout << "El jugador " << nombreJugador << " pierde y la banca gana" << endl;
    }

    else {
        while (!croupierSeRinde) {
            repartocartas(banca, puntosCroupier);
            croupierSeRinde = checkPuntos(puntosCroupier, jugadorGana, jugadorPierde);
            if (!croupierSeRinde) {
                croupierSeRinde = checkGanador(puntosJugador, puntosCroupier, croupierGana);
            }
        }
        if (croupierGana) {
            cout << "La banca gana y el jugador " << nombreJugador << " pierde" << endl;
        }
        else if (croupierPierde) {
            cout << "La banca pierde y el jugador " << nombreJugador << " gana" << endl;
        }
    }
}