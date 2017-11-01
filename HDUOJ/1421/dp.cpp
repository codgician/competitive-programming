#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iomanip>
#define SIZE 2002
using namespace std;

int arr[SIZE], dp[SIZE][SIZE / 2];

bool cmpRule(int a, int b)
{
    return a < b;
}

int main()
{
    ios::sync_with_stdio(false);
    int n, k;
    while (cin >> n >> k)
    {
        for (int i = 1; i <= n; i++)
            cin >> arr[i];

        sort(arr + 1, arr + n + 1, cmpRule);

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                if (j == 0)
                    dp[i][j] = 0;
                else
                    dp[i][j] = INT_MAX;
            }
        }

        for (int i = 2; i <= n; i++)
        {
            for (int j = 1; j * 2 <= i; j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i - 2][j - 1] + (arr[i] - arr[i - 1]) * (arr[i] - arr[i - 1]));
            }
        }
        cout << dp[n][k] << endl;
    }
    return 0;
}
