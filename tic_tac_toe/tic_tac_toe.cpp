#include <bits/stdc++.h>
using namespace std;

class Game {
    string grid[7];
    vector<int> elementInRow;
    vector<int> elementInCol;
    vector<int> elementInDiagonal; //diagonal[1] = \ direction, diagonal[2] = / direction

public:
    Game() {
        this->elementInRow = vector<int> (4, 0);
        this->elementInCol = vector<int> (4, 0);
        this->elementInDiagonal = vector<int> (3, 0);
        for (int r = 0; r < 7; r++) {
            if (r % 2 == 0) {
                this->grid[r] = "+---+---+---+";
            } else {
                this->grid[r] = "|   |   |   |";
            }
        }
    }

    int getElementInRow(int row);
    int getElementInCol(int col);
    int getElementInDiagonal(int diagonal);

    friend class Player;
    friend ostream& operator << (ostream& output, Game board);
    bool evaluateRow(int row);
    bool evaluateCol(int col);
    bool evaluateDiagonal(int diagonal);
    bool gridIsEmpty(int col, int row);
    bool isOver(int col, int row);
    void debug();
};

int Game::getElementInRow(int row) {
    return elementInRow[row];
}

int Game::getElementInCol(int col) {
    return elementInCol[col];
}

int Game::getElementInDiagonal(int diagonal) {
    return elementInDiagonal[diagonal];
}

bool Game::gridIsEmpty(int col, int row) {
    int r = row*2 - 1;
    int c = col*4 - 2;
    return (this->grid[r][c] == ' ');
}

ostream& operator << (ostream& output, Game board) {
    for (auto& row : board.grid) {
        output << row << "\n";
    }

    return output;
}

bool Game::evaluateRow(int row) {
    int r = row*2 - 1;
    return (grid[r][6] == grid[r][2] && grid[r][6] == grid[r][10]);
}

bool Game::evaluateCol(int col) {
    int c = col*4 - 2;
    return (grid[3][c] == grid[1][c] && grid[3][c] == grid[5][c]);
}

bool Game::evaluateDiagonal(int diagonal) {
    if (diagonal == 1) {
        return (grid[3][6] == grid[1][2] && grid[3][6] == grid[5][10]);
    } else {
        return (grid[3][6] == grid[5][2] && grid[3][6] == grid[1][10]);
    }
}

void Game::debug() {
    cout << *this << "\n";
    for (int r = 1; r <= 3; r++) {
        cout << "Elements in row " << r << " = " << elementInRow[r] << "\n";
    }
    for (int c = 1; c <= 3; c++) {
        cout << "Elements in col " << c << " = " << elementInCol[c] << "\n";
    }
    for (int d = 1; d <= 2; d++) {
        cout << "Elements in diagonal " << d << " = " << elementInDiagonal[d] << "\n";
    }
}

bool Game::isOver(int col, int row) {
    return (
        (this->getElementInCol(col) == 3 && this->evaluateCol(col)) ||
        (this->getElementInRow(row) == 3 && this->evaluateRow(row)) ||
        (this->getElementInDiagonal(1) == 3 && this->evaluateDiagonal(1)) ||
        (this->getElementInDiagonal(2) == 3 && this->evaluateDiagonal(2))
    );
}

class Player {
    Game *game;
    static int no;
    string name;
    char symbol;
    
public:
    Player() {
        this->no++;
        symbol = (no % 2 == 1 ? 'O' : 'X');
    }

    void setGame(Game *game);
    void setName(string name);
    string getName();
    void choose(int col, int row);
};
int Player::no = 0;

void Player::setGame(Game *game) {
    this->game = game;
}

void Player::choose(int col, int row) {
    int r = row*2 - 1;
    int c = col*4 - 2;

    this->game->grid[r][c] = this->symbol;
    this->game->elementInRow[row]++;
    this->game->elementInCol[col]++;
    if (col == row) this->game->elementInDiagonal[1]++;
    if (col == 4 - row) this->game->elementInDiagonal[2]++;
}

void Player::setName(string name) {
    this->name = name;
}

string Player::getName() {
    return this->name;
}


int main() {
    Game game;
    Player player_1, player_2;
    player_1.setGame(&game);
    player_1.setName("Doggy");
    player_2.setGame(&game);
    player_2.setName("Picko");

    int round = 0;
    cout << game << "\n";
    while (true) {
        round++;
        Player &currentPlayer = (round % 2 == 1 ? player_1 : player_2);
        cout << currentPlayer.getName() << "'s turn!\n";

        int col, row;

        //process input
        while (true) {
            cout << "Choose position: ";
            cin >> col >> row;
            if ((row >= 1 && row <= 3) && (col >= 1 && col <= 3) && game.gridIsEmpty(col, row))
                break;
            
            cout << "Invalid position!\n\n";
        }
        currentPlayer.choose(col, row);
        cout << "\n" << game << "\n";

        // check winner
        if (game.isOver(col, row)) {
            cout << currentPlayer.getName() << " wins!\n";
            break;
        }

        // check if the grid is full with 9 rounds
        if (round == 9) {
            cout << "Draw!\n";
            break;
        }
    }

    return 0;
}