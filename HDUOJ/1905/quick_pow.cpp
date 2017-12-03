#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

long long int mod;

bool isPrime(long long int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

long long int quickPow(long long int a, long long int n)
{
    int ans = 1;
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

int main()
{
    ios::sync_with_stdio(false);
    long long int p, a;
    while (cin >> p >> a)
    {
        if (p == 0 && a == 0)
            break;
        mod = p;
        if (!isPrime(p) && quickPow(a, p) % p == a)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
