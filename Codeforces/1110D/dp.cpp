#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
#include <cassert>
using namespace std;

#define SIZE 1000010

int arr[SIZE], dp[SIZE][3][3];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(arr, 0, sizeof(arr));

    int len, num;
    cin >> len >> num;
    for (int i = 0; i < len; i++)
    {
        int cnt;
        cin >> cnt;
        arr[cnt]++;
    }

    memset(dp, -1, sizeof(dp));
    dp[0][0][0] = 0;
    for (int i = 0; i <= num; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (dp[i][j][k] == -1)
                    continue;
                int lim = arr[i + 1] - j - k;
                for (int t = 0; t <= min(lim, 2); t++)
                    dp[i + 1][k][t] = max(dp[i + 1][k][t], dp[i][j][k] + t + (lim - t) / 3);
            }
        }
    }

    cout << dp[num + 1][0][0] << endl;

    return 0;
}