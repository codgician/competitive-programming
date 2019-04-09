#include <bits/stdc++.h>
using namespace std;

#define SIZE 110

const int mod = 9999973;

long long int dp[SIZE][SIZE][SIZE];

long long int combN2(long long int n) {
    return  (n * (n - 1) / 2) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int row, column;
    cin >> row >> column;
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j <= column; j++) {
            for (int k = 0; j + k <= column; k++) {
                if (dp[i][j][k] == 0)
                    continue;
                dp[i + 1][j][k] = (dp[i + 1][j][k] + dp[i][j][k]) % mod;
                if (j + k < column)
                    dp[i + 1][j + 1][k] = (dp[i + 1][j + 1][k] + dp[i][j][k] * (column - j - k) % mod) % mod;
                if (j > 0)
                    dp[i + 1][j - 1][k + 1] = (dp[i + 1][j - 1][k + 1] + dp[i][j][k] * j % mod) % mod;
                if (j + k + 1 < column)
                    dp[i + 1][j + 2][k] = (dp[i + 1][j + 2][k] + dp[i][j][k] * combN2(column - j - k) % mod) % mod;
                if (j + k < column && j > 0)
                    dp[i + 1][j][k + 1] = (dp[i + 1][j][k + 1] + dp[i][j][k] * (column - j - k) % mod * j % mod) % mod;
                if (j > 1)
                    dp[i + 1][j - 2][k + 2] = (dp[i + 1][j - 2][k + 2] + dp[i][j][k] * combN2(j) % mod) % mod;
            }
        }
    }
    
    long long int ans = 0;
    for (int j = 0; j <= column; j++) {
        for (int k = 0; j + k <= column; k++) {
            ans = (ans + dp[row][j][k]) % mod;
        }
    }
    cout << ans << endl;
    return 0;
}
