#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

vector<vector<char>> board;


bool isRowValid(int x, int y, int num){
    for (int i = 0; i < board[x].size(); i ++){
        if (i == y) continue;
        if (board[x][i] == num) return false;
    }
    return true;
}

bool isColumnValid(int x, int y, int num){
    for (int i = 0; i < 9; i ++){
        if (x == i) continue;
        if (board[i][y] == num) return false;
    }
    return true;
}

bool isSquareValid(int x, int y, int num){
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

bool leftDValid(int x, int y, int num)
{
    for (int i = 0; i < 9; i ++){
        if (x == i && y == i) continue;
        if (board[i][i] == num) return false;
    }
    return true;
}


bool rightDValid(int x, int y, int num)
{   
    if (   (!(x == 0 && y == 8)) && (!(x == 1 && y == 7)) && (!(x == 2 && y == 6))
        && (!(x == 3 && y == 5)) && (!(x == 4 && y == 4)) && (!(x == 5 && y == 3))
        && (!(x == 6 && y == 2)) && (!(x == 7 && y == 1)) && (!(x == 8 && y == 0)))
    {
        return true;
    }

    int i = 0;
    int j = 8;
    while (i <= 8 && j >= 0)
    {
        if (x == i && y == j) {
            i ++;
            j --;
            continue;
        }
        if (board[i][j] == num) {
            return false;
        }
        i ++;
        j --;
    }
    return true;
}


bool isDiagonalValid(int x,int y,int num)
{   
    if (x == 4 && y == 4) return (leftDValid(x,y,num) && rightDValid(x,y,num));
    if (x == y) return leftDValid(x,y,num);
    return rightDValid(x,y,num);
}

bool isValid(int x, int y, int num){
    if (isRowValid(x,y,num) && isColumnValid(x,y,num) && isSquareValid(x,y,num) && isDiagonalValid(x,y,num))
        return true;
    return false;
}

bool solve(int leftover, int x){
    if (leftover == 0) return true;

    for (int i = x; i < board.size(); i ++){
        for (int j = 0; j < board[i].size(); j ++){
            if (board[i][j] != '.') continue;
            for (int k = 1; k <= 9; k ++){
                if (isValid(i,j,k + 48)){
                    board[i][j] = '0' + k;
                    if (solve(leftover - 1, i)) return true;    
                    board[i][j] = '.';
                }
            }
            return false;
        }
    }
    return false;
}


void solveSudoku() {
    int empty = 0;
    for (int i = 0; i < board.size(); i ++){
        for (int j = 0; j < board[i].size(); j ++){
            if (board[i][j] == '.') empty ++; 
        }
    }
    solve(empty, 0);
}

void printSudoku()
{
    for (int i = 0; i < board.size(); i ++){
        for (int j = 0; j < board[i].size(); j ++){
            cout << board[i][j];
        }
        cout << "\n";
    }
}


int main()
{
    string s;
    vector<char> row;
    for (int i = 0; i < 9; i ++)
    {
        cin >> s;
        for (int j = 0; j < s.size(); j++){
            row.push_back(s[j]);
        }
        board.push_back(row);
        row.clear();
    }

    solveSudoku();
    printSudoku();

    return 0;
}