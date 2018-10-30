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

#define SIZE 2010

int dp[SIZE];
long long int fiboPfxSum[SIZE];
int fiboPt;

void initFiboPfxSum()
{
    fiboPfxSum[0] = 0;
    fiboPfxSum[1] = 1;
    fiboPfxSum[2] = 2;

    long long int prev = 1, cnt = 1;
    fiboPt = 3;
    while (fiboPt < SIZE && fiboPfxSum[fiboPt - 1] <= 1e18)
    {
        long long int nxt = cnt + prev;
        prev = cnt, cnt = nxt;
        fiboPfxSum[fiboPt] = fiboPfxSum[fiboPt - 1] + nxt;
        fiboPt++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int a, b, qNum;
    cin >> a >> b >> qNum;

    if (a == 2 && b == 1)
    {
        // Observation part: Fibonacci
        initFiboPfxSum();
        while (qNum--)
        {
            long long int cnt;
            cin >> cnt;

            if (cnt == 1)
            {
                cout << 0 << endl;
                continue;
            }

            int pos = lower_bound(fiboPfxSum + 0, fiboPfxSum + fiboPt, cnt - 1) - fiboPfxSum;
            cout << pos + 1 << endl;
        }

        return 0;
    }

    dp[1] = 0;
    for (int i = 2; i < SIZE; i++)
    {
        dp[i] = INT_MAX;
        for (int j = 1; j < i; j++)
        {
            dp[i] = min(dp[i], max(dp[j] + a, dp[i - j] + b));
        }
    }

    while (qNum--)
    {
        int cnt;
        cin >> cnt;
        cout << dp[cnt] << endl;
    }    

    return 0;
}