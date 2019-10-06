#include <bits/stdc++.h>
using namespace std;

#define SIZE 110

int arr[SIZE][SIZE], row, col; string str; 
int dirs[2][4] = {-1, 1, 0, 0, 0, 0, -1, 1};

int getDir(char ch) {
    if (ch == 'L')
        return 0;
    if (ch == 'R')
        return 1;
    if (ch == 'U')
        return 2;
    return 3;
}

int solve(int x, int y) {
    int ret = arr[x][y]; 
    for (const auto & ch : str) {
        int dir = getDir(ch);
        int x1 = x + dirs[1][dir], y1 = y + dirs[0][dir];
        const auto canMove = [x1, y1]() {
            return x1 >= 0 && y1 >= 0 && x1 < row && y1 < col;
        };
        if (!canMove())
            return 0;
        ret += arr[x1][y1]; x = x1, y = y1;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> row >> col >> str;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) 
                cin >> arr[i][j];  
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                cout << solve(i, j) << (j == col - 1 ? '\n' : ' ');    
    }    

    return 0;
}