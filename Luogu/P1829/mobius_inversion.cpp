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
#include <cassert>
using namespace std;

#define SIZE 10000010

const int mod = 20101009;

int primeArr[SIZE], factorArr[SIZE], primePt;
long long int f[SIZE], tfSum[SIZE];

void init()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    f[1] = 1;

    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            f[i] = ((1 - i) % mod + mod) % mod;
            primeArr[primePt++] = i;
        }
        
        for (int j = 0; j < primePt && primeArr[j] <= min(factorArr[i], (SIZE - 1) / i); j++)
        {
            factorArr[i * primeArr[j]] = primeArr[j];

            if (factorArr[i] == primeArr[j])
                f[i * primeArr[j]] = f[i];
            else
                f[i * primeArr[j]] = f[i] * f[primeArr[j]] % mod;
        }
    }

    tfSum[0] = 0;
    for (int i = 1; i < SIZE; i++)
    {
        tfSum[i] = (tfSum[i - 1] + i * f[i]) % mod;
    }
}

long long int getSum(long long int n)
{
    return ((n & 1) ? ((n + 1) >> 1) * n : (n >> 1) * (n + 1)) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();

    int n, m;
    cin >> n >> m;

    if (n > m)
        swap(n, m);

    long long int ans = 0;
    for (int i = 1, j; i <= n; i = j + 1)
    {
        if (n / i == 0 || m / i == 0)
            break;
        j = min(n / (n / i), m / (m / i));

        ans += getSum(n / i) * getSum(m / i) % mod * (tfSum[j] - tfSum[i - 1] + mod) % mod;
        ans %= mod;
    }

    cout << ans << endl;

    return 0;
}