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
#define SIZE 20
using namespace std;

// k = 0: Does not have 13
// k = 1: Previous is 1, does not have 3
// k = 2: Has 13
long long int dp[SIZE][SIZE][3];
int cntArr[SIZE];

const int mod = 13;

long long int dfs(int len, int rem, int type, bool hasLim)
{
    if (len == 0)
        return rem == 0 && type == 2;
    if (!hasLim && dp[len][rem][type] != -1)
        return dp[len][rem][type];

    long long int ans = 0;
    int lim = hasLim ? cntArr[len] : 9;
    for (int i = 0; i <= lim; i++)
    {
        int cntRem = (rem * 10 + i) % mod;
        if (type == 2 || (type == 1 && i == 3))
            ans += dfs(len - 1, cntRem, 2, hasLim && i == lim);
        else
            ans += dfs(len - 1, cntRem, i == 1 ? 1 : 0, hasLim && i == lim);
    }

    if (!hasLim)
        dp[len][rem][type] = ans;
    return ans;
}

inline long long int work(long long int cnt)
{
    int len = 0;
    while (cnt)
    {
        cntArr[++len] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len + 1] = 0;

    return dfs(len, 0, 0, true);
}

int main()
{
    ios::sync_with_stdio(false);
    memset(dp, -1, sizeof(dp));
    long long int num;
    while (cin >> num)
    {
        cout << work(num) << endl;
    }
    return 0;
}