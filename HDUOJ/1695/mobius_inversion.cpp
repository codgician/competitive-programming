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

#define SIZE 100010

int primeArr[SIZE], minFacArr[SIZE], mu[SIZE], phi[SIZE], primePt;
int muSum[SIZE];
long long int phiSum[SIZE];

void init()
{
    phi[1] = 1;
    mu[1] = 1;
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
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

    muSum[0] = 0;
    phiSum[0] = 0;
    for (int i = 1; i < SIZE; i++)
    {
        phiSum[i] = phiSum[i - 1] + phi[i];
        muSum[i] = muSum[i - 1] + mu[i];
    }
}

long long int workMu(int n, int m)
{
    long long int ans = 0;
    for (int i = 1, j; i <= n; i = j + 1)
    {
        if (n / i == 0)
            break;
        j = min(n / (n / i), m / (m / i));
        ans += (long long int)(muSum[j] - muSum[i - 1]) * (n / i) * (m / i);
    }
    return ans;
}

long long int work(int n, int m)
{
    if (n > m)
        swap(n, m);
    return workMu(n, m) - phiSum[n] + (n > 0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        int a, b, c, d, k;
        cin >> a >> b >> c >> d >> k;
        long long int ans = 0;
        if (k > 0)
            ans = work(b / k, d / k) - work(b / k, (c - 1) / k) + work((a - 1) / k, (c - 1) / k) - work((a - 1) / k, d / k);
        cout << "Case " << t << ": " << ans << endl;
    }

    return 0;
}