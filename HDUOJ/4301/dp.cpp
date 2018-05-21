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
#define SIZE 1005
using namespace std;

int dp[SIZE][SIZE << 1][2];

const int mod = 100000007;

void init()
{
    memset(dp, 0, sizeof(dp));
    dp[1][1][1] = 1;
    dp[1][2][0] = 1;

    for (int i = 2; i <= 1000; i++)
    {
        for (int j = 1; j <= (i << 1); j++)
        {
            dp[i][j][1] = (dp[i - 1][j][0] << 1) + dp[i - 1][j][1] + dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1];
            if (dp[i][j][1] >= mod)
                dp[i][j][1] %= mod;

            dp[i][j][0] = dp[i - 1][j][0] + (dp[i - 1][j - 1][1] << 1) + (dp[i - 1][j - 1][0] << 1) + dp[i - 1][j - 2][0] + dp[i - 1][j - 2][1];
            if (dp[i][j][0] >= mod)
                dp[i][j][0] %= mod;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int len, num;
        cin >> len >> num;
        cout << (dp[len][num][0] + dp[len][num][1]) % mod << endl;
    }
    return 0;
}