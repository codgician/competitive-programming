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

#define SIZE 1024

const long long int mod = 1e9 + 7;

int arr[SIZE];
int dp[2][11][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        int num, lim;
        cin >> num >> lim;
        lim = min(num, lim);

        int xorSum = 0;
        for (int i = 1; i <= num; i++)
        {
            cin >> arr[i];
            xorSum ^= arr[i];
        }

        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        for (int i = 1; i <= num; i++)
        {
            for (int j = 0; j <= min(i, lim); j++)
            {
                for (int k = 0; k < SIZE; k++)
                {
                    dp[i & 1][j][k] = dp[!(i & 1)][j][k];
                    if (j > 0) 
                    {
                        dp[i & 1][j][k] += dp[!(i & 1)][j - 1][k ^ arr[i]];
                        dp[i & 1][j][k] %= mod;
                    }
                }
            }
        }

        long long int ans = 0;
        for (int i = 0; i <= lim; i++)
        {
            ans += dp[num & 1][i][xorSum];
            ans %= mod;
        }
        cout << ans << endl;
    }
    return 0;
}