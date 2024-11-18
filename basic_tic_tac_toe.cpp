#include <iostream>
#include <vector>
using namespace std;

vector<int> board(10, 2); // 10 spaces (index 0 unused), initialized to 2 (blank)
int turn = 1; // Keeps track of whose turn it is

// Function to display the board
void displayBoard() {
    for (int i = 1; i <= 9; i++) {
        if (board[i] == 3)
            cout << "X ";
        else if (board[i] == 5)
            cout << "O ";
        else
            cout << ". ";
        if (i % 3 == 0)
            cout << endl;
    }
    cout << endl;
}

// Procedure to make a move
void Go(int n) {
    board[n] = (turn % 2 == 1) ? 3 : 5; // 3 for X, 5 for O
    turn++;
}

// Procedure to check possible winning move
int Posswin(int p) {
    // Rows, Columns, and Diagonals to check
    vector<vector<int>> lines = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, // Rows
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, // Columns
        {1, 5, 9}, {3, 5, 7}             // Diagonals
    };

    for (const auto& line : lines) {
        int product = board[line[0]] * board[line[1]] * board[line[2]];
        if (product == p * p * 2) { // Check for winning product
            for (int cell : line) {
                if (board[cell] == 2) // Find the blank cell
                    return cell;
            }
        }
    }
    return 0; // No winning move found
}

// Procedure to find the "Make2" move
int Make2() {
    if (board[5] == 2)
        return 5; // Center is preferred
    // Return any corner (2, 4, 6, 8) if center is occupied
    vector<int> corners = {2, 4, 6, 8};
    for (int corner : corners) {
        if (board[corner] == 2)
            return corner;
    }
    return 0; // No valid move found
}

// Procedure to play the game
void playTicTacToe() {
    while (turn <= 9) {
        int move = 0;

        if (turn == 1)
            Go(1); // Turn 1: Go(1)
        else if (turn == 2)
            Go(board[5] == 2 ? 5 : 1); // Turn 2: Prefer center, else Go(1)
        else if (turn == 3)
            Go(board[9] == 2 ? 9 : 3); // Turn 3: Prefer corner, else Go(3)
        else if (turn == 4)
            Go(Posswin(3) ? Posswin(3) : Make2()); // Turn 4: Block X or Go(Make2)
        else if (turn == 5) {
            if (Posswin(3))
                Go(Posswin(3)); // Win if possible
            else if (Posswin(5))
                Go(Posswin(5)); // Block O
            else
                Go(board[7] == 2 ? 7 : 3); // Prefer corner
        } else if (turn == 6)
            Go(Posswin(5) ? Posswin(5) : (Posswin(3) ? Posswin(3) : Make2())); // Block O or X
        else if (turn == 7 || turn == 9)
            Go(Posswin(3) ? Posswin(3) : (Posswin(5) ? Posswin(5) : Make2())); // Prioritize win, block, or Go(Make2)
        else if (turn == 8)
            Go(Posswin(5) ? Posswin(5) : (Posswin(3) ? Posswin(3) : Make2())); // Similar to Turn 7/9

        // Display board after each turn
        cout << "Turn " << turn - 1 << ":\n";
        displayBoard();

        // Check if the game is over
        if (turn > 9) {
            cout << "Game Over! It's a draw.\n";
            break;
        }
    }
}

// Main function
int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    playTicTacToe();
    return 0;
}
