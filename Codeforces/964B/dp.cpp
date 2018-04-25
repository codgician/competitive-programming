/*
    This is a monument of my foolishness.
    Goodbye, Codeforces.
*/

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

int arr[SIZE], num[SIZE], dp[SIZE][SIZE];
int tmp[SIZE], prefixSum[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int msgNum, initVal, decVal, factor, timeLimit;
    cin >> msgNum >> initVal >> decVal >> factor >> timeLimit;
    memset(tmp, 0, sizeof(tmp));
    for (int i = 1; i <= msgNum; i++)
    {
        int cnt;
        cin >> cnt;
        tmp[cnt]++;
    }
    
    int arrPt = 1;
    for (int i = 1; i <= timeLimit; i++)
    {
        if (tmp[i] > 0)
        {
            arr[arrPt] = i;
            num[arrPt] = tmp[i];
            arrPt++;
        }
    }
    arrPt--;

    prefixSum[0] = 0;
    for (int i = 1; i <= arrPt; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + num[i];
    }

    int cntNum = 0, pt = 1;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i < timeLimit; i++)
    {
        int delta = 0;
        while (arr[pt] <= i && pt <= arrPt)
        {
            cntNum += num[pt];
            delta++;
            pt++;
        }

        dp[i][0] = dp[i - 1][0] + cntNum * factor;

        if (delta == 0)
        {
            for (int j = 1; j <= arrPt && arr[j] <= i; j++)
            {
                dp[i][j] = dp[i - 1][j] + (cntNum - prefixSum[j]) * factor;
            }
        }
        else
        {
            for (int j = 1; j <= arrPt && arr[j] <= i; j++)
            {
                dp[i][j] = max(dp[i - 1][j - 1] + num[j] * (initVal - (i - arr[j]) * decVal) + (cntNum - prefixSum[j]) * factor, dp[i - 1][j] + (cntNum - prefixSum[j]) * factor);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= arrPt; i++)
    {
        int cntAdd = 0;
        for (int j = i + 1; j <= arrPt; j++)
        {
            cntAdd += num[j] * (initVal - (timeLimit - arr[j]) * decVal);
        }
        ans = max(ans, dp[timeLimit - 1][i] + cntAdd);
    }

    cout << ans << endl;
    return 0;
}
