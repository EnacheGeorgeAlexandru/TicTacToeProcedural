#include <iostream>
#include <optional>
int board[3][3]{ 0,0,0,0,0,0,0,0,0 };
std::string player1, player2;
enum class PlayerId
{
    ONE,
    TWO
};

PlayerId turn = PlayerId::ONE;

std::string getPlayerName(PlayerId player)
{
    if (PlayerId::ONE == player)
    {
        return player1;
    }

    if (PlayerId::TWO == player)
    {
        return player2;
    }

    return "this is an error and should be treated via exceptions, but this is a story for another time";
}

bool isAnyMoveLeft()
{   
    for (int i = 0; i < 3; i++)
        for (int j = 0; i < 3; i++)
            if (board[i][j] == 0)
                return true;
    return false; // complex check to see if all board squares have been filled
}

std::optional<PlayerId> isAnyWinner()
{
    bool win_line = 1, win_col = 1, win_first_diag = 1, win_second_diag = 1;
    for (int i = 0; i < 3; i++)
    {
        win_line = 1; win_col = 1;
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 1)
                win_line = 0;
            if (board[j][i] != 1)
                win_col = 0;
            if (i == j)
                if (board[i][j] != 1)
                    win_first_diag = 0;
            if (i + j == 2)
                if (board[i][j] != 1)
                    win_second_diag = 0;
        }
        if (win_line == 1 || win_col == 1)
            return PlayerId::ONE;
    }
    if (win_first_diag == 1 || win_second_diag == 1)
        return PlayerId::ONE;

    win_line = 1, win_col = 1, win_first_diag = 1, win_second_diag = 1;
    for (int i = 0; i < 3; i++)
    {
        win_line = 1; win_col = 1;
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 2)
                win_line = 0;
            if (board[j][i] != 2)
                win_col = 0;
            if (i == j)
                if (board[i][j] != 2)
                    win_first_diag = 0;
            if (i + j == 2)
                if (board[i][j] != 2)
                    win_second_diag = 0;
        }
        if (win_line == 1 || win_col == 1)
            return PlayerId::TWO;
    }
    if (win_first_diag == 1 || win_second_diag == 1)
        return PlayerId::TWO;

    return std::nullopt;
}

bool isGameFinished() // unused function, but good example to see how functions tie together
{
    const auto winner = isAnyWinner();
    if (winner.has_value())
    {
        return true;
    }

    return isAnyMoveLeft();
}

bool isTie() // unused function, but good example to see how functions tie together
{
    return !isAnyWinner().has_value() && !isAnyMoveLeft();
}

void printBoard()
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

void takeNextTurn()
{
    int input_value = 0;
    if (turn == PlayerId::ONE) input_value = 1;
    if (turn == PlayerId::TWO) input_value = 2;

    int input_line, input_col;
    std::cout << getPlayerName(turn) << ": ";
    std::cin >> input_line >> input_col;
    if (input_line > -1 && input_line < 3 && input_col > -1 && input_col < 3 && board[input_line][input_col] == 0)
        board[input_line][input_col] = input_value;
    else
    {
        std::cout << "wrong input. try again.\n";
        takeNextTurn();
        return;
    }
    if (turn == PlayerId::ONE)
        turn = PlayerId::TWO;
    else if (turn == PlayerId::TWO)
        turn = PlayerId::ONE;
}

void doGameLoop()
{
    while (true)
    {
        printBoard();

        const auto winner = isAnyWinner();
        if (winner.has_value())
        {
            std::cout << "The game has finished. Player " << getPlayerName(winner.value()) << " has won, congratz!\n";
            return;
        }

        if (!isAnyMoveLeft())
        {
            std::cout << "The game has finished. It's a tie!\n";
            return;
        }

        takeNextTurn();
    }
}

void setupPlayers()
{
    std::cout << "Hello and welcome to Tic-Tac-Toe!\n";

    std::cout << "Enter first player's name:\n";
    std::cin >> player1;

    std::cout << "Enter second player's name:\n";
    std::cin >> player2;
}

int main()
{
    setupPlayers();
    doGameLoop();

    return 0;
}