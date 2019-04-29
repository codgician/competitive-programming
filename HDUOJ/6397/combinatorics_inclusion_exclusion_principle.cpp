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

#define SIZE 200020

const int mod = 998244353;

long long int factorialArr[SIZE], invFactorialArr[SIZE];

inline long long int fastPow(long long int a, long long int n)
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

inline void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

inline void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = fastPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

inline long long int getComb(int n, int m)
{
    if (m > n)
        return 0;
    return factorialArr[n] * invFactorialArr[m] % mod * invFactorialArr[n - m] % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initFactorial();
    initInvFactorial();
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n, m, k;
        cin >> n >> m >> k;

        if (k <= n - 1)
        {
            cout << getComb(m + k - 1, k) << endl;
        }
        else if (k > m * (n - 1))
        {
            cout << 0 << endl;
        }
        else
        {
            long long int ans = 0;
            for (int i = 0; i <= k / n; i++)
            {
                if (i & 1)
                    ans = (ans - getComb(m, i) * getComb(m + k - 1 - i * n, k - i * n) % mod + mod) % mod;
                else
                    ans = (ans + getComb(m, i) * getComb(m + k - 1 - i * n, k - i * n) % mod) % mod;
            }
            cout << ans << endl;
        }
    }
    return 0;
}