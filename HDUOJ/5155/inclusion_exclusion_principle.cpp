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
#define SIZE 101
using namespace std;

const int mod = 1000000007;

long long int factorialArr[SIZE];

inline void initFactorial()
{
    factorialArr[0] = 1;   
    for (int i = 1; i < SIZE; i++)
    {
        factorialArr[i] = factorialArr[i - 1] * i % mod;
    }
}

inline long long int quickPow(long long int a, long long int n)
{
    long long int ans = 1;
    a %= mod;
    while (n > 0)
    {
        if (n & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

inline long long int getComb(long long int n, long long int m)
{
    if (n < m)
        return 0;
    return factorialArr[n] * quickPow(factorialArr[m], mod - 2) % mod * quickPow(factorialArr[n - m], mod - 2) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    initFactorial();
    int row, column;
    while (cin >> row >> column)
    {
        long long int ans = 0;
        for (int i = 0; i <= row; i++)
        {
            long long int cnt = getComb(row, i) * quickPow((quickPow(2, row - i) - 1 + mod) % mod, column);

            if (i & 1)
                ans -= cnt;
            else
                ans += cnt;
            ans = (ans + mod) % mod;
        }
        cout << ans << endl;
    }
    return 0;
}