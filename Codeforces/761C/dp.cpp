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
#define SIZE 51
using namespace std;

int dp[SIZE][8];
int cost[SIZE][3];

int main()
{
    ios::sync_with_stdio(false);
    int num, len;
    cin >> num >> len;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < 3; j++)
            cost[i][j] = INT_MAX;

        for (int j = 0; j < len; j++)
        {
            char ch;
            cin >> ch;

            int typeId;
            if (ch >= '0' && ch <= '9')
                typeId = 0;
            else if (ch >= 'a' && ch <= 'z')
                typeId = 1;
            else
                typeId = 2;

            cost[i][typeId] = min(cost[i][typeId], min(j, abs(len - j)));
        }
    }

    for (int j = 0; j < 8; j++)
    {
        dp[0][j] = INT_MAX;
    }
    for (int j = 0; j < 3; j++)
    {
        dp[0][1 << j] = cost[0][j];
    }

    for (int i = 1; i < num; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            dp[i][j] = dp[i - 1][j];

            for (int k = 0; k < 3; k++)
            {
                if (((j >> k) & 1) && dp[i - 1][j - (1 << k)] != INT_MAX && cost[i][k] != INT_MAX)
                {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - (1 << k)] + cost[i][k]);
                }
            }
        }
    }

    cout << dp[num - 1][7] << endl;
    return 0;
}