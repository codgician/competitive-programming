#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define SIZE 2001
using namespace std;

const long long int mod = 1000000007;

long long int dp[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(dp, 0, sizeof(dp));
        int maxNum, len;
        cin >> maxNum >> len;

        for (int i = 1; i <= maxNum; i++)
            dp[1][i] = 1;

        for (int i = 1; i < len; i++)
        {
            for (int j = 1; j <= maxNum; j++)
            {
                for (int k = 1; j * k <= maxNum; k++)
                {
                    dp[i + 1][j * k] += dp[i][j];
                    if (dp[i + 1][j * k] > mod)
                        dp[i + 1][j * k] %= mod;
                }
            }
        }

        long long int ans = 0;
        for (int i = 1; i <= maxNum; i++)
        {
            ans += dp[len][i];
            if (ans > mod)
                ans %= mod;
        }
        cout << ans << endl;
    }
    return 0;
}
