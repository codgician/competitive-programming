#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#define SIZE 5001
using namespace std;

int dp[SIZE][SIZE];  // i: line i, j: indentation of line i, dp[i][j]: types
const long long int mod = 1000000007;

int main()
{
    ios::sync_with_stdio(false);
    dp[0][0] = 1;
    int stNum, maxIndentation = 0;
    cin >> stNum;
    char prevSt = 's';
    for (int i = 1; i <= stNum; i++)
    {
        if (prevSt == 'f')
        {
            // current line indentation <- previous line indentation + 1
            for (int j = 0; j <= maxIndentation; j++)
            {
                dp[i][j + 1] = dp[i - 1][j];
                dp[i][j + 1] %= mod;
            }
            maxIndentation++;
        }
        else
        {
            // current line indentation <- 0 ~ previous line indentation
            // in other words, current line indentation < previous line indentation
            // therefore, indention i of current line originates from indentation i, i + 1, ..., maxIndentationNum of previous line
            // maintain a suffix sum to prevent O(n^3)
            int suffixSum = 0;
            for (int j = maxIndentation; j >= 0; j--)
            {
                suffixSum += dp[i - 1][j];
                suffixSum %= mod;
                dp[i][j] = suffixSum;
                dp[i][j] %= mod;
            }
        }
        cin >> prevSt;
    }

    int ans = 0;
    for (int i = 0; i <= maxIndentation; i++)
    {
        ans += dp[stNum][i];
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}
