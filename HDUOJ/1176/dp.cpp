#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iomanip>
#define TIME_SIZE 100001
#define NODE_SIZE 11
using namespace std;

int arr[TIME_SIZE][NODE_SIZE], dp[TIME_SIZE][NODE_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int pieNum;
    while (cin >> pieNum)
    {
        if (pieNum == 0)
            break;
        memset(arr, 0, sizeof(arr));
        int maxTime = 0;
        for (int i = 0; i < pieNum; i++)
        {
            int nodeNum, pieTime;
            cin >> nodeNum >> pieTime;
            arr[pieTime][nodeNum]++;
            if (pieTime > maxTime)
                maxTime = pieTime;
        }

        for (int j = 0; j < NODE_SIZE; j++)
        {
            dp[maxTime][j] = arr[maxTime][j];
        }

        for (int i = maxTime - 1; i >= 0; i--)
        {
            for (int j = 0; j < NODE_SIZE; j++)
            {
                if (j == 0)
                    dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + arr[i][j];
                else if (j == 10)
                    dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - 1]) + arr[i][j];
                else
                    dp[i][j] = max(dp[i + 1][j], max(dp[i + 1][j - 1], dp[i + 1][j + 1])) + arr[i][j];
            }
        }
        cout << dp[0][5] << endl;
    }
    return 0;
}
