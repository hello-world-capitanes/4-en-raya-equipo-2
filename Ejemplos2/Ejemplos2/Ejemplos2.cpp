#include <iostream>
using namespace std;

#define T 3
#define F 4

const int a = 8;
const int b = 8;

struct choice {
    int x = -1;
    int y = -1;
};

// Se verifica que el tablero no esté lleno.
bool freeSpace(int board[a][b], choice choice) {

    for (int i = 0; i < choice.x; i++)
    {
        for (int x = 0; x < choice.y; x++) {
            if (board[i][x] == 0) {
                return true;
            }
        }
    }

    cout << "Empate" << endl;
    return false;

}

// Se imprime en el tablero los espacios en blanco, las fichas del jugador 1: O y las fichas del jugador 2: X
void printBoard(int board[a][b], choice choice) {
    for (int i = 0; i < choice.x; i++)
    {
        for (int x = 0; x < choice.y; x++) {
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
int placeToken(int board[a][b], int column, choice choice) {
    for (int i = 0; i < choice.x; i++) {
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
bool winner(int board[a][b], int row, int column, int player, choice choice) {

    bool found = false;
    int total = 0;

    // Vertical
#pragma region vertical
    for (int i = 0; i < choice.x; i++) {

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

    for (int i = 0; i < choice.y; i++) {
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
        if (newRow >= choice.x) {
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

    } while (newRow < choice.x);
#pragma endregion

    // Diagonal ->
#pragma region diagonal->
    newRow = row;
    newColumn = column;
    found = false;
    total = 0;

    while ((newRow != 0 || newColumn != choice.y)) {
        newRow--;
        newColumn++;

        if (newRow == 0 || newColumn == choice.y) {
            break;
        }
    }

    do {
        if (newRow >= choice.x) {
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

    } while (newRow < choice.x);

    return false;

}
#pragma endregion

int main()
{
    choice choice;

    bool chose = false;
    char c;

    while (!chose) {
        cout <<"Quieres Jugar de a)3-en-3  b)4-en-4  c) 8-a-6 o d) 8-a-8?: ";
        cin >> c;
        switch (c) {
        case 'a':
            choice.x = T;
            choice.y = T;
            chose = true;
            break;
        case 'b':
            choice.x = F;
            choice.y = F;
            chose = true;
            break;
        case 'c':
            choice.x = a;
            choice.y = 6;
            chose = true;
            break;
        case 'd':
            choice.x = a;
            choice.y = b;
            chose = true;
            break;
        default:
            cout << "Eleccion Equivocada" << endl;

        }//switch

    }//while
    

    int arr[a][b];

    for (int i = 0; i < choice.x; i++) {
        for (int x = 0; x < choice.y; x++) {
            arr[i][x] = 0;
        }
    }

    int player = 0;
    string name;
    string name_player2;
    int last = 0;

    cout << "Como se llama el jugador 2? ";
    cin >> name_player2;

    do {
        int placeColumn = 0;
        bool columnOver = true;

        if (last == 1) {
            player = 2;
            name = name_player2;
        }
        else {
            player = 1;
        }

        do {
            cout << endl;
            cout << "Turno del jugador " << player << ", imprima un numero del 1 al "<< choice.y << endl;
            cin >> placeColumn;
            cout << endl;
            placeColumn--;
            columnOver = columnOverflow(arr, placeColumn);
        } while ((placeColumn < 0 || placeColumn > choice.y-1) || columnOver);

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

