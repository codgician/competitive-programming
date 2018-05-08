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

long long int arr[SIZE], valArr[SIZE];
long long int dp[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int len;
    cin >> len;
    for (int i = 1; i <= len; i++)
    {
        cin >> arr[i];
        arr[i] -= i;
        valArr[i] = arr[i];
    }

    if (len == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    sort(valArr + 1, valArr + len + 1);
    int valLen = unique(valArr + 1, valArr + len + 1) - valArr - 1;

    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= len; i++)
    {
        dp[i][1] = dp[i - 1][1] + abs(arr[i] - valArr[1]);
        for (int j = 2; j <= valLen; j++)
        {
            dp[i][j] = min(dp[i - 1][j] + abs(arr[i] - valArr[j]), dp[i][j - 1]);
        }
    }

    cout << dp[len][valLen] << endl;
    return 0;
}