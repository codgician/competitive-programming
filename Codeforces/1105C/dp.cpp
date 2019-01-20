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

#define SIZE 200010

const int mod = 1e9 + 7;

long long int dp[SIZE][3], arr[3];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len, leftPt, rightPt;
    cin >> len >> leftPt >> rightPt;

    int range = rightPt - leftPt + 1;
    for (int i = 0; i < 3; i++)
        arr[i] = range / 3;
    if (range % 3 >= 1)
        arr[leftPt % 3]++;
    if (range % 3 >= 2)
        arr[(leftPt + 1) % 3]++;

    for (int i = 0; i < 3; i++)
        dp[1][i] = arr[i];
    for (int i = 1; i < len; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                dp[i + 1][(j + k) % 3] += dp[i][j] * arr[k] % mod;
                dp[i + 1][(j + k) % 3] %= mod;
            } 
        }
    }
    cout << dp[len][0] << endl;
    return 0;
}