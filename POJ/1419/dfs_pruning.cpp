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
#define SIZE 101
using namespace std;

bool arr[SIZE][SIZE];
int path[SIZE], dp[SIZE], ans[SIZE];
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
    if (cntNum == maxNum)
    {
        for (int i = 0; i < cntNum; i++)
        {
            ans[i] = path[i];
        }
    }

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
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(arr, true, sizeof(arr));
        maxNum = 1;
        int edgeNum;
        cin >> nodeNum >> edgeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            arr[from][to] = false;
            arr[to][from] = false;
        }

        dp[nodeNum - 1] = 1;
        for (int i = nodeNum - 2; i >= 0; i--)
        {
            path[0] = i;
            dfs(i, 1);
            dp[i] = maxNum;
        }
        cout << maxNum << endl;
        for (int i = 0; i < maxNum; i++)
        {
            cout << ans[i] + 1;
            if (i < maxNum - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}
