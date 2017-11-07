#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <iomanip>
#define SIZE 10001
#define INF 999
using namespace std;

bool arr[SIZE];
int dp[SIZE], stone[SIZE];

int main()
{
    ios::sync_with_stdio(false);
    int bridgeLength;
    bool isFirst = true;
    while (cin >> bridgeLength)
    {
        if (!isFirst)
            cout << endl;
        else
            isFirst = false;

        int minHop, maxHop, stoneNum;
        cin >> minHop >> maxHop >> stoneNum;

        stone[0] = 0;
        for (int i = 1; i <= stoneNum; i++)
            cin >> stone[i];

        if (minHop == maxHop)
        {
            int ans = 0;
            for (int i = 1; i <= stoneNum; i++)
                if (stone[i] % maxHop == 0)
                    ans++;
            cout << ans;
        }
        else
        {
            // Route compression
            sort(stone, stone + stoneNum + 1);

            int k = maxHop * (maxHop - 1);
            for (int i = 1, j = 0; i <= stoneNum; i++)
            {
                stone[i] -= j;
                int delta = stone[i] - stone[i - 1];
                if (delta > k)
                {
                    j += delta - k;
                    stone[i] = stone[i - 1] + k;
                }
            }

            for (int i = 0; i <= stone[stoneNum] + 1; i++)
            {
                arr[i] = false;
                dp[i] = INF;
            }

            for (int i = 0; i <= stoneNum; i++)
                arr[stone[i]] = true;

            dp[0] = 0;
            for (int i = 1; i <= stone[stoneNum] + 1; i++)
            {
                for (int j = minHop; j <= maxHop && j <= i; j++)
                {
                    dp[i] = min(dp[i], dp[i - j] + arr[i]);
                }
            }

            cout << dp[stone[stoneNum] + 1];
        }
    }
    return 0;
}
