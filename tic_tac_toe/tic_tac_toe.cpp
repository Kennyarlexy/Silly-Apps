#include <bits/stdc++.h>
using namespace std;

class Game {
    string grid[7];
    vector<int> elementInRow;
    vector<int> elementInCol;
    vector<int> elementInDiagonal; //diagonal 1 = \ direction, diagonal 2 = / direction

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

    int getElementInRow(int row) {
        return elementInRow[row];
    }

    int getElementInCol(int col) {
        return elementInCol[col];
    }

    friend class Player;
    friend ostream& operator << (ostream& output, Game board);
    bool evaluateRow(int row);
    bool evaluateCol(int col);
    bool evaluateDiagonal(int diagonal);
    void debug();
};

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
    return (grid[4][c] == grid[2][c] && grid[4][c] == grid[6][c]);
}

bool Game::evaluateDiagonal(int diagonal) {
    if (diagonal == 1) {
        return (grid[4][6] == grid[2][2] && grid[4][6] == grid[6][10]);
    } else {
        return (grid[4][6] == grid[6][2] && grid[4][6] == grid[2][10]);
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
        cout << "Elements in diagonal " << d << " = " << elementInCol[d] << "\n";
    }
}


class Player {
    Game *game;
    static int no;
    char symbol;
    
public:
    Player() {
        this->no++;
        symbol = (no % 2 == 1 ? 'O' : 'X');
    }

    void setGame(Game *game);
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

    // if (this->game->elementInRow[row] == 3) {
    //     this->game->evaluateRow(row);
    // }

    // if (this->game->elementInCol[col] == 3) {
    //     this->game->evaluateCol(col);
    // }

    // if (col == row) {
    //     int diagonal = 1;
    //     int &element = this->game->elementInDiagonal[diagonal];
    //     element++;

    //     if (element == 3) this->game->evaluateDiagonal(diagonal);
    // }

    // if (col == 4 - row) {
    //     int diagonal = 2;
    //     int &element = this->game->elementInDiagonal[diagonal];
    //     element++;

    //     if (element == 3) this->game->evaluateDiagonal(diagonal);
    // }
}



int main() {
    Game game;
    Player player_1, player_2;
    player_1.setGame(&game);
    player_2.setGame(&game);

    player_1.choose(1, 1);
    player_2.choose(2, 2);
    player_1.choose(2, 1);
    player_2.choose(3, 2);

    cout << "Enter \"3 1\"\n";
    int col, row; cin >> col >> row;
    player_1.choose(col, row);
    cout << game << "\n";
    if (game.getElementInRow(row) == 3) {
        if (game.evaluateRow(row)) cout << "You Win!\n";
    }

    // game.debug();

    return 0;
}