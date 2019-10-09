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

#define SIZE 110

typedef struct _Edge
{
    int to, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;

int bugArr[SIZE], posArr[SIZE];
int dp[SIZE][SIZE];
int vertexNum, itemNum;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt)
{
    int cntNum = bugArr[cntPt] / 20 + (bugArr[cntPt] % 20 != 0);
    for (int i = cntNum; i <= itemNum; i++)
        dp[cntPt][i] = posArr[cntPt];

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt);

        for (int j = itemNum; j >= cntNum; j--)
        {
            for (int k = 1; j + k <= itemNum; k++)
            {
                if (dp[nextPt][k] != 0)
                    dp[cntPt][j + k] = max(dp[cntPt][j + k], dp[cntPt][j] + dp[nextPt][k]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> vertexNum >> itemNum)
    {
        if (vertexNum == -1 && itemNum == -1)
            break;

        memset(head, -1, sizeof(head));
        memset(dp, 0, sizeof(dp));
        arrPt = 0;

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> bugArr[i] >> posArr[i];
        }
        for (int i = 1; i < vertexNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to);
            addEdge(to, from);
        }

        if (itemNum == 0)
        {
            cout << 0 << endl;
            continue;
        }

        dfs(0, -1);
        cout << dp[0][itemNum] << endl;
    }

    return 0;
}