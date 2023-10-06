#include <vector>
#include <string>

class TicTacToe {
    private:
        std::vector<std::vector<std::string> > board;
        int moveCount;
        int playerScore;
        int computerScore;
        int tieScore;
        bool keepPlaying;
        bool firstMove;
    public:
        TicTacToe();
        void game();
        void printGame();
        std::vector<bool> winner();
        void playerMakeMove();
        void computerMakeMove();
        void resetGame();
        void endGame();
        void playAgain();
        bool isWinner();
        bool isTie();
        void initialize();
};