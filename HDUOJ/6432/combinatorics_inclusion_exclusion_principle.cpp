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

#define SIZE 200200

const int mod = 998244353;

long long int factorialArr[SIZE], invFactorialArr[SIZE];

long long int fastPow(long long int a, long long int n)
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

void initFactorial()
{
    factorialArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = fastPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

long long int getComb(int n, int m)
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
        int num;
        cin >> num;

        long long int ans = ((num & 1) ? -1 : 1);
        for (int i = 0; i < num; i++)
        {
            long long int cnt = getComb(num, i) * factorialArr[num - i - 1] % mod;
            if (i & 1)
                cnt = -cnt;
            ans = (ans + cnt + mod) % mod;
        }

        cout << ans << endl;
    }
    return 0;
}