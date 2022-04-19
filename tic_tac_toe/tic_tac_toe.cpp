#include <bits/stdc++.h>
using namespace std;

class Game {
    string grid[7];

public:
    Game() {
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
    bool evaluateRow(int row);
    bool evaluateCol(int col);
    bool evaluateDiagonal();
    bool canChoose(int col, int row);
    bool isOver(int col, int row);
};

class Player {
    Game *game;
    static int no;
    string name;
    char symbol;
    
public:
    Player() {
        this->no++;
        this->symbol = (no % 2 == 1 ? 'O' : 'X');
    }

    void setGame(Game *game);
    void setName(string name);
    string getName();
    void choose(int col, int row);
};

//Game::function() definition----------------------------------------------------------------------------------
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

bool Game::evaluateDiagonal() {
    if (grid[3][6] == ' ') return false;

    return (
        (grid[3][6] == grid[1][2] && grid[3][6] == grid[5][10]) ||
        (grid[3][6] == grid[5][2] && grid[3][6] == grid[1][10])
    );
}

bool Game::canChoose(int col, int row) {
    int r = row*2 - 1;
    int c = col*4 - 2;
    return (this->grid[r][c] == ' ');
}

bool Game::isOver(int col, int row) {
    return (this->evaluateCol(col) || this->evaluateRow(row) || this->evaluateDiagonal());
}

//Player::function() definition--------------------------------------------------------------------------------
int Player::no = 0;

void Player::setGame(Game *game) {
    this->game = game;
}

void Player::setName(string name) {
    this->name = name;
}

string Player::getName() {
    return this->name;
}

void Player::choose(int col, int row) {
    int r = row*2 - 1;
    int c = col*4 - 2;
    this->game->grid[r][c] = this->symbol;
}

//global function definition-----------------------------------------------------------------------------------
void play(Player &player_1, Player &player_2, bool turn) {
    Game game;
    player_1.setGame(&game);
    player_2.setGame(&game);
    cout << game << "\n";

    int round = 0;
    while (true) {
        round++;
        Player *currentPlayer;
        if (turn)   currentPlayer = (round % 2 == 1 ? &player_1 : &player_2);
        else        currentPlayer = (round % 2 == 1 ? &player_2 : &player_1);
        cout << currentPlayer->getName() << "'s turn!\n";

        int col, row;
        //process input
        while (true) {
            cout << "Choose position: ";
            cin >> col >> row;
            if ((row >= 1 && row <= 3) && (col >= 1 && col <= 3) && game.canChoose(col, row))
                break;
            
            cout << "Invalid position!\n\n";
        }
        currentPlayer->choose(col, row);
        cout << "\n" << game << "\n";

        // check winner
        if (game.isOver(col, row)) {
            cout << currentPlayer->getName() << " wins!\n";
            break;
        }

        // check if the grid is full with 9 rounds
        if (round == 9) {
            cout << "Draw!\n";
            break;
        }
    }
}


int main() {
    Player player_1, player_2;
    string name_1, name_2;
    cout << "Welcome to Tic Tac Toe Game!\n";
    cout << "Player 1's name: "; cin >> name_1;
    cout << "Player 2's name: "; cin >> name_2; cout << "\n";
    player_1.setName(name_1);
    player_2.setName(name_2);

    bool turn = true;
    while (true) {
        play(player_1, player_2, turn);
        string ans;
        cout << "Play again? (y/n)\n>>> "; cin >> ans;
        if (ans != "y") break;
        turn = !turn;
    }

    return 0;
}