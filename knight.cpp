#include <iostream>
#include <vector>
using namespace std;

int solution_count = 0; // Renamed from 'count' to avoid ambiguity

void display(const vector<vector<char>>& board) {
    int m = board.size();
    int n = board[0].size();
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

bool can_attack(const vector<vector<char>>& board, int row, int col) {
    int m = board.size();
    int n = board[0].size();
    
    int movesX[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int movesY[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    
    for(int i = 0; i < 8; i++) {
        int newRow = row + movesX[i];
        int newCol = col + movesY[i];
        
        if(newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) {
            if(board[newRow][newCol] == 'K') {
                return true;
            }
        }
    }
    return false;
}

bool enough_cells_remaining(const vector<vector<char>>& board, int row, int col, int k) {
    int m = board.size();
    int n = board[0].size();
    int cells_left = (m * n) - (row * n + col);
    return cells_left >= k;
}

bool is_valid_position(const vector<vector<char>>& board, int row, int col, int k) {
    if (board[row][col] != '.') {
        return false;
    }
    if (can_attack(board, row, col)) {
        return false;
    }
    return true;
}

void kn(vector<vector<char>>& board, int k, int startI, int startJ) {
    int m = board.size();
    int n = board[0].size();
    
    if(k == 0) {
        display(board);
        solution_count++; // Updated to use the renamed variable
        return;
    }
    
    if(!enough_cells_remaining(board, startI, startJ, k)) {
        return;
    }
    
    for(int i = startI; i < m; i++) {
        int j_start = (i == startI) ? startJ : 0;
        
        for(int j = j_start; j < n; j++) {
            if(!is_valid_position(board, i, j, k)) {
                continue;
            }
            
            board[i][j] = 'K';
            kn(board, k-1, i, j+1);
            board[i][j] = '.';
            
            if(solution_count > 10000) {
                return;
            }
        }
    }
}

int main() {
    int m, n, k;
    
    cout << "Enter board dimensions (m n): ";
    cin >> m >> n;
    cout << "Enter number of knights (k): ";
    cin >> k;
    
    if(k > m*n) {
        cout << "Error: Too many knights for the board size!" << endl;
        return 1;
    }
    
    if(k > (m*n)/2) {
        cout << "Warning: Number of knights may be too high for a valid solution." << endl;
    }
    
    vector<vector<char>> board(m, vector<char>(n, '.'));
    
    cout << "\nSearching for solutions (limited to first 10000):\n" << endl;
    kn(board, k, 0, 0);
    
    cout << "\nTotal number of solutions found: " << solution_count << endl; // Updated variable name
    
    return 0;
}
