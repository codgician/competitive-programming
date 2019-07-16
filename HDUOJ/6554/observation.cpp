#include <bits/stdc++.h>
using namespace std;

#define SIZE 20

int base[4][4] = {1, 1, 1, 3, 2, 1, 3, 3, 2, 2, 4, 3, 2, 4, 4, 4};
int ans[SIZE][SIZE], row, column;

void draw(int x, int y) {
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++) 
            ans[x + i][y + j] = base[i][j];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while (cin >> row >> column) {
        if (row % 4 != 0 || column % 4 != 0) {
            cout << "no response\n";
            continue;
        }

        for (int i = 0; i < row; i += 4)
            for (int j = 0; j < column; j += 4)
                draw(i, j);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++)
                cout << ans[i][j];
            cout << '\n';
        }
    }

    return 0;
}