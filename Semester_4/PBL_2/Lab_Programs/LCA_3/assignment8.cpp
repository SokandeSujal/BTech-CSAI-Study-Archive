#include <iostream>
using namespace std;

#define MAX 10

int board[MAX][MAX];
int n;

bool isSafe(int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
        {
            return false;
        }
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
    {
        if (board[i][j] == 1)
            return false;
    }
    return true;
}

bool solve(int row)
{

    if (row == n)
        return true;

    for (int col = 0; col < n; col++)
    {

        if (isSafe(row, col))
        {

            board[row][col] = 1;

            if (solve(row + 1))
                return true;

            board[row][col] = 0;
        }
    }

    return false;
}

void display()
{
    cout << "\nSolution:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "Enter value of N: ";
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 0;

    if (solve(0))
        display();
    else
        cout << "No solution exists!\n";

    return 0;
}
