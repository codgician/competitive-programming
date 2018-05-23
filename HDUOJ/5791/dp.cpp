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
#define SIZE 1010
using namespace std;

const int mod = 1000000007;

int fstArr[SIZE], sndArr[SIZE];
long long int dp[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int fstLen, sndLen;
    while (cin >> fstLen >> sndLen)
    {
        for (int i = 1; i <= fstLen; i++)
        {
            cin >> fstArr[i];
        }
        for (int i = 1; i <= sndLen; i++)
        {
            cin >> sndArr[i];
        }

        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= fstLen; i++)
        {
            for (int j = 1; j <= sndLen; j++)
            {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mod) % mod;
                if (fstArr[i] == sndArr[j])
                {
                    dp[i][j] += dp[i - 1][j - 1] + 1;
                    dp[i][j] %= mod;
                }
            }
        }

        cout << dp[fstLen][sndLen] % mod << endl; 
    }
    return 0;
}