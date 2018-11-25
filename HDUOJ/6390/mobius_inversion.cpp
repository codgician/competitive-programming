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

#define SIZE 1000010

int primeArr[SIZE], minFacArr[SIZE], mu[SIZE], muSum[SIZE], phi[SIZE], primePt;
long long int invArr[SIZE];

void init()
{
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    mu[1] = 1;
    phi[1] = 1;
    for (int i = 2; i < SIZE; i++)
    {
        if (minFacArr[i] == 0)
        {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }

        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++)
        {
            minFacArr[i * primeArr[j]] = primeArr[j];
            if (minFacArr[i] == primeArr[j])
            {
                mu[i * primeArr[j]] = 0;
                phi[i * primeArr[j]] = phi[i] * primeArr[j];
            }
            else
            {
                mu[i * primeArr[j]] = -mu[i];
                phi[i * primeArr[j]] = phi[i] * (primeArr[j] - 1);
            }
        }
    }

    muSum[1] = mu[1];
    for (int i = 2; i < SIZE; i++)
        muSum[i] = muSum[i - 1] + mu[i];
}

void initInv(int mod)
{
    invArr[1] = 1;
    for (int i = 2; i < SIZE; i++)
        invArr[i] = (mod - mod / i) * invArr[mod % i] % mod;
}

long long int work(int n, int m, int mod)
{
    if (n > m)
        swap(n, m);

    long long int ans = 0;
    for (int i = 1, j; i <= n; i = j + 1)
    {
        if (n / i == 0)
            break;
        j = min(n / (n / i), m / (m / i));
        ans += (long long int)(muSum[j] - muSum[i - 1]) * (n / i) * (m / i);
        ans %= mod;
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n, m, p;
        cin >> n >> m >> p;
        if (n > m)
            swap(n, m);
        initInv(p);

        long long int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans += i * invArr[phi[i]] % p * work(n / i, m / i, p) % p;
            ans %= p;
        }
        cout << ans << endl;
    }

    return 0;
}