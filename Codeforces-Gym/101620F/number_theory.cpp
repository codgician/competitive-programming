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

#define SIZE 20000010

long long int factorialArr[SIZE], invFactorialArr[SIZE];
long long int n, mod, rem;

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

inline void initFactorial(int initSize)
{
    factorialArr[0] = 1;
    for (int i = 1; i < initSize; i++)
        factorialArr[i] = factorialArr[i - 1] * i % mod;
}

inline void initInvFactorial(int initSize)
{
    invFactorialArr[initSize - 1] = quickPow(factorialArr[initSize - 1], mod - 2);
    for (int i = initSize - 2; i >= 0; i--)
        invFactorialArr[i] = invFactorialArr[i + 1] * (i + 1) % mod;
}

inline long long int getInv(int n)
{
    return factorialArr[n - 1] * invFactorialArr[n] % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> n >> mod >> rem)
    {
        if (n >= (mod << 1))
        {
            if (rem == 0)
            {
                if (n == 2)
                    cout << -1 << " " << -1 << endl;
                else
                    cout << 2 << " " << 1 << endl;
                continue;
            }

            cout << -1 << " " << -1 << endl;
            continue;
        }

        if (n >= mod)
        {
            // Problem lies in mod
            if (rem == 0)
            {
                if (n == 2)
                {
                    cout << -1 << " " << -1 << endl;
                }
                else
                {
                    if (mod == 2)
                        cout << 3 << " " << 1 << endl;
                    else
                        cout << 2 << " " << 1 << endl;
                }
                continue;
            }

            initFactorial(mod);
            initInvFactorial(mod);

            long long int k = factorialArr[mod - 1] * factorialArr[n % mod] % mod;
            long long int ans = getInv(k) * rem % mod;
            cout << mod << " " << ans << endl;
        }
        else
        {
            if (rem == 0)
            {
                cout << -1 << " " << -1 << endl;
                continue;
            }

            initFactorial(mod);
            initInvFactorial(mod);

            // (p - 2)! mod p = 1
            if (rem * (factorialArr[mod - 1] * invFactorialArr[n] % mod) % mod == mod - 1)
            {
                cout << -1 << " " << -1 << endl;
                continue;
            }

            int ans = -1, ansPt = -1;
            for (int i = n; i >= 2; i--)
            {
                long long int k = factorialArr[n] * getInv(i) % mod;
                long long int cntAns = getInv(k) * rem % mod;

                if (cntAns < i && cntAns != 0)
                {
                    ans = cntAns;
                    ansPt = i;
                    break;
                }
            }

            cout << ansPt << " " << ans << endl;
        }
    }

    return 0;
}