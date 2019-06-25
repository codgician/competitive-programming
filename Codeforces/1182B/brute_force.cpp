#include <bits/stdc++.h>
using namespace std;

#define SIZE 510

bool arr[SIZE][SIZE];
int row, column, num, dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};

bool inBound(int x, int y) {
    return x >= 0 && x < row && y >= 0 && y < column;
}

bool check(const int x, const int y) {
    if (x == 0 || x == row - 1 || y == 0 || y == column - 1)
        return false;
    int cntNum = 1;
    for (int i = 0; i < 4; i++) {
        int x1 = x + dir[0][i], y1 = y + dir[1][i];
        if (!arr[x1][y1])
            return false;
        while (inBound(x1, y1) && arr[x1][y1]) {
            x1 += dir[0][i]; y1 += dir[1][i];
            cntNum++;
        }
    }
    return cntNum == num;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> row >> column;
    num = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            char ch; cin >> ch;
            if (ch == '*') {
                arr[i][j] = true; num++;
            } else {
                arr[i][j] = false;
            }
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (arr[i][j]) {
                if (check(i, j)) {
                    cout << "YES\n";
                    return 0;
                }
            }
        }
    }
    cout << "NO\n";
    return 0;
}