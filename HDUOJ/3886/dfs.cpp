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
#define SIZE 110
using namespace std;

int dp[SIZE][SIZE][10];
int cntArr[SIZE];
string rule;

const int mod = 100000000;

bool judge(char cntRule, int prev, int cnt)
{
    if (cntRule == '/')
        return prev < cnt;
    if (cntRule == '-')
        return prev == cnt;
    if (cntRule == '\\')
        return prev > cnt;
    return false;
}

long long int dfs(int pos, int rulePos, int prev, bool hasLim, bool frontZero)
{
    if (pos < 0)
        return rulePos == (int)rule.size();
    if (!hasLim && dp[pos][rulePos][prev] != -1)
        return dp[pos][rulePos][prev];

    int lim = hasLim ? cntArr[pos] : 9;
    long long int ans = 0;
    for (int i = 0; i <= lim; i++)
    {
        if (frontZero)
        {
            ans += dfs(pos - 1, rulePos, i, hasLim && i == lim, frontZero && i == 0);
        }
        else
        {
            if (rulePos < (int)rule.size() && judge(rule[rulePos], prev, i))
            {
                ans += dfs(pos - 1, rulePos + 1, i, hasLim && i == lim, frontZero && i == 0);
            }
            else if (rulePos > 0 && judge(rule[rulePos - 1], prev, i))
            {
                ans += dfs(pos - 1, rulePos, i, hasLim && i == lim, frontZero && i == 0);
            }
        }
        ans %= mod;
    }
    if (!hasLim)
    {
        dp[pos][rulePos][prev] = ans;
    }
    return ans;
}

int solve(string &str)
{
    int len = 0;
    for (int i = (int)str.size() - 1; i >= 0; i--)
    {
        cntArr[len++] = str[i] - '0';
    }
    cntArr[len] = 0;

    while (cntArr[len] == 0)
        len--;

    return dfs(len, 0, 0, true, true);
}

int main()
{
    while (cin >> rule)
    {
        memset(dp, -1, sizeof(dp));
        string leftPt, rightPt;
        cin >> leftPt >> rightPt;

        if (leftPt[leftPt.size() - 1] != '0')
        {
            leftPt[leftPt.size() - 1]--;
        }
        else
        {
            leftPt[leftPt.size()] = '9';
            for (int i = leftPt.size() - 2; i >= 0; i--)
            {
                if (leftPt[i] != '0')
                {
                    leftPt[i]--;
                    break;
                }
                leftPt[i] = '9';
                if (i == 0)
                {
                    leftPt.clear();
                    leftPt += '0';
                }
            }
        }

        int ans = (solve(rightPt) - solve(leftPt) + mod) % mod;
        cout << setw(8) << setfill('0') << ans << endl;
    }
    return 0;
}