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
using namespace std;

#define SIZE 20
#define SUM_SIZE 1600

int cntArr[SIZE];
long long int dp[SIZE][SIZE][SUM_SIZE];

long long int dfs(int pos, int pivotPt, int cntSum, bool hasLim)
{
    if (pos < 0)
        return cntSum == 0;
    if (cntSum < 0)
        return 0;
    if (!hasLim && dp[pos][pivotPt][cntSum] != -1)
        return dp[pos][pivotPt][cntSum];

    long long int ans = 0;
    int lim = hasLim ? cntArr[pos] : 9;
    for (int i = 0; i <= lim; i++)
    {
        ans += dfs(pos - 1, pivotPt, cntSum + (pos - pivotPt) * i, hasLim && i == lim);
    }

    if (!hasLim)
        dp[pos][pivotPt][cntSum] = ans;
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
        
    long long int ans = 0;
    for (int i = 0; i < len; i++)
    {
        ans += dfs(len - 1, i, 0, true);
    }
    return ans - (len - 1); // 0, 00, 000 ...
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        cout << work(rightPt) - work(leftPt - 1) << endl;
    }

    return 0;
}