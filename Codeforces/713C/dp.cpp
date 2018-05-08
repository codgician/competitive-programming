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
    for (int i = 0; i < len; i++)
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

    long long int ans = LLONG_MAX;
    sort(valArr + 0, valArr + len);
    int valLen = unique(valArr, valArr + len) - valArr;

    for (int j = 0; j < valLen; j++)
    {
        dp[0][j] = abs(arr[0] - valArr[j]);
    }
    for (int i = 1; i < len; i++)
    {
        long long int prevMinVal = LLONG_MAX;
        for (int j = 0; j < valLen; j++)
        {
            prevMinVal = min(prevMinVal, dp[i - 1][j]);
            dp[i][j] = prevMinVal + abs(arr[i] - valArr[j]);

            if (i == len - 1)
            {
                ans = min(ans, dp[i][j]);
            }
        }
    }

    cout << ans << endl;
    return 0;
}