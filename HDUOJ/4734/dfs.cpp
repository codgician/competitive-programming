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
#define SIZE 10
#define MAX_FVAL 10010
using namespace std;

int dp[SIZE][MAX_FVAL];
int cntArr[SIZE];

inline int getFVal(int cnt)
{
    int tmp = 1, ans = 0;
    while (cnt)
    {
        ans += cnt % 10 * tmp;
        cnt /= 10;
        tmp <<= 1;
    }
    return ans;
}

int dfs(int pos, int cntFLim, bool hasLim)
{
    if (cntFLim < 0)
        return 0;
    if (pos < 0)
        return 1;
    if (!hasLim && dp[pos][cntFLim] != -1)
        return dp[pos][cntFLim];

    int ans = 0, lim = hasLim ? cntArr[pos] : 9;
    for (int i = 0; i <= lim; i++)
    {
        ans += dfs(pos - 1, cntFLim - i * (1 << pos), hasLim && i == lim);
    }

    if (!hasLim)
        dp[pos][cntFLim] = ans;
    return ans;
}

inline int work(int fLim, int cnt)
{
    int len = 0;
    while (cnt)
    {
        cntArr[len++] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len] = 0;
    return dfs(len - 1, getFVal(fLim), true);
}

int main()
{
    ios::sync_with_stdio(false);
    memset(dp, -1, sizeof(dp));
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int fLim, pt;
        cin >> fLim >> pt;
        cout << "Case #" << t << ": " << work(fLim, pt) << endl;
    }
    return 0;
}