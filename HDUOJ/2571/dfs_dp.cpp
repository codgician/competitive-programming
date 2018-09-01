#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define N_SIZE 21
#define M_SIZE 1001
#define INF 999999
using namespace std;

int arr[N_SIZE][M_SIZE], dp[N_SIZE][M_SIZE];
int row, column;

int dfs(int x, int y)
{
    if (dp[x][y] != -INF)
        return dp[x][y];

    int ans = -INF;

    if (x + 1 < row)
        ans = max(ans, dfs(x + 1, y));
    if (y + 1 < column)
        ans = max(ans, dfs(x, y + 1));

    for (int k = 2; k * (y + 1) - 1 < column; k++)
    {
        ans = max(ans, dfs(x, k * (y + 1) - 1));
    }

    dp[x][y] = ans + arr[x][y];
    return dp[x][y];
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    for (int t = 0; t < caseNum; t++)
    {
        cin >> row >> column;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> arr[i][j];
                dp[i][j] = -INF;
            }
        }

        dp[row - 1][column - 1] = arr[row - 1][column - 1];

        cout << dfs(0, 0) << endl;
    }
    return 0;
}
