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

#define SIZE 20

long long int dp[SIZE][4];
int cntArr[SIZE];

long long int dfs(int pos, int nonZeroNum, bool hasLim)
{
    if (nonZeroNum > 3)
        return 0;
    if (pos < 0)
        return (nonZeroNum > 3) ? 0 : 1;
    if (!hasLim && dp[pos][nonZeroNum] != -1)
        return dp[pos][nonZeroNum];

    long long int ans = 0;
    int lim = hasLim ? cntArr[pos] : 9;

    ans += dfs(pos - 1, nonZeroNum, hasLim && 0 == lim);
    for (int i = 1; i <= lim; i++)
    {
        ans += dfs(pos - 1, nonZeroNum + 1, hasLim && i == lim);
    }

    if (!hasLim)
        dp[pos][nonZeroNum] = ans;
    return ans;
}

long long int work(long long int cnt)
{
    int len = 0;
    while (cnt)
    {
        cntArr[len++] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len] = 0;
    return dfs(len - 1, 0, true);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        long long int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        cout << work(rightPt) - work(leftPt - 1) << endl;
    }
    return 0;
}