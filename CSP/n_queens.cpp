#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Check if placing a queen at board[row] = col is safe
bool isSafe(int row, int col, vector<int> &board)
{
    for (int prevRow = 0; prevRow < row; prevRow++)
    {
        int prevCol = board[prevRow];

        // Same column OR same diagonal
        if (prevCol == col || abs(prevCol - col) == abs(prevRow - row))
        {
            return false;
        }
    }
    return true;
}

// Recursive function to place queens
void solveNQueens(int row, int n, vector<int> &board, vector<vector<int>> &solutions)
{
    if (row == n)
    {
        // All queens placed successfully
        solutions.push_back(board);
        return;
    }

    // Try placing queen in each column of this row
    for (int col = 0; col < n; col++)
    {
        if (isSafe(row, col, board))
        {
            board[row] = col;                           // Place queen
            solveNQueens(row + 1, n, board, solutions); // Recurse to next row
            board[row] = -1;                            // Backtrack: remove queen
        }
    }
}

void solveNQueensBB(int row, int n,
                    vector<int> &board,
                    vector<bool> &cols,
                    vector<bool> &diag1,
                    vector<bool> &diag2,
                    vector<vector<int>> &solutions)
{
    if (row == n)
    {
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (!cols[col] && !diag1[row - col + n - 1] && !diag2[row + col])
        {
            board[row] = col;

            // Mark column and diagonals as occupied
            cols[col] = diag1[row - col + n - 1] = diag2[row + col] = true;

            solveNQueensBB(row + 1, n, board, cols, diag1, diag2, solutions);

            cols[col] = diag1[row - col + n - 1] = diag2[row + col] = false;
            board[row] = -1; // Optional
        }
    }
}

// Display the board
void printSolutions(const vector<vector<int>> &solutions)
{
    int count = 1;
    for (const auto &solution : solutions)
    {
        cout << "Solution " << count++ << ":\n";
        int n = solution.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << (solution[i] == j ? "Q " : ". ");
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main()
{
    int n;
    cout << "Enter the number of queens (n): ";
    cin >> n;

    vector<int> board(n, -1); // board[i] = column position of queen in row i
    vector<vector<int>> solutions;

    int choice;
    cout << "Choose the method to solve N-Queens:\n";
    cout << "1. Backtracking\n";
    cout << "2. Branch and Bound (Optimized Backtracking)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        solveNQueens(0, n, board, solutions);
    }
    else if (choice == 2)
    {
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false); // row - col + (n - 1)
        vector<bool> diag2(2 * n - 1, false); // row + col
        solveNQueensBB(0, n, board, cols, diag1, diag2, solutions);
    }
    else
    {
        cout << "Invalid choice. Exiting program.\n";
        return 1;
    }
    
    printSolutions(solutions);
    return 0;
}
