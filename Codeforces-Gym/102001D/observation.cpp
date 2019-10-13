#include <bits/stdc++.h>
using namespace std;

#define SIZE 510

char arr[SIZE][SIZE];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int row, col, ans = 0, dryNum = 0; cin >> row >> col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            char ch; cin >> ch; arr[i][j] = ch;
            dryNum += (ch == '#' && (i == 0 || i == row - 1 || j == 0 || j == col - 1));
            if (row == 1) {
                ans += (ch == '.' && j > 0 && j < col - 1);
            } else if (col == 1) {
                ans += (ch == '.' && i > 0 && i < row - 1);
            } else {
                ans += (ch == '.' && i > 0 && i < row - 1 && j > 0 && j < col - 1);
            }
        }
    }

    dryNum -= (arr[0][0] == '#') + (arr[0][col - 1] == '#') + (arr[row - 1][0] == '#') + (arr[row - 1][col - 1] == '#');

    if (min(row, col) > 1 && max(row, col) >= 3) {
        if (min(row, col) == 2) {
            if (row == 2) {
                for (int i = 1; i < col - 1; i++)
                    ans += (arr[0][i] == '.' && arr[1][i] == '.');
            } else {
                for (int i = 1; i < row - 1; i++)
                    ans += (arr[i][0] == '.' && arr[i][1] == '.');
            }
        } else if (dryNum == 0) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}