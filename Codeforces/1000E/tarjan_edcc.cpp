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
using namespace std;

#define VERTEX_SIZE 600200
#define EDGE_SIZE 1200400

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[2][EDGE_SIZE];
int head[2][VERTEX_SIZE], arrPt[2];

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;

int edccId[VERTEX_SIZE], edccNum;

bool isBridge[EDGE_SIZE];
int bridgeNum;

bool hasVisited[VERTEX_SIZE];
int dp[VERTEX_SIZE];

int vertexNum, edgeNum;
int ans;

void addEdge(int id, int from, int to)
{
    arr[id][arrPt[id]] = {to, head[id][from]};
    head[id][from] = arrPt[id]++;
}

void tarjan(int cntPt, int edgeId)
{
    dfn[cntPt] = cntTime;
    low[cntPt] = cntTime;
    cntTime++;

    for (int i = head[0][cntPt]; i != -1; i = arr[0][i].next)
    {
        int nextPt = arr[0][i].to;
        if (dfn[nextPt] == -1)
        {
            tarjan(nextPt, i);
            low[cntPt] = min(low[cntPt], low[nextPt]);

            if (low[nextPt] > dfn[cntPt])
            {
                bridgeNum++;
                isBridge[i] = true;
                isBridge[i ^ 1] = true;
            }
        }
        else if (i != (edgeId ^ 1))
        {
            low[cntPt] = min(low[cntPt], dfn[nextPt]);
        }
    }
}

void dfs(int cntPt)
{
    edccId[cntPt] = edccNum;
    for (int i = head[0][cntPt]; i != -1; i = arr[0][i].next)
    {
        int nextPt = arr[0][i].to;
        if (edccId[nextPt] > -1 || isBridge[i])
            continue;
        dfs(nextPt);
    }
}

void dfs2(int cntPt)
{
    hasVisited[cntPt] = true;
    for (int i = head[1][cntPt]; i != -1; i = arr[1][i].next)
    {
        int nextPt = arr[1][i].to;
        if (hasVisited[nextPt])
            continue;
        dfs2(nextPt);
        ans = max(ans, dp[cntPt] + dp[nextPt] + 1);
        dp[cntPt] = max(dp[cntPt], dp[nextPt] + 1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    memset(dfn, -1, sizeof(dfn));
    memset(edccId, -1, sizeof(edccId));
    memset(isBridge, false, sizeof(isBridge));
    memset(hasVisited, false, sizeof(hasVisited));
    memset(arrPt, 0, sizeof(arrPt));
    cntTime = 0;
    edccNum = 0;
    bridgeNum = 0;

    cin >> vertexNum >> edgeNum;
    for (int i = 0; i < edgeNum; i++)
    {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        addEdge(0, from, to);
        addEdge(0, to, from);
    }

    for (int i = 0; i < vertexNum; i++)
    {
        if (dfn[i] == -1)
        {
            tarjan(i, 0);
        }
    }

    for (int i = 0; i < vertexNum; i++)
    {
        if (edccId[i] == -1)
        {
            dfs(i);
            edccNum++;
        }
    }

    for (int i = 0; i < arrPt[0]; i += 2)
    {
        int from = arr[0][i ^ 1].to;
        int to = arr[0][i].to;

        if (edccId[from] == edccId[to])
            continue;

        addEdge(1, edccId[from], edccId[to]);
        addEdge(1, edccId[to], edccId[from]);
    }

    ans = 0;
    memset(dp, 0, sizeof(dp));
    dfs2(0);
    cout << ans << endl;

    return 0;
}