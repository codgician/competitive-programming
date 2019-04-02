#include <bits/stdc++.h>
using namespace std;

#define DELTA_SIZE 17
#define SIZE 801

const int mod = 1e9 + 7;

int arr[SIZE][SIZE], dir[2][2] = {1, 0, 0, 1};
int dp[SIZE][SIZE][DELTA_SIZE][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int row, column, siz;
    cin >> row >> column >> siz;
    siz++;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cin >> arr[i][j];
            dp[i][j][arr[i][j] % siz][0] = 1;
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            for (int k = 0; k < siz; k++) {
                for (int w = 0; w < 2; w++) {
                    if (dp[i][j][k][w] == 0)
                        continue;
                    for (int d = 0; d < 2; d++) {
                        int i1 = i + dir[0][d], j1 = j + dir[1][d];
                        if (i1 >= row || j1 >= column)
                            continue;
                        int nextSiz = (k + ((w << 1) - 1) * arr[i1][j1] + siz) % siz;
                        dp[i1][j1][nextSiz][w ^ 1] = (dp[i1][j1][nextSiz][w ^ 1] + dp[i][j][k][w]) % mod;
                    }
                }
            }
        }
    }

    long long int ans = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            ans = (ans + dp[i][j][0][1]) % mod;
    cout << ans << endl;
    return 0;
}