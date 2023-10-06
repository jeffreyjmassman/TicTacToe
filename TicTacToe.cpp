#include "TicTacToe.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using std::vector; using std::cout; using std::endl; using std::cin;
using std::string;

void TicTacToe::game() {
    srand(time(0));
    moveCount = 0;
    for (int x = 0; x < 3; x++) {
        vector<string> vec;
        board.push_back(vec);
        for (int y = 0; y < 3; y++) {
            board[x].push_back(" ");
        }
    }
    this->printGame();
    //cout << "Do you want to go first?"
    cout << "Make a move! Type in first your desired x coordinate, then your y coordinate. \n" << endl;
    while (1) {
        this->playerMakeMove();
        this->printGame();
        vector<bool> wincheck = this->winner();
        if (wincheck[0]) {
            if (wincheck[1]) {
                cout << "Congratulations! You have won!" << endl;
                return;
            }
            else {
                cout << "Sorry, but the computer has won." << endl;
                return;
            }
        }
        if (moveCount == 9) {
            cout << "The game is a tie!" << endl;
            return;
        }
        this->computerMakeMove();
        this->printGame();
        wincheck = this->winner();
        if (wincheck[0]) {
            if (wincheck[1]) {
                cout << "Congratulations! You have won!" << endl;
                return;
            }
            else {
                cout << "Computer wins! Better luck next time!" << endl;
                return;
            }
        }
    }
}

void TicTacToe::printGame() {
    cout << "\n \n \n \n \n \n \n \n " << endl;
    cout << "                                   0   1   2" << endl;
    cout << "                                0  " << board[0][0] << " | " << board[1][0] << " | " << board[2][0] << endl;
    //cout << "                                  ___________" << endl;
    cout << "                                  ===========" << endl;
    cout << "                                1  "<< board[0][1] << " | " << board[1][1] << " | " << board[2][1] << endl;
    //cout << "                                  ___________" << endl;
    cout << "                                  ===========" << endl;
    cout << "                                2  "<< board[0][2] << " | " << board[1][2] << " | " << board[2][2] << endl;
    cout << "\n \n \n \n \n \n \n \n" << endl;
}

void TicTacToe::test() {
    for (int x = 0; x < 3; x++) {
        vector<string> vec;
        board.push_back(vec);
        for (int y = 0; y < 3; y++) {
           board[x].push_back("X");
        }
    }
}

vector<bool> TicTacToe::winner() {
    //vector encodes whether or not there was a winner, and if so, who it was. whowon[0] = is there a winner?
    // whowon[1] = who was it? true = X, false = O
    vector<bool> whowon;
    whowon.push_back(false);
    whowon.push_back(false);
    // check rows
    for (int y = 0; y < 3; y++) {
        string first = board[0][y];
        if (board[1][y] == first && board[2][y] == first) {
            if (first == "X") {
                whowon[0] = true;
                whowon[1] = true;
            }
            if (first == "O") {
                whowon[0] = true;
                whowon[1] = false;
            }
            return whowon;
        } 
    }
    // check columns
    for (int x = 0; x < 3; x++) {
        string first = board[x][0]; 
        if (board[x][1] == first && board[x][2] == first) {
            if (first == "X") {
                whowon[0] = true;
                whowon[1] = true;
            }
            if (first == "O") {
                whowon[0] = true;
                whowon[1] = false;
            }
            return whowon;
        }
    }
    //check diags
    string first = board[0][0];
    if (board[1][1] == first && board[2][2] == first) {
        if (first == "X") {
                whowon[0] = true;
                whowon[1] = true;
            }
        if (first == "O") {
                whowon[0] = true;
                whowon[1] = false;
        }
        return whowon;
    }
    
    first = board[0][2];
    if (board[1][1] == first && board[2][0] == first) {
        if (first == "X") {
                whowon[0] = true;
                whowon[1] = true;
            }
        if (first == "O") {
                whowon[0] = true;
                whowon[1] = false;
        }
        return whowon;
    }
    return whowon;
}

