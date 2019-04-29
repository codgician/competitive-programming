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
long long int dp[SIZE][SIZE];

inline void initFactorial()
{
    factorialArr[0] = 1;   
    for (int i = 1; i < SIZE; i++)
    {
        factorialArr[i] = factorialArr[i - 1] * i % mod;
    }
}

inline long long int fastPow(long long int a, long long int n)
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
    return factorialArr[n] * fastPow(factorialArr[m], mod - 2) % mod * fastPow(factorialArr[n - m], mod - 2) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    initFactorial();
    int row, column;
    while (cin >> row >> column)
    {
        for (int i = 1; i <= row; i++)
            dp[i][1] = 1;
        for (int j = 1; j <= column; j++)
            dp[1][j] = 1;

        for (int i = 2; i <= row; i++)
        {
            for (int j = 2; j <= column; j++)
            {
                dp[i][j] = dp[i][j - 1] * ((fastPow(2, i) - 1 + mod) % mod) % mod;
                for (int k = 1; k < i; k++)
                {
                    dp[i][j] += dp[i - k][j - 1] * getComb(i, k) % mod * fastPow(2, i - k) % mod;
                    dp[i][j] %= mod;
                }
            }
        }
        cout << dp[row][column] << endl;
    }
    return 0;
}