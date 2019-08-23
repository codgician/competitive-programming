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

int primeArr[SIZE], factorArr[SIZE], mu[SIZE], sumArr[SIZE];
int primePt;

void initMu()
{
    mu[1] = 1;
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            mu[i] = -1;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt; j++)
        {
            if (primeArr[j] > factorArr[i] || primeArr[j] > (SIZE - 1) / i)
                break;
            factorArr[i * primeArr[j]] = primeArr[j];

            if (factorArr[i] == primeArr[j])
                mu[i * primeArr[j]] = 0;
            else
                mu[i * primeArr[j]] = -mu[i];
        }
    }
}

void initSum()
{
    sumArr[0] = 0;
    for (int i = 1; i < SIZE; i++)
    {
        sumArr[i] = sumArr[i - 1] + mu[i];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    initMu();
    initSum();

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int n, m, d;
        cin >> n >> m >> d;
        if (n > m)
            swap(n, m);
        n /= d;
        m /= d;

        long long int ans = 0;
        for (int i = 1, j; i <= n; i = j + 1)
        {
            if (n / i == 0 || m / i == 0)
                break;
            j = min(n / (n / i), m / (m / i));
            ans += (long long int)(sumArr[j] - sumArr[i - 1]) * (n / i) * (m / i);
        }
        cout << ans << endl;
    }

    return 0;
}