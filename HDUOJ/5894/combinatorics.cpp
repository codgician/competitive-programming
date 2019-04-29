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
#define SIZE 1000010
using namespace std;

long long int factorialArr[SIZE];

const long long int mod = 1e9 + 7;

inline void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

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
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        long long int n, m, k;
        cin >> n >> m >> k;
        if (m == 1)
            cout << n << endl;
        else
            cout << n * getComb(n - m * k - 1, m - 1) % mod * fastPow(m, mod - 2) % mod << endl;
    }
    return 0;
}