#include <bits/stdc++.h>
using namespace std;

class Game {
    string grid[7];
    vector<int> elementInRow;
    vector<int> elementInCol;
    vector<int> elementInDiagonal;

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

    friend class Player;
    friend ostream& operator << (ostream& output, Game board);
    void debug();
};

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

ostream& operator << (ostream& output, Game board) {
    for (auto& row : board.grid) {
        output << row << "\n";
    }

    return output;
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
    void choose(int pos_x, int pos_y);
};
int Player::no = 0;

void Player::setGame(Game *game) {
    this->game = game;
}

void Player::choose(int pos_x, int pos_y) {
    int row = pos_y*2 - 1;
    int col = pos_x*4 - 2;
    this->game->grid[row][col] = this->symbol;

    this->game->elementInCol[pos_x]++;
    this->game->elementInRow[pos_y]++;

    if (pos_x == pos_y) this->game->elementInDiagonal[1]++;
    if (pos_x == 4 - pos_y) this->game->elementInDiagonal[2]++;
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
    player_1.choose(3, 1);

    game.debug();

    return 0;
}