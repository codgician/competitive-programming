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
using namespace std;

const int mod = 1e9 + 7;

long long int quickPow(long long int a, long long int n)
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

long long int getComb(long long int n, long long int m)
{
    long long int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        long long int a = (m + i - n) % mod;
        long long int b = i % mod;
        ans = ans * (a * quickPow(b, mod - 2) % mod) % mod;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    return 0;
}