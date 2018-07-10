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

#define SIZE 1010

const int mod = 998244353;

int arr[SIZE];
long long int dp[SIZE];
long long int factorialArr[SIZE];

inline void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

long long int quickPow(long long int a, long long int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

long long int getComb(long long int n, long long int m)
{
    if (n < m)
        return 0;
    return factorialArr[n] * quickPow(factorialArr[m], mod - 2) % mod * quickPow(factorialArr[n - m], mod - 2) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    initFactorial();
    int len;
    cin >> len;
    for (int i = 0; i < len; i++)
    {
        cin >> arr[i];
    }

    dp[len] = 1;
    for (int i = len - 1; i >= 0; i--)
    {
        if (arr[i] <= 0)
            continue;

        for (int j = i + arr[i] + 1; j <= len; j++)
        {
            dp[i] += dp[j] * getComb(j - i - 1, arr[i]) % mod;
            dp[i] %= mod;
        }
    }

    long long int ans = 0;
    for (int i = 0; i < len; i++)
    {
        ans += dp[i];
        ans %= mod;
    }
    cout << ans << endl;

    return 0;
}

