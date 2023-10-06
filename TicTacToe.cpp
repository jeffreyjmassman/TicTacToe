#include "TicTacToe.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <thread>
#include <chrono>

using std::vector; using std::cout; using std::endl; using std::cin;
using std::string;

TicTacToe::TicTacToe() {
    playerScore = 0;
    computerScore = 0;
    tieScore = 0;
    keepPlaying = true;
    firstMove = true;
    for (int x = 0; x < 3; x++) {
        vector<string> vec;
        vector<string> vec2;
        board.push_back(vec);
        colors.push_back(vec2);
        for (int y = 0; y < 3; y++) {
            board[x].push_back(" ");
            colors[x].push_back(" ");
        }
    }
}

void TicTacToe::game() {
    while (keepPlaying) {
        if (firstMove) {
            this->initialize();
        }
        this->playerMakeMove();
        this->printGame();
        if (this->isWinner() || this->isTie()) {
            playAgain();
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        this->computerMakeMove();
        this->printGame();
        if (this->isWinner() || this->isTie()) {
            playAgain();
            continue;
        }
    }
}

void TicTacToe::printGame() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (board[x][y] == "X") {
                colors[x][y] = "\x1b[32mX\x1b[0m"; //green
                continue;
            }
            if (board[x][y] == "O") {
                colors[x][y] = "\x1b[31mO\x1b[0m"; //red
            }
        }
    }
    cout << "\n \n \n \n \n \n \n \n " << endl;
    cout << "                                   0   1   2" << endl;
    cout << "                                0  " << colors[0][0] << " | " << colors[1][0] << " | " << colors[2][0] << endl;
    //cout << "                                  ___________" << endl;
    cout << "                                  ===========" << endl;
    cout << "                                1  "<< colors[0][1] << " | " << colors[1][1] << " | " << colors[2][1] << endl;
    //cout << "                                  ___________" << endl;
    cout << "                                  ===========" << endl;
    cout << "                                2  "<< colors[0][2] << " | " << colors[1][2] << " | " << colors[2][2] << endl;
    cout << "\n \n \n \n \n \n \n \n" << endl;
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

void TicTacToe::resetGame() {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            board[x][y] = " ";
            colors[x][y] = " ";
        }
    }
    moveCount = 0;
    firstMove = true;
}

void TicTacToe::endGame() {
    cout << "Okay. Here are the results: \n" << endl;
    cout << "\x1b[32mYour score: \x1b[0m" << playerScore << endl;
    cout << "\x1b[31mComputer score: \x1b[0m" << computerScore << endl;
    cout << "\x1b[33mTies: \x1b[0m" << tieScore << "\n" << endl;
    cout << "Thanks for playing!" << endl;
    keepPlaying = false;
}

void TicTacToe::playAgain() {
    int play = 0;
    cout << "Do you want to play again? 1 or 0: ";
    cin >> play;
    if (play) {
        cout << "Okay! Starting new game. \n";
        this->resetGame();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
    else {
        this->endGame();
    }
}

bool TicTacToe::isWinner() {
    vector<bool> wincheck = this->winner();
    if (wincheck[0]) {
        if (wincheck[1]) {
            cout << "\x1b[32mCongratulations! You have won!\x1b[0m" << endl;
            playerScore++;
        }
        else {
            cout << "\x1b[31mSorry, but the computer has won.\x1b[0m" << endl;
            computerScore++;
        }
        return true;
    }
    return false;
}

bool TicTacToe::isTie() {
    if (moveCount == 9) {
        cout << "\x1b[33mThe game is a tie!\x1b[0m" << endl;
        tieScore++;
        return true;
    }
    return false;
}

void TicTacToe::initialize() {
    srand(time(0));
    this->printGame();
    int goFirst = 0;
    cout << "Do you want to go first? Type '1' for yes, '0' for no: ";
    cin >> goFirst;
    if (!goFirst) {
        cout << "Very well. The computer will make the first move." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        this->computerMakeMove();
        this->printGame();
    }
    cout << "Make a move! Type in first your desired x coordinate, then your y coordinate. \n" << endl;
    firstMove = false;
}