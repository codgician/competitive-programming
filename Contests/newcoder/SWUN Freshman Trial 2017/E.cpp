#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
using namespace std;

const long long int mod = 1000000007;

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
int main()
{
    ios::sync_with_stdio(false);
    long long int blockNum, colorNum;
    cin >> blockNum >> colorNum;
    if (blockNum == 1)
    {
        cout << 0 << endl;
    }
    else
    {
        long long int tot = quickPow(colorNum, blockNum) % mod;
        long long int noSame = ((colorNum % mod) * quickPow(colorNum - 1, blockNum - 1)) % mod;
        long long int ans = tot - noSame;
        if (ans < 0)
            ans += mod;
        ans %= mod;
        cout << ans << endl;
    }
    return 0;
}
