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
#define SIZE 2010
using namespace std;

int arr[SIZE];
int valArr[SIZE];
int dp[SIZE][SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int len;
    {
        for (int i = 0; i < len; i++)
        {
            cin >> arr[i];
            valArr[i] = arr[i];
        }

        int ans = INT_MAX;
        sort(valArr + 0, valArr + len);
        int valLen = unique(valArr, valArr + len) - valArr;

        if (len == 1)
        {
            cout << 0 << endl;
            continue;
        }

        for (int j = 0; j < valLen; j++)
        {
            dp[0][j] = abs(arr[0] - valArr[j]);
        }
        for (int i = 1; i < len; i++)
        {
            int prevMinVal = INT_MAX;
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

        reverse(valArr + 0, valArr + valLen);
        for (int j = 0; j < valLen; j++)
        {
            dp[0][j] = abs(arr[0] - valArr[j]);
        }
        for (int i = 1; i < len; i++)
        {
            int prevMinVal = INT_MAX;
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
    }
    return 0;
}