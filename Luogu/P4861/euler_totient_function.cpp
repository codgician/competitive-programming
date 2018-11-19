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

long long int quickPow(long long int a, long long int n, long long int mod)
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

int getPhi(int n)
{
    int ans = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            ans -= ans / i;
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        ans -= ans / n;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int m, k;
    cin >> m >> k;

    if (k == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    if (__gcd(m, k) != 1)
    {
        cout << "Let's go Blue Jays!" << endl;
        return 0;
    }

    int phi = getPhi(m);

    int ans = phi;
    for (int i = 2; i * i <= phi; i++)
    {
        if (phi % i == 0)
        {
            if (quickPow(k, i, m) == 1)
            {
                ans = min(ans, i);
                break;
            }

            if (quickPow(k, phi / i, m) == 1)
                ans = min(ans, phi / i);
        }
    }

    cout << ans << endl;

    return 0;
}