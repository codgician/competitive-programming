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
using namespace std;

int dp[SIZE][SIZE];
int cntArr[SIZE];

int dfs(int pos, int prevVal, bool isZero, bool hasLim)
{
    if (pos < 0)
        return isZero ? 0 : 1;
    if (!hasLim && dp[pos][prevVal] != -1)
        return dp[pos][prevVal];

    int ans = 0, lim = hasLim ? cntArr[pos] : 9;
    if (isZero)
    {
        ans += dfs(pos - 1, 0, true, hasLim && 0 == lim);
    }
    for (int i = 1; i <= lim; i++)
    {
        if (isZero)
            ans += dfs(pos - 1, i, false, hasLim && i == lim);
        else if (prevVal % i == 0)
            ans += dfs(pos - 1, i, false, hasLim && i == lim);
    }

    if (!hasLim)
        dp[pos][prevVal] = ans;

    return ans;
}

inline int work(int cnt)
{
    int len = 0;
    while (cnt)
    {
        cntArr[len++] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len] = 0;
    return dfs(len - 1, 0, true, true);
}

int main()
{
    ios::sync_with_stdio(false);
    memset(dp, -1, sizeof(dp));
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        cout << work(rightPt) - work(leftPt - 1) << endl;
    }
    return 0;
}