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

void resetthevalue(int current_cell_position, designSudoku &board);
int cell_value(int position, int value, designSudoku &board);
void save_value(int position, int value, designSudoku &board);

void fill_values(designSudoku &board)
{
    int count = 0;
    int x, y, value;
    srand(time(0));
    cout << "Values will be displayed here:-";
    for (int i = 0; i < 20; i++)
    {
        x = rand() % 9 + 1;
        y = rand() % 9 + 1;
        value = rand() % 9 + 1;
        if (board.main_board[y - 1][x - 1] == 0)
        {
            // cout << value << " at (" << y << ", " << x << ")\n";
            count++;
            board.main_board[y - 1][x - 1] = value;
            board.board_input[y - 1][x - 1] = true;
            board.row[y - 1][value - 1] = true;
            board.column[x - 1][value - 1] = true;
            board.squares[(y - 1) / 3][(x - 1) / 3][value - 1] = true;
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

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
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
    while (positionatcell < 81) // Changed to < 81 for clarity
    {
        bool cellPassed = false; // Reset this at the beginning of the loop

        // Skip cells that are pre-filled
        if (board.board_input[positionatcell / 9][positionatcell % 9])
        {
            positionatcell++;
            continue; // Move to the next cell
        }

        resetthevalue(positionatcell, board);
        
        for (int i = 1; i <= 9; i++) // Check possible values from 1 to 9
        {
            if (cell_value(positionatcell, i, board))
            {
                save_value(positionatcell, i, board);
                cellPassed = true; // Mark that we successfully placed a value
                positionatcell++; // Move to the next cell
                break; // Exit the for loop after placing a value
            }
        }

        if (!cellPassed) // If no value was placed, backtrack
        {
            positionatcell--; // Move back to the previous cell
            while (positionatcell >= 0 && board.board_input[positionatcell / 9][positionatcell % 9])
            {
                positionatcell--; // Skip over filled cells
            }
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
    if(board.squares[x/3][y/3][i-1]==true)
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
