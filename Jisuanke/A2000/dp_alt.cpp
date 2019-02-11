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

#define SIZE 1000010

long long int fac1Pow[SIZE];
long long int dp[SIZE];

const long long int mod = 1e9 + 7;

long long int quickPow(long long int a, long long int n)
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n, k;
        cin >> n >> k;

        long long int twoPowK = quickPow(2, k);
        long long int fac1 = (twoPowK - 1 + mod) % mod, fac2 = (twoPowK - 2 + mod) % mod;

        fac1Pow[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            fac1Pow[i] = fac1Pow[i - 1] * fac1 % mod;
        }

        dp[1] = twoPowK;
        dp[2] = twoPowK * fac1 % mod;
        for (int i = 3; i <= n; i++)
        {
            dp[i] = (twoPowK * fac1Pow[i - 2] % mod * fac2 % mod + dp[i - 2]) % mod;
        }

        cout << dp[n] << endl;
    }
    return 0;
}