void TicTacToe::playerMakeMove() {
    int x = 0;
    int y = 0;
    while (1) {
        cout << "Your x Coordinate: ";
        cin >> x;
        cout << "Your y coordinate: ";
        cin >> y;
        if (board[x][y] == " ") {
            break;
        }
        cout << "Sorry, there is already an " << board[x][y] << " at that space. Please pick another one." << endl;
    }
    cout << "\n" << endl;
    board[x][y] = "X";
    moveCount++;
}

void TicTacToe::computerMakeMove() {
    //if there are 0 or 1 moves, pick a random corner or the middle
    if (moveCount < 2) {
        while(1) {
            int valx = rand() % 2;
            int valy = rand() % 2;
            //try for the middle randomly, 50% chance (not accounting for rand() bias)
            int middle = rand() % 10;
            if (middle < 5) {
                if (board[1][1] == " ") {
                    board[1][1] = "O";
                    moveCount++;
                    return;
                }
            }
            //otherwise, try a corner
            int cornerx = (valx == 0) ? 0 : 2;
            int cornery = (valy == 0) ? 0 : 2;
            if (board[cornerx][cornery] == " ") {
                board[cornerx][cornery] = "O";
                moveCount++;
                return;
            }
        }
    }
    //See if there are 2 or more O's next to each other and place O next to it
    //columns 
    for (int x = 0; x < 3; x++) {
        int oCount = 0;
        for (int y = 0; y < 3; y++) {
            if (board[x][y] == "O") {
                oCount++;
            }
        }
        if (oCount == 2) {
            for (int y = 0; y < 3; y++) {
                if (board[x][y] == " ") {
                    board[x][y] = "O";
                    moveCount++;
                    return;
                }
            }
        }
    }
    //rows
    for (int y = 0; y < 3; y++) {
        int oCount = 0;
        for (int x = 0; x < 3; x++) {
            if (board[x][y] == "O") {
                oCount++;
            }
        }
        if (oCount == 2) {
            for (int x = 0; x < 3; x++) {
                if (board[x][y] == " ") {
                    board[x][y] = "O";
                    moveCount++;
                    return;
                }
            }
        }
    }
    int oCount = 0;
    for (int i = 0; i < 3; i++) {
        if (board[i][i] == "O") {
            oCount++;
        }
    }
    if (oCount == 2) {
        for (int i = 0; i < 3; i++) {
            if (board[i][i] == " ") {
                board[i][i] = "O";
                moveCount++;
                return;
            }
        }
    }
    oCount = 0;
    for (int i = 0; i < 3; i++) {
        if (board[2-i][i] == "O") {
            oCount++;
        }
    }
    if (oCount == 2) {
        for (int i = 0; i < 3; i++) {
            if (board[2-i][i] == " ") {
                board[2-i][i] = "O";
                moveCount++;
                return;
            }
        }
    }
    //check if player almost winning
    //columns 
    for (int x = 0; x < 3; x++) {
        int xCount = 0;
        for (int y = 0; y < 3; y++) {
            if (board[x][y] == "X") {
                xCount++;
            }
        }
        if (xCount == 2) {
            for (int y = 0; y < 3; y++) {
                if (board[x][y] == " ") {
                    board[x][y] = "O";
                    moveCount++;
                    return;
                }
            }
        }
    }
    //rows
    for (int y = 0; y < 3; y++) {
        int xCount = 0;
        for (int x = 0; x < 3; x++) {
            if (board[x][y] == "X") {
                xCount++;
            }
        }
        if (xCount == 2) {
            for (int x = 0; x < 3; x++) {
                if (board[x][y] == " ") {
                    board[x][y] = "O";
                    moveCount++;
                    return;
                }
            }
        }
    }
    int xCount = 0;
    for (int i = 0; i < 3; i++) {
        if (board[i][i] == "X") {
            xCount++;
        }
    }
    if (xCount == 2) {
        for (int i = 0; i < 3; i++) {
            if (board[i][i] == " ") {
                board[i][i] = "O";
                moveCount++;
                return;
            }
        }
    }
    xCount = 0;
    for (int i = 0; i < 3; i++) {
        if (board[2-i][i] == "X") {
            xCount++;
        }
    }
    if (xCount == 2) {
        for (int i = 0; i < 3; i++) {
            if (board[2-i][i] == " ") {
                board[2-i][i] = "O";
                moveCount++;
                return;
            }
        }
    }
    //Otherwise, find one O and place next to it
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[x][y] == "O") {
                if (x+1 < 3) {
                    if (board[x+1][y] == " ") {
                        if (x+2 < 3) {
                            if (board[x+2][y] == " ") {
                                int shift = rand() % 2 + 1;
                                board[x+shift][y] = "O";
                                moveCount++;
                                return;
                            }
                        }
                        if (x-1 >= 0) {
                            if (board[x-1][y] == " ") {
                                int shift = (rand() % 2 == 0) ? 1 : -1;
                                board[x+shift][y] = "O";
                                moveCount++;
                                return;
                            }
                        }
                    }
                }
                if (x-1 >= 0) {
                    if (board[x-1][y] == " ") {
                        if (x-2 >= 0) {
                            if (board[x-2][y] == " ") {
                                int shift = (rand() % 2 == 0) ? -1 : -2;
                                board[x+shift][y] = "O";
                                moveCount++;
                                return;
                            }
                        }
                        if (x+1 < 3) {
                            if (board[x+1][y] == " ") {
                                int shift = (rand() % 2 == 0) ? 1 : -1;
                                board[x+shift][y] = "O";
                                moveCount++;
                                return;
                            }
                        }
                    }
                }
                if (y + 1 < 3) {
                    if (board[x][y+1] == " ") {
                        if (y + 2 < 3) {
                            if (board[x][y+2] == " ") {
                                int shift = rand() % 2 + 1;
                                board[x][y+shift] = "O";
                                moveCount++;
                                return;
                            }
                        }
                        if (y - 1 >= 0) {
                            if (board[x][y-1] == " ") {
                                int shift = (rand() % 2 == 0) ? 1 : -1;
                                board[x][y+shift] = "O";
                                moveCount++;
                                return;
                            }
                        }
                    }
                }
                if (y - 1 >= 0) {
                    if (board[x][y-1] == " ") {
                        if (y - 2 >= 3) {
                            if (board[x][y-2] == " ") {
                                int shift = rand() % 2 + 1;
                                board[x][y+shift] = "O";
                                moveCount++;
                                return;
                            }
                        }
                        if (y + 1 < 3) {
                            if (board[x][y+1] == " ") {
                                int shift = (rand() % 2 == 0) ? 1 : -1;
                                board[x+shift][y] = "O";
                                moveCount++;
                                return;
                            }
                        }
                    }
                }
                if (x == y) {
                    //Technically since x == y, we only need to check of x < 3, but I'll keep for intuitive purposes
                    if ( x+ 1 < 3 && y + 1 < 3) {
                        if (board[x+1][y+1] == " ") {
                            if (x + 2 < 3 && y + 2 < 3) {
                                if (board[x+2][y+2] == " ") {
                                    int shift = rand() % 2 + 1;
                                    board[x+shift][y+shift] = "O";
                                    moveCount++;
                                    return;
                                }
                            }
                            if (x - 1 >= 0 && y - 1 >= 0) {
                                if (board[x-1][y-1] == " ") {
                                    int shift = (rand() % 2 == 0) ? 1 : -1;
                                    board[x+shift][y+shift] = "O";
                                    moveCount++;
                                    return;
                                }
                            }
                        }
                    }
                }
                if (2-x == y) {
                    if (x + 1 < 3 && y - 1 >= 0) {
                        if (board[x+1][y-1] == " ") {
                            if (x + 2 < 3 && y - 2 >= 0) {
                                if (board[x+2][y-2] == " ") {
                                    int shift = rand() % 2 + 1;
                                    board[x+shift][y-shift] = "O";
                                    moveCount++;
                                    return;
                                }
                            }
                            if (x - 1 >= 0 && y + 1 < 3) {
                                if (board[x-1][y+1] == " ") {
                                    int shift = (rand() % 2 == 0) ? 1 : -1;
                                    board[x+shift][y-shift] = "O";
                                    moveCount++;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //Last resort, place O in any blank space; Usually this indicates a tie game
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (board[x][y] == " ") {
                board[x][y] = "O";
                moveCount++;
                return;
            }
        }
    }
}