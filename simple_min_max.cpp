#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Constants for board states
const int BLANK = 2;
const int X = 3;  // Player
const int O = 5;  // AI

// Ratings for board positions (used to prioritize moves)
const int ratings[9] = {3, 2, 3, 2, 5, 2, 3, 2, 3};  // Corners: 3, Edges: 2, Center: 5

vector<int> board(9, BLANK);
int turn = 1;
int MAX_DEPTH = 4;

// Function prototypes
void displayBoard();
bool isBoardFull();
int checkWin();
int minimax(int depth, int player);
int bestMove();
void playerMove();
void go(int n, int player);
void playGame();
void setDepth(int depth);

// Function to display the current board
void displayBoard() {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) cout << endl;
        char symbol;
        if (board[i] == X) symbol = 'X';
        else if (board[i] == O) symbol = 'O';
        else symbol = ' ';
        cout << symbol << " ";
    }
    cout << endl;
}

// Function to check if the board is full
bool isBoardFull() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == BLANK) return false;
    }
    return true;
}

// Function to check for a winner
int checkWin() {
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };
    
    for (int i = 0; i < 8; i++) {
        int product = board[winPatterns[i][0]] * board[winPatterns[i][1]] * board[winPatterns[i][2]];
        if (product == X * X * X) return X;
        if (product == O * O * O) return O;
    }
    return 0;
}

// Minimax algorithm to evaluate moves
int minimax(int depth, int player) {
    int winner = checkWin();
    if (winner == X) return -10 + depth; // Penalize the AI for losing
    if (winner == O) return 10 - depth;  // Reward the AI for winning
    if (isBoardFull() || depth == MAX_DEPTH) return 0; // Draw or max depth reached

    int bestScore = (player == O) ? numeric_limits<int>::min() : numeric_limits<int>::max();

    for (int i = 0; i < 9; i++) {
        if (board[i] == BLANK) {
            board[i] = player;
            int score = minimax(depth + 1, (player == O) ? X : O);
            board[i] = BLANK;
            
            if (player == O)
                bestScore = max(bestScore, score);
            else
                bestScore = min(bestScore, score);
        }
    }
    return bestScore;
}

// Function to find the best move for the AI
int bestMove() {
    int bestScore = numeric_limits<int>::min();
    int move = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == BLANK) {
            board[i] = O;
            int score = minimax(0, X) + ratings[i]; // Use Minimax and add position rating
            board[i] = BLANK;
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

// Function for the player's move
void playerMove() {
    int move;
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> move;
        move--; // Map 1-9 to 0-8
        if (move >= 0 && move < 9 && board[move] == BLANK) {
            go(move, X); // Player is X
            break;
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

// Function to make a move on the board
void go(int n, int player) {
    board[n] = player;
}

// Function to set the depth of the Minimax algorithm
void setDepth(int depth) {
    MAX_DEPTH = depth;
}

// Main game loop
void playGame() {
    while (!isBoardFull() && checkWin() == 0) {
        displayBoard();

        if (turn % 2 == 1) { // Player's turn
            playerMove();
        } else { // AI's turn
            int move = bestMove();
            go(move, O);
            cout << "AI played at position " << (move + 1) << endl;
        }
        turn++;

        int winner = checkWin();
        if (winner == X) {
            displayBoard();
            cout << "You win!" << endl;
            return;
        } else if (winner == O) {
            displayBoard();
            cout << "AI wins!" << endl;
            return;
        }
    }

    displayBoard();
    cout << "It's a tie!" << endl;
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "You are X. The AI is O." << endl;

    int depth;
    cout << "Enter maximum depth for AI (1-4): ";
    cin >> depth;
    setDepth(depth);

    playGame();
    return 0;
}