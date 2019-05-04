#include <bits/stdc++.h>
using namespace std;

#define SIZE 200010

int arr[2][SIZE][4];
int lim[4];
string str[2];

int id(char ch) {
    if (ch == 'L')
        return 0;
    if (ch == 'R')
        return 1;
    if (ch == 'U')
        return 2;
    return 3;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int row, column, len, x, y;
    cin >> row >> column >> len >> x >> y;
    for (int t = 0; t < 2; t++)
        cin >> str[t];

    lim[0] = y;  // Left
    lim[1] = column + 1 - y;  // Right
    lim[2] = x;  // Up
    lim[3] = row + 1 - x;  // Down

    for (int t = 0; t < 2; t++)
        for (int j = 0; j < 4; j++)
            arr[t][0][j] = 0;

    bool ans = true;
    for (int i = 1; i <= len && ans; i++) {
        for (int t = 0; t < 2; t++)
            for (int j = 0; j < 4; j++)
                arr[t][i][j] = arr[t][i - 1][j];
        int op;
        op = id(str[0][i - 1]);
        arr[0][i][op]++;

        if (arr[0][i][op] - arr[1][i - 1][op ^ 1] >= lim[op]) {
            ans = false; break;
        }

        op = id(str[1][i - 1]);
        arr[1][i][op] = min(lim[op] + arr[1][i][op ^ 1] - 1, arr[1][i][op] + 1);
    }

    if (ans)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
