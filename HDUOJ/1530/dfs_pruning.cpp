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
#include <set>
#include <map>
#define SIZE 99
using namespace std;

bool arr[SIZE][SIZE];
int path[SIZE], dp[SIZE]; // dp[i]: number of nodes in maximum clique of G{i ~ N}
int nodeNum, maxNum, cntStartPt;

bool canAdd(int cntPt, int cntNum)
{
    for (int i = 0; i < cntNum; i++)
    {
        if (!arr[cntPt][path[i]])
        {
            return false;
        }
    }
    return true;
}

void dfs(int cntPt, int cntNum)
{
    maxNum = max(maxNum, cntNum);

    if (cntNum + nodeNum - cntPt - 1 <= maxNum)
        return;

    for (int i = cntPt + 1; i < nodeNum; i++)
    {
        if (dp[i] + cntNum <= maxNum)
            return;

        if (canAdd(i, cntNum))
        {
            path[cntNum] = i;
            dfs(i, cntNum + 1);
        }
    }

    return;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> nodeNum)
    {
        if (nodeNum == 0)
            break;

        maxNum = 1;
        for (int i = 0; i < nodeNum; i++)
        {
            for (int j = 0; j < nodeNum; j++)
            {
                cin >> arr[i][j];
            }
        }

        dp[nodeNum - 1] = 1;
        for (int i = nodeNum - 2; i >= 0; i--)
        {
            path[0] = i;
            dfs(i, 1);
            dp[i] = maxNum;
        }
        cout << maxNum << endl;
    }
    return 0;
}
