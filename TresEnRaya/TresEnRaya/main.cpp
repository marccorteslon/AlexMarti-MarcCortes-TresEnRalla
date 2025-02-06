#include <iostream>


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
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
            return true;
        }
    }
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)) {
        return true;
    }
    return false;
}



bool tableroLleno() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i][j] == ' ') return false;
    return true;
}



void jugar() {
    char jugador = 'X';
    int fila, columna;

    while (true) {
        imprimirTablero();
        std::cout << "Le toca a " << jugador << ". Elige casilla [1-3]: ";
        std::cin >> fila >> columna;

        fila--;  // Ajustar a índice del array (1-3 → 0-2)
        columna--;

        if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero[fila][columna] == ' ') {
            tablero[fila][columna] = jugador;

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
        else {
            std::cout << "NO >:C.\n";
        }
    }
}




int main() {
    jugar();
    return 0;
}
