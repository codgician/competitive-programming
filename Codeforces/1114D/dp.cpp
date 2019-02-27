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

#define SIZE 5010

int arr[SIZE];
int dp[SIZE][SIZE][2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int len;
    cin >> len;

    int preColor;
    cin >> preColor;
    preColor--;
    int arrPt = 0;
    for (int i = 1; i < len; i++)
    {
        int cntColor;
        cin >> cntColor;
        cntColor--;
        if (cntColor != preColor)
        {
            arr[arrPt++] = preColor;
            preColor = cntColor;
        }
    }
    arr[arrPt++] = preColor;

    for (int i = 0; i < arrPt; i++)
    {
        dp[i][i][0] = 0;
        dp[i][i][1] = 0;
        for (int j = i + 1; j < arrPt; j++)
        {
            dp[i][j][0] = INT_MAX, dp[i][j][1] = INT_MAX;
            dp[j][i][0] = INT_MAX, dp[j][i][1] = INT_MAX;
        }
    }

    for (int k = 2; k <= arrPt; k++)
    {
        for (int l = 0; l < arrPt; l++)
        {
            int r = l + k - 1;
            if (r > arrPt)
                break;
            // Extend left
            dp[l][r][0] = min(dp[l + 1][r][0] + (arr[l + 1] != arr[l]), dp[l + 1][r][1] + (arr[r] != arr[l]));
            // Extend right
            dp[l][r][1] = min(dp[l][r - 1][0] + (arr[l] != arr[r]), dp[l][r - 1][1] + (arr[r - 1] != arr[r]));
        }
    }

    cout << min(dp[0][arrPt - 1][0], dp[0][arrPt - 1][1]) << endl;
    return 0;
}