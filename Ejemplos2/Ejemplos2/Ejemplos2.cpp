#include <iostream>
using namespace std;

#define T 3
#define F 4

const int a = 8;
const int b = 8;

// Se verifica que el tablero no esté lleno.
bool freeSpace(int board[a][b], int choice) {

    for (int i = 0; i < choice; i++)
    {
        for (int x = 0; x < choice; x++) {
            if (board[i][x] == 0) {
                return true;
            }
        }
    }

    cout << "Empate" << endl;
    return false;

}

// Se imprime en el tablero los espacios en blanco, las fichas del jugador 1: O y las fichas del jugador 2: X
void printBoard(int board[a][b], int choice) {
    for (int i = 0; i < choice; i++)
    {
        for (int x = 0; x < choice; x++) {
            if (board[i][x] == 1) {
                cout << " A ";
            }
            else if (board[i][x] == 2){
                cout << " B ";

            }
            else {
                cout << " . ";
            }
        }
        cout << endl;
    }
}

// Se imprime el token del jugador, verificando primero que el lugar de la columna este vacia.
int placeToken(int board[a][b], int column, int choice) {
    for (int i = 0; i < choice; i++) {
        if (!(i+1 > 5)) {
            if (board[i][column] == 0 && board[i + 1][column] != 0) {
                return i;
            }
        }
        else {
            if (board[i][column] == 0) {
                return i;
            }
        }
    }
    return -1;
}

// Verifica que se ha llegado al tope del tablero.
bool columnOverflow(int board[a][b], int column) {
    if (board[0][column] != 0) {
        cout << "No hay espacio para la ficha" << endl;
        return true;
    }
    return false;
}

// Se busca si ya algun jugador ha ganado la partida, en vertical, horizontal o diagonales.
bool winner(int board[a][b], int row, int column, int player, int choice) {

    bool found = false;
    int total = 0;

    // Vertical
#pragma region vertical
    for (int i = 0; i < choice; i++) {

        if (found) {
            if (board[i][column] == player) {
                total++;
            }
            else {

                found = false;
                total = 0;
            }
        }
        if (board[i][column] == player && !found) {

            found = true;
            total++;
        }
        if (total == 4) {

            cout << "Jugador " << player << " ha ganado." << endl;
            return true;
        }

    }
#pragma endregion

    // Horizontal 
#pragma region horizontal
    found = false;
    total = 0;

    for (int i = 0; i < choice; i++) {
        if (found) {
            if (board[row][i] == player) {
                total++;
            }
            else {
                found = false;
                total = 0;
            }
        }
        if (board[row][i] == player && !found) {
            found = true;
            total++;
        }
        if (total == 4) {
            cout << "Jugador " << player << " ha ganado." << endl;
            return true;
        }
    }
#pragma endregion 

    // Diagonal <-
#pragma region diagonal<-
    int newRow = row;
    int newColumn = column;
    found = false;
    total = 0;

    while ((newRow != 0 || newColumn != 0)) {
        newRow--;
        newColumn--;

        if (newRow == 0 || newColumn == 0) {
            break;
        }
    }

    do {
        if (newRow >= choice) {
            break;
        }
        if (found) {
            if (board[newRow][newColumn] == player) {
                total++;
            }
            else {
                found = false;
                total = 0;
            }
        }
        if (board[newRow][newColumn] == player && !found) {
                found = true;
                total++;
        }
        if (total == 4) {
                cout << "Jugador " << player << " ha ganado." << endl;
                return true;
        }

        newRow++;
        newColumn++;

    } while (newRow < choice);
#pragma endregion

    // Diagonal ->
#pragma region diagonal->
    newRow = row;
    newColumn = column;
    found = false;
    total = 0;

    while ((newRow != 0 || newColumn != choice)) {
        newRow--;
        newColumn++;

        if (newRow == 0 || newColumn == choice) {
            break;
        }
    }

    do {
        if (newRow >= choice) {
            break;
        }
        if (found) {
            if (board[newRow][newColumn] == player) {
                total++;
            }
            else {
                found = false;
                total = 0;
            }
        }
        if (board [newRow][newColumn] == player && !found) {
            found = true;
            total++;
        }
        if (total == 4) {
            cout << "Jugador " << player << " ha ganado." << endl;
            return true;
        }

        newRow++;
        newColumn--;

    } while (newRow < choice);

    return false;

}
#pragma endregion

int main()
{
    bool chose = false;
    int choice;

    while (!chose) {
        cout <<"Quieres Juegar de 3-en-3 o 4-en-4?: ";
        cin >> choice;
        if (choice == T || choice == F)
            chose = true;
        else
            cout << "Eleccion Equivocada" << endl << endl;
    }
    

    int arr[a][b];

    for (int i = 0; i < choice; i++) {
        for (int x = 0; x < choice; x++) {
            arr[i][x] = 0;
        }
    }

    int player = 0;
    int last = 0;

    do {
        int placeColumn = 0;
        bool columnOver = true;

        if (last == 1) {
            player = 2;
        }
        else {
            player = 1;
        }

        do {
            cout << endl;
            cout << "Turno del jugador " << player << ", imprima un numero del 1 al "<< choice << endl;
            cin >> placeColumn;
            cout << endl;
            placeColumn--;
            columnOver = columnOverflow(arr, placeColumn);
        } while ((placeColumn < 0 || placeColumn > choice-1) || columnOver);

        int placeRow = placeToken(arr, placeColumn, choice);
        arr[placeRow][placeColumn] = player;
        printBoard(arr, choice);

        if (winner(arr, placeRow, placeColumn, player, choice)) {
            break;
        }

        last = player;
        player++;
    } while (freeSpace(arr, choice));

    return 0;

}

