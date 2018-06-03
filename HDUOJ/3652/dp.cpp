#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 20
using namespace std;

// k = 0: Does not have 13
// k = 1: Begins with 3, but does not have 13
// k = 2: Has 13
long long int dp[SIZE][SIZE][3];
int modArr[SIZE];
int cntArr[SIZE];

const int mod = 13;

inline void init()
{
    modArr[0] = 1;
    for (int i = 1; i < SIZE; i++)
        modArr[i] = modArr[i - 1] * 10 % mod;

    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                int nextRem = (j + modArr[i] * k) % mod;

                if (k == 1)
                {
                    dp[i + 1][nextRem][0] -= dp[i][j][1];
                    dp[i + 1][nextRem][2] += dp[i][j][1];
                }
                if (k == 3)
                {
                    dp[i + 1][nextRem][1] += dp[i][j][0];
                }

                dp[i + 1][nextRem][0] += dp[i][j][0];
                dp[i + 1][nextRem][2] += dp[i][j][2];
            }
        }
    } 
}

inline long long int work(long long int cnt)
{
    long long int ans = 0;
    int len = 0, cntMod = 0;
    while (cnt)
    {
        cntArr[++len] = cnt % 10;
        cnt /= 10;
    }
    cntArr[len + 1] = 0;

    bool has13 = false;
    for (int i = len; i > 0; cntMod = (cntMod + cntArr[i] * modArr[i - 1]) % 13, i--)
    {
        for (int j = 0; j < cntArr[i]; j++)
        {
            int restMod = (mod - (cntMod + j * modArr[i - 1]) % mod) % mod;
            if (has13)
                ans += dp[i - 1][restMod][0];
            ans += dp[i - 1][restMod][2];
        }

        if (has13)
            continue;

        if (cntArr[i + 1] == 1 && cntArr[i] > 3)
            ans += dp[i][(mod - cntMod) % mod][1];
        if (cntArr[i] > 1)
            ans += dp[i - 1][(mod - (cntMod + modArr[i - 1]) % mod) % mod][1];
        if (cntArr[i + 1] == 1 && cntArr[i] == 3)
            has13 = true;
    }
    return ans;
}


int main()
{
    ios::sync_with_stdio(false);
    init();
    long long int num;
    while (cin >> num)
    {
        cout << work(num + 1) << endl;
    }
    return 0;
}