#include<iostream>

class connect4{
    private:
        const int N_ROWS = 6;
        const int N_COLS = 7;
        const int CONSECUTIVE_CELLS_REQUIRED = 4;
        char board[N_ROWS][N_COLS];
        int currentTurn = 1;
        // check if a certain (x, y) is inside the playing ground
        bool validRow(int x){
            return (x >= 0 && x < N_ROWS);
        }
        bool validCol(int y){
            return (y >= 0 && y < N_COLS);
        }
        bool valid(int x, int y){
            return (validRow(x) & validCol(y));
        }
        // check if all the 
        bool allSameColor(int row, int col, int dx, int dy, char color){
            for(int i = 0; i < CONSECUTIVE_CELLS_REQUIRED; i++){
                int curRow = row + dx * i;
                int curCol = col + dy * i;
                if(!valid(curRow, curCol)) return 0;
                if(board[curRow][curCol] != color) return 0;
            }
            return 1;
        }
        // return 0 if no one has won yet, 1 if first player (RED) won, 2 if second player (BLUE) won
        int win(){
            for(int i = 0; i < N_ROWS; i++){
                for(int j = 0; j < N_COLS; j++){
                    // (i, j) is the first cell in four consecutive cells that we want to check for
                    // the direction is determined by the position of the second cell relative to first cell,
                    // which can be anything in {-1, 0, 1} x {-1, 0, 1} except for (0, 0)
                    for(int k = -1; k <= 1; k++){
                        for(int h = -1; h <= 1; h++){
                            if(k == 0 && h == 0) continue;
                            if(allSameColor(i, j, k, h, 'R')) return 1;
                            if(allSameColor(i, j, k, h, 'B')) return 2;
                        }
                    }
                }
            }
            return 0;
        }

    public:
        void winMessage(int whoWin){
            if(whoWin <= 0 || whoWin > 2){
                std::cout << "WRONG CALL\n";
                return;
            }
            std::cout << "PLAYER " << whoWin << " WINS\n";
            return;
        }
        void move(int turn, int moveCol, char move){
            if(turn != currentTurn){
                std::cout << "WRONG MOVE\n";
                return;
            }
            if(!validCol(moveCol)){
                std::cout << "INVALID COLUMN\n";
                return;
            }
            int moveRow = N_ROWS - 1;
            while(moveRow >= 0 && board[moveRow][moveCol] != '.') moveRow--;
            if(moveRow < 0){
                std::cout << "COLUMN IS FULL\n";
                return;
            }
            if(currentTurn == 1){
                board[moveRow][moveCol] = 'R';
            }
            else{
                board[moveRow][moveCol] = 'B';
            }
            int whoWin = win();
            if(whoWin > 0) winMessage(whoWin);
            currentTurn = (currentTurn == 1 ? 2 : 1);
        }
        void init(){
            currentTurn = 1;
            for(int i = 0; i < N_ROWS; i++){
                for(int j = 0; j < N_COLS; j++){
                    board[i][j] = '.';
                }
            }
        }
};