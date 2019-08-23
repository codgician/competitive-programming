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

int primeArr[SIZE], minFacArr[SIZE], mu[SIZE], sumArr[SIZE], primePt;

void initMu()
{
    mu[1] = 1;
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (minFacArr[i] == 0)
        {
            minFacArr[i] = i;
            mu[i] = -1;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++)
        {
            minFacArr[i * primeArr[j]] = primeArr[j];
            if (minFacArr[i] == primeArr[j])
                mu[i * primeArr[j]] = 0;
            else
                mu[i * primeArr[j]] = -mu[i];
        }
    }
}

void initSum()
{
    for (int i = 1; i * i < SIZE; i++)
    {
        for (int j = 1; i * i * j < SIZE; j++)
        {
            sumArr[i * i * j] += mu[j];
        }
    }

    sumArr[0] = 0;
    for (int i = 1; i < SIZE; i++)
    {
        sumArr[i] += sumArr[i - 1];
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
        int n, m;
        cin >> n >> m;
        if (n > m)
            swap(n, m);

        long long int ans = 0;
        for (int i = 1, j; i <= n; i = j + 1)
        {
            if (n / i == 0)
                break;
            j = min(n / (n / i), m / (m / i));
            ans += (long long int)(sumArr[j] - sumArr[i - 1]) * (n / i) * (m / i);
        }
        ans = (long long int)n * m  - ans;
        cout << ans << endl;
    }

    return 0;    
}