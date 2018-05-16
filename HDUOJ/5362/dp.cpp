#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 2010
using namespace std;

long long int dp[SIZE][SIZE];
long long int powArr[SIZE];

const int mod = 1000000007;

int main()
{
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        int len, range;
        scanf("%d%d", &len, &range);

        powArr[0] = 1;
        for (int i = 1; i <= len; i++)
        {
            powArr[i] = powArr[i - 1] * range;
            if (powArr[i] >= mod)
                powArr[i] %= mod;
        }

        dp[1][0] = 0;
        dp[1][1] = range;

        for (int i = 2; i <= len; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                // dp[i][j] = dp[i - 1][j - 1] * (range - j + 1) + dp[i - 1][j + 1] * (j + 1)
                dp[i][j] = dp[i - 1][j - 1] * (range - j + 1);
                if (dp[i][j] >= mod)
                    dp[i][j] %= mod;
                dp[i][j] += dp[i - 1][j + 1] * (j + 1);
                if (dp[i][j] >= mod)
                    dp[i][j] %= mod;
            }
        }

        int ans = 0;
        for (int i = 1; i <= len; i++)
        {
            // ans += dp[i][i & 1] * powArr[len - i] * (len - i + 1)
            long long int cnt = dp[i][i & 1] * powArr[len - i];
            if (cnt >= mod)
                cnt %= mod;
            cnt *= len - i + 1;
            if (cnt >= mod)
                cnt %= mod;
            ans += cnt;
            if (ans >= mod)
                ans %= mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}