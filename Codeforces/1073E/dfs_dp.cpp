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

#define SIZE 30
#define STATE_SIZE 2048

typedef struct _State
{
    long long int num, sum;
} State;

State dp[SIZE][STATE_SIZE];
long long int factorialArr[SIZE];

int cntArr[SIZE];

const long long int mod = 998244353;

unsigned int k;

void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * 10 % mod;
}

State dfs(int pos, unsigned int cntState, bool hasLim, bool frontZero)
{
    unsigned int cntDiff = __builtin_popcount(cntState);
    if (cntDiff > k)
        return {0, 0};

    if (pos < 0)
        return {(cntDiff > k ? 0 : 1), 0};

    if (!hasLim && dp[pos][cntState].num != -1)
        return dp[pos][cntState];

    State ans = {0, 0};
    int lim = hasLim ? cntArr[pos] : 9;

    for (int i = 0; i <= lim; i++)
    {
        if (frontZero && i == 0)
        {
            State tmp = dfs(pos - 1, cntState, hasLim && i == lim, true);
            ans.num += tmp.num;
            ans.num %= mod;
            ans.sum += (tmp.sum + (i * factorialArr[pos] % mod) * tmp.num % mod) % mod;
            ans.sum %= mod;
            continue;
        }

        State tmp = dfs(pos - 1, (cntState | (1u << i)), hasLim && i == lim, false);
        ans.num += tmp.num;
        ans.num %= mod;
        ans.sum += (tmp.sum + (i * factorialArr[pos] % mod) * tmp.num % mod) % mod;
        ans.sum %= mod;
    }

    if (!hasLim)
        dp[pos][cntState] = ans;
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

    return dfs(len - 1, 0, true, true).sum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initFactorial();

    memset(dp, -1, sizeof(dp));
    long long int leftPt, rightPt;
    cin >> leftPt >> rightPt >> k;    

    cout << (work(rightPt) - work(leftPt - 1) + mod) % mod << endl;

    return 0;
}