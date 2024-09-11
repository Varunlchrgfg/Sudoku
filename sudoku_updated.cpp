#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class designSudoku
{
public:
    int main_board[9][9];
    bool row[9][9];
    bool column[9][9];
    bool board_input[9][9];
    bool squares[3][3][9];
    int singledimensionboard[81] = {0};
};
void fill_values(designSudoku &board)
{
    int count = 0;
    int x, y, value;
    srand(time(0));
    cout << "Values will be displayed here:-";
    for (int i = 0; i < 20; i++)
    {
        x = rand() % 9 ;
        y = rand() % 9 ;
        value = rand() % 9 + 1;
        if (board.main_board[y][x] == 0)
        {
            // cout << value << " at (" << y << ", " << x << ")\n";
            count++;
            board.main_board[y][x] = value;
            board.board_input[y][x] = true;
            board.row[y][value - 1] = true;
            board.column[x][value - 1] = true;
            board.squares[y / 3][x / 3][value - 1] = true;
        }
        else
        {
            i--;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board.singledimensionboard[9 * i + j] = board.main_board[i][j];
        }
    }
    cout << count << endl;
}
void initialize_board(designSudoku &board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board.main_board[i][j] = 0;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board.board_input[i][j] = false;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board.row[i][j] = false;
        }
    }
    cout << endl;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board.column[i][j] = false;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                board.squares[i][j][k] = false;
            }
        }
    }
}
void display_board(designSudoku &board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << board.main_board[i][j] << " ";
        }
        cout << endl;
    }
}
void calculate_solution(designSudoku &board)
{
    int positionatcell = 0;
    bool cellPassed = false;
    while (positionatcell < 81)
    {
        cout << positionatcell << " " << endl;
        cellPassed = true;
        if (board.board_input[positionatcell / 9][positionatcell % 9])
        {
            positionatcell++;
            continue;
        }
        int currentcellvalue = board.singledimensionboard[positionatcell];
        resetthevalue(positionatcell, board);

        cout<<"-";
        for(int i=(currentcellvalue+1);i<=9;i++){
            if(cell_value(positionatcell,i,board)){
                save_value(positionatcell,i,board);
                cellPassed=true;
                positionatcell++;
                break;
            }
        }
        if(!cellPassed){
        positionatcell--;
        while(board.board_input[positionatcell/9][positionatcell%9])
        positionatcell--;
        }
    }
}
void save_value(int positionatcell, int i,designSudoku &board){
    board.singledimensionboard[positionatcell]=i;
    board.row[positionatcell/9][i-1]=true;
    board.column[positionatcell%9][i-1]=true;
    board.squares[positionatcell/27][(positionatcell%9)/3][i-1]=true;
}
int cell_value(int positionatcell,int i,designSudoku &board){
    int y=0,x=0;
    y=positionatcell/9;
    x=positionatcell%9;

    if(board.column[x][i-1]==true)
    return 0;
    if(board.row[y][i-1]==true)
    return 0;
    if(board.squares[y/3][x/3][i-1]==true)
    return 0;
    else
    return 1;
}
void resetthevalue(int currentcellpostion, designSudoku &board)
{
    if (!board.singledimensionboard[currentcellpostion])
        return;
    int valueneedtoreset = board.singledimensionboard[currentcellpostion];
    board.row[currentcellpostion / 9][valueneedtoreset - 1] = false;
    board.column[currentcellpostion % 9][valueneedtoreset - 1] = false;
    board.squares[currentcellpostion / 27][(currentcellpostion % 9) / 3][valueneedtoreset - 1] = false;
    board.singledimensionboard[currentcellpostion] = 0;
}
int main()
{

    designSudoku board;
    initialize_board(board);
    fill_values(board);
    display_board(board);
    calculate_solution(board);
}
