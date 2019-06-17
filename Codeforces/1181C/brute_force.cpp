#include <bits/stdc++.h>
using namespace std;

#define SIZE 1010

char arr[SIZE][SIZE];
int bel[SIZE][SIZE], rgt[SIZE][SIZE];
pair<int, int> rgtMin[SIZE][SIZE];
int row, column;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> row >> column;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cin >> arr[i][j];
            bel[i][j] = 1; rgt[i][j] = 1;
            rgtMin[i][j] = make_pair(1, 1);
        }
    }

    // Initialize right
    for (int i = 0; i < row; i++) {
        for (int j = column - 2; j >= 0; j--) {
            if (arr[i][j + 1] == arr[i][j]) {
                rgt[i][j] += rgt[i][j + 1];
                rgtMin[i][j] = make_pair(rgt[i][j], rgt[i][j]);
            }
        }
    }

    // Initialize below
    for (int j = 0; j < column; j++) {
        for (int i = row - 2; i >= 0; i--)
            if (arr[i][j] == arr[i + 1][j]) {
                bel[i][j] += bel[i + 1][j];
                rgtMin[i][j].second = min(rgtMin[i][j].second, rgtMin[i + 1][j].second);
            }

        for (int i = 1; i < row; i++)
            if (arr[i][j] == arr[i - 1][j])
                rgtMin[i][j].first = min(rgtMin[i][j].first, rgtMin[i - 1][j].first);
    }
    
    long long int ans = 0;
    for (int i = 0; i < row - 2; i++) {
        int j = 0;
        while (j < column) {
            int i2 = i + bel[i][j];
            int i3 = i2 + bel[i2][j];
            int cntHeight = i3 - i2;
            if (cntHeight == 0 || i2 >= row || i3 + cntHeight > row || i2 - i != cntHeight || bel[i3][j] < cntHeight) {
                j++;
                continue;
            }
            int cntWidth = min(min(rgtMin[i][j].second, rgtMin[i3 + cntHeight - 1][j].first), rgtMin[i2][j].second);
            ans += 1ll * cntWidth * (cntWidth + 1) / 2;
            j += cntWidth;
        }
    }

    cout << ans << '\n';
    return 0;
}