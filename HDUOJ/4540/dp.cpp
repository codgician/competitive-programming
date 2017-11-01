#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iomanip>
#define TIME_SIZE 22
#define MOUSE_SIZE 11
#define INF 99999
using namespace std;

int arr[TIME_SIZE][MOUSE_SIZE], dp[TIME_SIZE][MOUSE_SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int maxTime, mouseNum;
    while (cin >> maxTime >> mouseNum)
    {
        // Hitting the first mouse does not cost energy.
        for (int i = 0; i < maxTime; i++)
            for (int j = 0; j < mouseNum; j++)
                cin >> arr[i][j];

        for (int j = 0; j < mouseNum; j++)
            dp[0][j] = 0;
        for (int i = 1; i < maxTime; i++)
            for (int j = 0; j < mouseNum; j++)
                dp[i][j] = INF;

        for (int i = 1; i < maxTime; i++)
        {
            for (int j = 0; j < mouseNum; j++)
            {
                for (int k = 0; k < mouseNum; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + abs(arr[i - 1][k] - arr[i][j]));
                }
            }
        }

        int ans = INF;
        for (int j = 0; j < mouseNum; j++)
        {
            if (dp[maxTime - 1][j] < ans)
                ans = dp[maxTime - 1][j];
        }
        cout << ans << endl;
    }
    return 0;
}
