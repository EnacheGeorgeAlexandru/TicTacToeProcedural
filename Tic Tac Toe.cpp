#include <iostream>
int board[3][3]{ 0,0,0,0,0,0,0,0,0 };

void print_board(int board[3][3])
{
    for (int i = 0; i < 3; i++)
    {   
        std::cout << "------------" << "\n" << "|";
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                std::cout << "   |";
            if (board[i][j] == 1)
                std::cout << " x |";
            if (board[i][j] == 2)
                std::cout << " 0 |";
        }
        std::cout << '\n';
    }
    std::cout << "------------" << "\n";
}

void input(int (&board)[3][3], int player)
{
    int input_line, input_col;
    std::cout << "player " << player << ": ";
    std::cin >> input_line >> input_col;
    if (input_line > -1 && input_line < 3 && input_col > -1 && input_col < 3 && board[input_line][input_col] == 0)
        board[input_line][input_col] = player;
    else
    {
        std::cout << "wrong input. try again" << "\n";
        input(board, player);
    }
}

int check_win(int(&board)[3][3], int player)
{
    bool win_line = 1, win_col = 1, win_first_diag = 1, win_second_diag = 1;
    for (int i = 0; i < 3; i++)
    {
        win_line = 1; win_col = 1;
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != player)
                win_line = 0;
            if (board[j][i] != player)
                win_col = 0;
            if (i == j)
                if (board[i][j] != player)
                    win_first_diag = 0;
            if (i + j == 2)
                if (board[i][j] != player)
                    win_second_diag = 0;
        }
        if (win_line == 1 || win_col == 1)
            return 1;
    }
    if (win_first_diag == 1 || win_second_diag == 1)
        return 1;
    return 0;
}
int main()
{
    print_board(board);
    for(int i = 0; i < 9; i++)
    {
        input(board , i % 2 + 1);
        print_board(board);
        if (check_win(board, i % 2 + 1) == 1) {std::cout << "player " << i % 2 + 1 << " won";break;}
        if (i == 8) std::cout << "game ended. it's a tie!";
    } 
}
