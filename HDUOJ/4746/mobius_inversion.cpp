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

#define SIZE 500010
#define LOG_SIZE 20

int primeArr[SIZE], factorArr[SIZE], mu[SIZE], pd[SIZE], primePt;
long long int sumArr[SIZE][LOG_SIZE];

void init()
{
    memset(factorArr, 0, sizeof(factorArr));
    primePt = 0;
    mu[1] = 1;
    pd[1] = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (factorArr[i] == 0)
        {
            factorArr[i] = i;
            pd[i] = 1;
            mu[i] = -1;
            primeArr[primePt++] = i;
        }

        for (int j = 0; j < primePt && primeArr[j] <= factorArr[i] && primeArr[j] <= (SIZE - 1) / i; j++)
        {
            factorArr[i * primeArr[j]] = primeArr[j];
            pd[i * primeArr[j]] = pd[i] + pd[primeArr[j]];
            if (factorArr[i] == primeArr[j])
                mu[i * primeArr[j]] = 0;
            else
                mu[i * primeArr[j]] = -mu[i];
        }
    }

    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 1; j * i < SIZE; j++)
        {
            sumArr[j * i][pd[i]] += mu[j];
        }
    }

    for (int j = 0; j < LOG_SIZE; j++)
        sumArr[0][j] = 0;
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 0; j < LOG_SIZE; j++)
        {
            sumArr[i][j] += sumArr[i - 1][j];
        }
    }
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 0; j < LOG_SIZE - 1; j++)
        {
            sumArr[i][j + 1] += sumArr[i][j];
        }
    }
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
        p = min(p, LOG_SIZE - 1);

        long long int ans = 0;
        for (int i = 1, j; i <= n; i = j + 1)
        {
            if (n / i == 0)
                break;
            j = min(n / (n / i), m / (m / i));
            ans += (sumArr[j][p] - sumArr[i - 1][p]) * (n / i) * (m / i);
        }
        cout << ans << endl;
    }

    return 0;
}