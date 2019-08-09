#include <bits/stdc++.h>
using namespace std;

#define SIZE 55

bool arr[SIZE][SIZE];
int pfx[SIZE][SIZE], dp[SIZE][SIZE][SIZE][SIZE];

int rectSum(int xl, int yl, int xr, int yr) {
    return pfx[xr][yr] + pfx[xl - 1][yl - 1] - pfx[xl - 1][yr] - pfx[xr][yl - 1];
} 

int dfs(int xl, int yl, int xr, int yr) {
    if (dp[xl][yl][xr][yr] != -1)
        return dp[xl][yl][xr][yr];

    // All white
    if (rectSum(xl, yl, xr, yr) == 0) {
        dp[xl][yl][xr][yr] = 0;
        return 0;
    }

    // All black
    dp[xl][yl][xr][yr] = max(xr - xl + 1, yr - yl + 1);
    if (rectSum(xl, yl, xr, yr) == (xr - xl + 1) * (yr - yl + 1))
        return dp[xl][yl][xr][yr];

    // Partition by x / y
    for (int i = xl; i < xr; i++)
        dp[xl][yl][xr][yr] = min(dp[xl][yl][xr][yr], dfs(xl, yl, i, yr) + dfs(i + 1, yl, xr, yr));
    for (int j = yl; j < yr; j++)
        dp[xl][yl][xr][yr] = min(dp[xl][yl][xr][yr], dfs(xl, yl, xr, j) + dfs(xl, j + 1, xr, yr));

    return dp[xl][yl][xr][yr];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int len; cin >> len;
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i <= len; i++)
        pfx[i][0] = 0, pfx[0][i] = 0;
    for (int i = 1; i <= len; i++) {
        for (int j = 1; j <= len; j++) {
            char ch; cin >> ch;
            arr[i][j] = (ch == '#');
            pfx[i][j] = arr[i][j];
        }
    }

    for (int i = 1; i <= len; i++)
        for (int j = 1; j <= len; j++)
            pfx[i][j] += pfx[i - 1][j];
    for (int j = 1; j <= len; j++)
        for (int i = 1; i <= len; i++)
            pfx[i][j] += pfx[i][j - 1];

    cout << dfs(1, 1, len, len) << '\n';
    return 0;
}