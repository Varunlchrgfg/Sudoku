#include<iostream>
using namespace std;
class designSudoku{
    public:
    int main_board[9][9];
    bool row[9][9];
    bool column[9][9];
    bool squares[3][3][9];
};
void initialize_board(designSudoku board){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board.main_board[i][j]=0;
            cout<<board.main_board[i][j];
        }
        cout<<endl;
    }

}
int main(){

    designSudoku board;
    initialize_board(board);

}

