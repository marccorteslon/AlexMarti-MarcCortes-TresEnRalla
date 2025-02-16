#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <string>

char tablero[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };


void imprimirTablero() {
    std::cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        std::cout << "| ";
        for (int j = 0; j < 3; j++) {
            std::cout << tablero[i][j] << " | ";
        }
        std:: cout << "\n-------------\n";
    }
}



bool verificarGanador(char jugador) {
    for (int i = 0; i < 3; i++) {
        //Jugador 1
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
            return true;
        }

        //Jugador 2 (falta cambiarlo por la IA)
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
            return true;
        }
        /*else {
            std::cout << "Turno de O\n";
            InteligenciaArtificial();
        }*/

    }
    
    return false;
}



bool tableroLleno() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] == ' ') return false;
    return true;
}

void IA() {
    int fila, columna;
    srand(time(NULL));
    do {
        fila = rand() % 3;
        columna = rand() % 3;
    } while (tablero[fila][columna] != ' ');
    tablero[fila][columna] = 'O';
}

void guardarPartida() {
    std::string nombreArchivo;
    std::cout << "Ingresa un nombre para el archivo de guardado: ";
    std::cin >> nombreArchivo;
    nombreArchivo += ".tictacsave";

    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                archivo << tablero[i][j] << ' ';
            }
            archivo << '\n';
        }
        archivo.close();
        std::cout << "Partida guardada como " << nombreArchivo << "\n";
    }
    else {
        std::cout << "Error :(";
    }
}

bool cargarPartida() {
    std::string nombreArchivo;
    std::cout << "Ingresa el nombre de tu archivo de gurdado: ";
    std::cin >> nombreArchivo;
    nombreArchivo += ".tictacsave";

    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                archivo >> tablero[i][j];
            }
        }
        archivo.close();
        std::cout << "Partida cargada  correctamente :D";
        return true;
    }
    else {
        std::cout << "Error al cargar tu partida :(";
        return false;
    }
}

void jugar() {
    char jugador = 'X';
    int fila, columna;

    while (true) {
        imprimirTablero();

        if (jugador == 'X') {
            std::cout << "Seguir jugando [1]\nGuardar Partida [2]\n";
            short opcion;
            std::cin >> opcion;

            if (opcion == 2) {
                guardarPartida();
                continue;
            }
            else if (opcion != 1) {
                std::cout << "Error :(";
                continue;
            }
        }

        if (jugador == 'X') {
            std::cout << "Le toca a " << jugador << ". Elige casilla [1-3]: ";
            std::cin >> fila >> columna;

            fila--;
            columna--;

            if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero[fila][columna] == ' ') {
                tablero[fila][columna] = jugador;
            }
            else {
                std::cout << "NO >:C.\n";
                continue;
            }
        }
        else {
            IA();
        }

        if (verificarGanador(jugador)) {
            imprimirTablero();
            std::cout << "¡Ha ganado " << jugador << " !\n";
            break;
        }

        if (tableroLleno()) {
            imprimirTablero();
            std::cout << "¡Empate!(90% empata, como en la vida, vuelve a probar)\n";
            break;
        }

        jugador = (jugador == 'X') ? 'O' : 'X';
    }
}




int main() {
    std::cout << "MENU PRINCIPAL\n\n";
    std::cout << "Jugar [1]\n";
    std::cout << "Cargar Partida [2]\n";
    std::cout << "Salir [3]\n";

    short optionMenu;
    std::cin >> optionMenu;

    if (optionMenu == 2) {
        if (!cargarPartida()) {
            std::cout << "Iniciando nueva Partida\n";
        }
    }
    jugar();
    return 0;
}
