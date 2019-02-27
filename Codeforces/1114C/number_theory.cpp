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

typedef struct _Fac
{
    long long int val, exp, num;
} Fac;

int primeArr[SIZE], minFacArr[SIZE], primePt;
Fac facArr[SIZE];

void initPrime()
{
    memset(minFacArr, 0, sizeof(minFacArr));
    primePt = 0;
    for (int i = 2; i < SIZE; i++)
    {
        if (minFacArr[i] == 0)
        {
            minFacArr[i] = i;
            primeArr[primePt++] = i;
        }
        for (int j = 0; j < primePt && primeArr[j] <= min(minFacArr[i], (SIZE - 1) / i); j++)
            minFacArr[i * primeArr[j]] = primeArr[j];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    initPrime();
    long long int n, base;
    cin >> n >> base;

    int facPt = 0;
    for (int i = 0; i < primePt && primeArr[i] * primeArr[i] <= base; i++)
    {
        if (base % primeArr[i] != 0)
            continue;
        int exp = 1;
        base /= primeArr[i];
        while (base % primeArr[i] == 0)
        {
            exp++;
            base /= primeArr[i];
        }
        facArr[facPt++] = {primeArr[i], exp, 0};
    }
    if (base > 1)
        facArr[facPt++] = {base, 1, 0};
    for (int i = 0; i < facPt; i++)
    {
        long long int cnt = n;
        while (cnt > 1)
        {
            facArr[i].num += cnt / facArr[i].val;
            cnt /= facArr[i].val;
        }
    }

    long long int ans = LLONG_MAX;
    for (int i = 0; i < facPt; i++)
        ans = min(ans, facArr[i].num / facArr[i].exp);
    cout << ans << endl;

    return 0;
}