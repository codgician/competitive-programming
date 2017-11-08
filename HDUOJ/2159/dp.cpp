#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <climits>
#define SIZE 101
using namespace std;

typedef struct Node {
    int exp;
    int fav;
} monster;

monster arr[SIZE];
int dp[SIZE][SIZE];  //i: fav, j: killNum

int main()
{
    ios::sync_with_stdio(false);
    int exp, fav, monsterType, killNum;
    while (cin >> exp >> fav >> monsterType >> killNum)
    {
        for (int i = 0; i < monsterType; i++)
        {
            cin >> arr[i].exp >> arr[i].fav;
        }

        for (int i = 0; i <= fav; i++)
        {
            for (int j = 1; j <= killNum; j++)
            {
                dp[i][j] = 0;
            }
        }

        for (int t = 0; t < monsterType; t++)
        {
            for (int i = arr[t].fav; i <= fav; i++)
            {
                for (int j = 1; j <= killNum; j++)
                {
                    if (i - arr[t].fav >= 0)
                    {
                        dp[i][j] = max(dp[i][j], dp[i - arr[t].fav][j - 1] + arr[t].exp);
                    }
                }
            }
        }

        if (dp[fav][killNum] < exp)
        {
            cout << "-1" << endl;
        }
        else
        {
            int minCost = INT_MAX;
            for (int i = 0; i < minCost; i++)
            {
                for (int j = 0; j <= killNum; j++)
                {
                    if (dp[i][j] >= exp)
                        minCost = i;
                }
            }
            cout << fav - minCost << endl;
        }
    }
    return 0;
}
