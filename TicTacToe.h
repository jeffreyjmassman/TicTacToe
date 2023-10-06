#include <vector>
#include <string>

class TicTacToe {
    private:
        std::vector<std::vector<std::string> > board;
        int moveCount;
    public:
        void game();
        void printGame();
        void test();
        std::vector<bool> winner();
        void playerMakeMove();
        void computerMakeMove();
};