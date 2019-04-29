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

const long long int mod = 1e9 + 7;

#define SIZE 100001
#define BLOCK_NUM 245

const int blockSize = 410;

long long int factorialArr[SIZE], invFactorialArr[SIZE];
long long int dp[SIZE][BLOCK_NUM];
int n, m;

inline long long int fastPow(long long int a, long long int n)
{
    long long int ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans *= a;
            if (ans >= mod)
                ans %= mod;
        }
        a *= a;
        if (a >= mod)
            a %= mod;
        n >>= 1;
    }
    return ans;
}

inline void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
    {
        factorialArr[i] = factorialArr[i - 1] * i;
        if (factorialArr[i] >= mod)
            factorialArr[i] %= mod;
    }
}

inline void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = fastPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
    {
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1);
        if (invFactorialArr[i] >= mod)
            invFactorialArr[i] %= mod;
    }
}

inline long long int getComb(long long int n, long long int m)
{
    if (m > n)
        return 0;
    long long int ans = factorialArr[n] * invFactorialArr[m];
    if (ans >= mod)
        ans %= mod;
    ans *= invFactorialArr[n - m];
    if (ans >= mod)
        ans %= mod;
    return ans;
}

void init()
{
    memset(dp, 0, sizeof(dp));

    dp[0][0] = 1;
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 0; (j + 1) * blockSize - 1 <= i + blockSize; j++)
        {
            dp[i][j] = ((dp[i - 1][j] << 1) % mod - getComb(i - 1, (j + 1) * blockSize - 1) + mod) % mod;
        }

        if (i % blockSize == 0)
        {
            dp[i][i / blockSize] = dp[i][i / blockSize - 1] + 1;
        }
    }
}

int main()
{
    initFactorial();
    initInvFactorial();
    init();
    int caseNum;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        scanf("%d%d", &n, &m);

        if (m == 0)
        {
            puts("1");
            continue;
        }

        int inBlock = (m + 1) / blockSize - 1, outBlock = (m + 1) % blockSize;
        long long int ans = 0;
        if (inBlock >= 0)
            ans = dp[n][inBlock];
        for (int i = 1; i <= outBlock; i++)
        {
            ans += getComb(n, (inBlock + 1) * blockSize + i - 1);
            if (ans >= mod)
                ans %= mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}