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

int primeArr[SIZE], minFacArr[SIZE], primePt;
vector<int> facArr[SIZE];
int posArr[SIZE];

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
    int len;
    while (cin >> len)
    {
        memset(posArr, -1, sizeof(posArr));
        for (int i = 0; i < len; i++)
        {
            int cnt;
            cin >> cnt;
            for (int j = 0; j < primePt && primeArr[j] * primeArr[j] <= cnt; j++)
            {
                if (cnt % primeArr[j] > 0)
                    continue;
                facArr[i].push_back(primeArr[j]);
                while (cnt % primeArr[j] == 0)
                    cnt /= primeArr[j];
            }
            if (cnt > 1)
                facArr[i].push_back(cnt);
        }

        long long int ans = 0;
        for (int i = 0; i < len; i++)
        {
            for (int fac : facArr[i])
            {
                ans += 1ll * (len - i) * (i - posArr[fac]);
                posArr[fac] = i;
            }
        }
        cout << ans << endl;
    }

    return 0;
}