#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <climits>
#define SIZE 101
using namespace std;

int arr[SIZE][SIZE], dp[SIZE][SIZE];
int move_x[4] = {1, -1, 0, 0}, move_y[4] = {0, 0, 1, -1};
int row, column;

bool checkBoundary(int x, int y)
{
    return x >= 0 && x < row && y >= 0 && y < column;
}

int dfs(int x, int y)
{
    if (dp[x][y] > 0)
        return dp[x][y];

    dp[x][y] = 1;
    for (int i = 0; i < 4; i++)
    {
        int next_x = x + move_x[i];
        int next_y = y + move_y[i];
        if (arr[next_x][next_y] < arr[x][y] && checkBoundary(next_x, next_y))
        {
            dp[x][y] = max(dp[x][y], dfs(next_x, next_y) + 1);
        }
    }
    return dp[x][y];
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> row >> column;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cin >> arr[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            ans = max(ans, dfs(i, j));
        }
    }
    cout << ans << endl;
    return 0;
}
