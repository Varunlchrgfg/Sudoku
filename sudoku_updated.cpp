#include<iostream>
using namespace std;
class designSudoku{
    public:
    int main_board[9][9];
    bool row[9][9];
    bool column[9][9];
    bool board_input[9][9];
    bool squares[3][3][9];
};
void initialize_board(designSudoku board){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board.main_board[i][j]=0;
        }
    }

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board.board_input[i][j]=false;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board.row[i][j]=false;
        }
    }
    cout<<endl;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board.column[i][j]=false;
        }
    }

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<9;k++){
                board.squares[i][j][k]=false;
            }
        }
    }

}
int main(){

    designSudoku board;
    initialize_board(board);

}

