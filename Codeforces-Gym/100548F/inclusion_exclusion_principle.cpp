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

const long long int mod = 1e9 + 7;

long long int invArr[SIZE];
long long int combArr[SIZE];

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

void initInv()
{
    invArr[1] = 1;
    for (int i = 2; i < SIZE; i++)
        invArr[i] = (mod - mod / i) * invArr[mod % i] % mod;
}

void initComb(int n, int m)
{
    combArr[0] = 1;
    for (int i = 1; i <= m; i++)
        combArr[i] = combArr[i - 1] * (n - i + 1) % mod * invArr[i] % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initInv();
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int n, m, k;
        cin >> n >> m >> k;

        int sgn = 1;
        initComb(k, k);
        long long int ans = 0;
        for (int i = k; i >= 1; i--)
        {
            ans = (ans + ((combArr[i] * i % mod * fastPow(i - 1, n - 1) % mod) * sgn + mod) % mod) % mod;
            sgn = -sgn;
        }

        initComb(m, k);
        ans = ans * combArr[k] % mod;
        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}
