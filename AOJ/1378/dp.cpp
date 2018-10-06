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
using namespace std;

#define SIZE 101

long long int dp[SIZE][2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int targetLen, thickLen;
    while (cin >> targetLen >> thickLen)
    {
        memset(dp, 0, sizeof(dp));
        dp[1][0] = 1;
        dp[thickLen][0] = 1;
        for (int i = 2; i <= targetLen; i++)
        {
            dp[i][0] += dp[i - 1][1];
            if (i > thickLen)
                dp[i][0] += dp[i - thickLen][1];
            dp[i][1] += dp[i - 1][0];
        }

        long long int ans = 0;
        for (int i = 1; i <= targetLen; i++)
        {
            ans += dp[i][0];
        }
        cout << ans << endl;
    }

    return 0;
}