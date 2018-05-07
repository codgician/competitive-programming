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
#define SIZE 3010
using namespace std;

long long int fstArr[SIZE], sndArr[SIZE];
long long int dp[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int len;
    cin >> len;
    for (int i = 1; i <= len; i++)
    {
        cin >> fstArr[i];
    }
    for (int i = 1; i <= len; i++)
    {
        cin >> sndArr[i];
    }

    long long int ans = 0;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= len; i++)
    {
        long long int prevMaxLen = 0;
        for (int j = 1; j <= len; j++)
        {
            if (fstArr[i] == sndArr[j])
            {
                dp[i][j] = prevMaxLen + 1;
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }

            if (sndArr[j] < fstArr[i])
            {
                prevMaxLen = max(prevMaxLen, dp[i - 1][j]);
            }

            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans << endl;
    return 0;
}