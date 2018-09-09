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

typedef struct _State
{
    long long int num;
    long long int sum;
    long long int sqrSum;
} State;

State dp[SIZE][SIZE][SIZE];
long long int cntArr[SIZE];
long long int factorialArr[SIZE];

const int mod = 1e9 + 7;

inline void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * 10 % mod;
}

State dfs(int pos, int rem, int sumRem, bool hasLim)
{
    if (pos == -1)
    {
        State ans = {(rem != 0 && sumRem != 0), 0, 0};
        return ans;
    }

    if (!hasLim && dp[pos][rem][sumRem].num != -1)
        return dp[pos][rem][sumRem];

    int lim = hasLim ? cntArr[pos] : 9;
    State ans = {0, 0, 0};
    for (int i = 0; i <= lim; i++)
    {
        if (i == 7)
            continue;

        int nextRem = (rem * 10 + i) % 7;
        int nextSumRem = (sumRem + i) % 7;
        State tmp = dfs(pos - 1, nextRem, nextSumRem, hasLim && i == lim);

        ans.num += tmp.num;
        ans.num %= mod;
        ans.sum += (tmp.sum + (i * factorialArr[pos] % mod) * tmp.num % mod) % mod;
        ans.sum %= mod;

        ans.sqrSum += (tmp.sqrSum + ((2 * factorialArr[pos] * i) % mod) * tmp.sum) % mod;
        ans.sqrSum %= mod;
        ans.sqrSum += ((tmp.num * factorialArr[pos]) % mod * factorialArr[pos] % mod * i * i % mod);
        ans.sqrSum %= mod;
    }

    if (!hasLim)
        dp[pos][rem][sumRem] = ans;
    return ans;
}

inline long long int work(long long int cnt)
{
    int len = 0;
    while (cnt)
    {
        cntArr[len++] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len] = 0;

    return dfs(len - 1, 0, 0, true).sqrSum;
}

int main()
{
    ios::sync_with_stdio(false);
    memset(dp, -1, sizeof(dp));
    initFactorial();
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int leftPt, rightPt;
        cin >> leftPt >> rightPt;
        cout << (work(rightPt) - work(leftPt - 1) + mod) % mod << endl;
    }
    return 0;
}