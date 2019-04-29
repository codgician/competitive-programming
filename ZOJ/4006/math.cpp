#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

const int mod = 1e9 + 7;
long long int sec, pos;

long long int fastPow(long long int a, long long int n)
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
        ans = ans * (a * fastPow(b, mod - 2) % mod) % mod;
    }
    return ans;
}

long long int getAns(long long int p, long long int q)
{
    return p * fastPow(q, mod - 2) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> sec >> pos;
        pos = abs(pos);

        if (pos > sec)
        {
            cout << getAns(0, 1) << endl;
            continue;
        }
        cout << getAns(getComb(pos + sec, (sec << 1)), fastPow(4, sec)) << endl;
    }
    return 0;
}
