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

long long int dp[SIZE][2];

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

        dp[0][0] = 0;
        dp[0][1] = 0;
        dp[1][0] = 0;
        dp[1][1] = twoPowK;

        long long int fac1 = (twoPowK - 1 + mod) % mod, fac2 = (twoPowK - 2 + mod) % mod, fac3 = (twoPowK - 3 + mod) % mod;
        long long int totNum = twoPowK;
        for (int i = 2; i <= n; i++)
        {
            dp[i][0] = (fac3 * dp[i - 1][0] % mod + fac2 * dp[i - 1][1] % mod + fac2 * (totNum - (dp[i - 1][0] + dp[i - 1][1]) % mod + mod) % mod) % mod;
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
            totNum = totNum * fac1 % mod;
        }

        cout << (dp[n][0] + dp[n][1]) % mod << endl;
    }
    return 0;
}