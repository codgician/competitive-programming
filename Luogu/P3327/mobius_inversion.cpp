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

#define SIZE 50010

int primeArr[SIZE], factorArr[SIZE], numArr[SIZE], mu[SIZE], d[SIZE];
long long int dSum[SIZE], muSum[SIZE];
int primePt;

void initMuAndD()
{
    mu[1] = 1;
    d[1] = 1;
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            mu[i] = -1;
            numArr[i] = 1;
            d[i] = 2;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];

            if (factorArr[i] == primeArr[j])
            {
                mu[i * primeArr[j]] = 0;
                numArr[i * primeArr[j]] = numArr[i] + 1;
                d[i * primeArr[j]] = d[i] / (numArr[i] + 1) * (numArr[i * primeArr[j]] + 1);
            }
            else
            {
                mu[i * primeArr[j]] = -mu[i];
                numArr[i * primeArr[j]] = 1;
                d[i * primeArr[j]] = d[i] * d[primeArr[j]];
            }
        }
    }
}

void initSum()
{
    muSum[0] = 0;
    dSum[0] = 0;
    for (int i = 1; i < SIZE; i++)
    {
        muSum[i] = muSum[i - 1] + mu[i];
        dSum[i] = dSum[i - 1] + d[i];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initMuAndD();
    initSum();

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
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
            ans += (muSum[j] - muSum[i - 1]) * dSum[n / i] * dSum[m / i];
        }
        cout << ans << endl;
    }

    return 0;
}