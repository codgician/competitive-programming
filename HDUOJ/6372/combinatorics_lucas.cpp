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

#define PRIME_SIZE 100001
#define SIZE 1400000 // prime[1e5] + 1e5

const int mod = 1e9 + 7;

int primeArr[PRIME_SIZE], factorArr[SIZE], primePt;
long long int factorialArr[SIZE], invFactorialArr[SIZE];

inline long long int quickPow(long long int a, long long int n)
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
    {
        factorialArr[i] = factorialArr[i - 1] * i;
        if (factorialArr[i] >= mod)
            factorialArr[i] %= mod;
    }
}

inline void initInvFactorial()
{
    invFactorialArr[SIZE - 1] = quickPow(factorialArr[SIZE - 1], mod - 2);
    for (int i = SIZE - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

inline void initPrime()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            primeArr[primePt++] = i;
            if (primePt >= PRIME_SIZE)
                break;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];
        }
    }
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
    initPrime();
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int c, n, k;
        cin >> c >> n >> k;
        int p = primeArr[c - 1];

        long long int ans = 0;
        for (int j = 1; j <= k; j++)
        {
            long long int base = getComb(j + p, p - 1);
            if (base == 1)
            {
                ans += base * n % mod;
            }
            else
            {
                ans += (quickPow(base, n) - 1 + mod) % mod * quickPow(base - 1, mod - 2) % mod * base % mod; 
            }
            if (ans >= mod)
                ans %= mod;
        }
        cout << ans << endl;
    }
    return 0;
}