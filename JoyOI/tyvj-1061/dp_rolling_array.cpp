#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define SIZE 210
#define QSIZE 1010
using namespace std;
 
int costArr[SIZE][SIZE];
int qArr[QSIZE];
int dp[2][SIZE][SIZE];
 
int main()
{
    int len, qNum;
    scanf("%d%d", &len, &qNum);
    for (int i = 1; i <= len; i++)
    {
        for (int j = 1; j <= len; j++)
        {
            scanf("%d", costArr[i] + j);
        }
    }
 
    for (int i = 1; i <= qNum; i++)
    {
        scanf("%d", qArr + i);
    }
    qArr[0] = 3;
 
 
    for (int j = 1; j <= len; j++)
    {
        for (int k = 1; k <= len; k++)
        {
            dp[0][j][k] = INT_MAX;
        }
    }
    dp[0][1][2] = 0;
 
    for (int i = 0; i < qNum; i++)
    {
        for (int j = 1; j <= len; j++)
        {
            for (int k = 1; k <= len; k++)
            {
                dp[(i & 1) ^ 1][j][k] = INT_MAX;
            }
        }
 
        for (int j = 1; j <= len; j++)
        {
            for (int k = j + 1; k <= len; k++)
            {
                if (j == qArr[i] || k == qArr[i])
                    continue;
                if (dp[i & 1][j][k] == INT_MAX)
                    continue;
             
                dp[(i & 1) ^ 1][j][k] = min(dp[(i & 1) ^ 1][j][k], dp[i & 1][j][k] + costArr[qArr[i]][qArr[i + 1]]);

                if (qArr[i] < k)
                    dp[(i & 1) ^ 1][qArr[i]][k] = min(dp[(i & 1) ^ 1][qArr[i]][k], dp[i & 1][j][k] + costArr[j][qArr[i + 1]]);
                else
                    dp[(i & 1) ^ 1][k][qArr[i]] = min(dp[(i & 1) ^ 1][k][qArr[i]], dp[i & 1][j][k] + costArr[j][qArr[i + 1]]);

                if (j < qArr[i])
                    dp[(i & 1) ^ 1][j][qArr[i]] = min(dp[(i & 1) ^ 1][j][qArr[i]], dp[i & 1][j][k] + costArr[k][qArr[i + 1]]);
                else
                    dp[(i & 1) ^ 1][qArr[i]][j] = min(dp[(i & 1) ^ 1][qArr[i]][j], dp[i & 1][j][k] + costArr[k][qArr[i + 1]]);            }
        }
    }
 
    int ans = INT_MAX;
    for (int j = 1; j <= len; j++)
    {
        for (int k = j + 1; k <= len; k++)
        {
            ans = min(ans, dp[qNum & 1][j][k]);
        }
    }
 
    printf("%d\n", ans);
    return 0;
}