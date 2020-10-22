#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;


bool isRowValid(int x, int y, int num, vector<vector<char>>& board){
    for (int i = 0; i < board[x].size(); i ++){
        if (i == y) continue;
        if (board[x][i] == num) return false;
    }
    return true;
}

bool isColumnValid(int x, int y, int num, vector<vector<char>>& board){
    for (int i = 0; i < 9; i ++){
        if (x == i) continue;
        if (board[i][y] == num) return false;
    }
    return true;
}

bool isSquareValid(int x, int y, int num, vector<vector<char>>& board){
    int ibeg,jbeg; // top left corner cell of each 3x3 block
    if (x <= 2) ibeg = 0;
    else if (x <= 5) ibeg = 3;
    else ibeg = 6;

    if (y <= 2) jbeg = 0;
    else if (y <= 5) jbeg = 3;
    else jbeg = 6;

    for (int i = ibeg; i < ibeg + 3; i ++){
        for (int j = jbeg; j < jbeg + 3; j ++){
            if (x == i && y == j) continue;
            if (board[i][j] == num) return false;
        }
    }
    return true;

}

bool isValid(int x, int y, int num, vector<vector<char>>& board){
    if (isRowValid(x,y,num,board) && isColumnValid(x,y,num,board) && isSquareValid(x,y,num,board))
        return true;
    return false;
}

bool solve(int leftover, int x, vector<vector<char>>& board){
    if (leftover == 0) return true;

    for (int i = x; i < board.size(); i ++){
        for (int j = 0; j < board[i].size(); j ++){
            if (board[i][j] != '.') continue;
            for (int k = 1; k <= 9; k ++){
                if (isValid(i,j,k + 48,board)){
                    board[i][j] = '0' + k;
                    if (solve(leftover - 1, i,board)) return true;    
                    board[i][j] = '.';
                }
            }
            return false;
        }
    }
    return false;
}


void solveSudoku(vector<vector<char>>& board) {
    int empty = 0;
    for (int i = 0; i < board.size(); i ++){
        for (int j = 0; j < board[i].size(); j ++){
            if (board[i][j] == '.') empty ++; 
        }
    }
    solve(empty, 0, board);

}

void printSudoku(vector<vector<char>>&  board)
{
    for (int i = 0; i < board.size(); i ++){
        for (int j = 0; j < board[i].size(); j ++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}


int main()
{
    vector<vector<char>> board;
    board.push_back({'5','3','.','.','7','.','.','.','.'});
    board.push_back({'6','.','.','1','9','5','.','.','.'});
    board.push_back({'.','9','8','.','.','.','.','6','.'});
    board.push_back({'8','.','.','.','6','.','.','.','3'});
    board.push_back({'4','.','.','8','.','3','.','.','1'});
    board.push_back({'7','.','.','.','2','.','.','.','6'});
    board.push_back({'.','6','.','.','.','.','2','8','.'});
    board.push_back({'.','.','.','4','1','9','.','.','5'});
    board.push_back({'.','.','.','.','8','.','.','7','9'});  


    solveSudoku(board);
    printSudoku(board);

    return 0;
}