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
    int count=0;
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
            cout << value << " at (" << y << ", " << x << ")\n";
            count++;
            board.main_board[y-1][x-1]=value;
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
    cout<<count<<endl;
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
int main()
{

    designSudoku board;
    initialize_board(board);
    fill_values(board);
    display_board(board);
}
