#include <bits/stdc++.h>
using namespace std;

#define VERTEX_SIZE 10010
#define EDGE_SIZE 200200

typedef struct _Edge
{
    int to;
    int cost;
    int next;
} Edge;

Edge arr[2][EDGE_SIZE];
int head[2][VERTEX_SIZE], arrPt[2];
int vertexNum, edgeNum;

int dfn[VERTEX_SIZE], low[VERTEX_SIZE], cntTime;
int edccId[VERTEX_SIZE], edccNum;

bool isBridge[EDGE_SIZE];
int bridgeNum;

int ans;

void addEdge(int id, int from, int to, int cost)
{
    arr[id][arrPt[id]] = {to, cost, head[id][from]};
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

int findMin(int cntPt, int parentPt)
{
    int minVal = INT_MAX, secMinVal = INT_MAX;
    for (int i = head[1][cntPt]; i != -1; i = arr[1][i].next)
    {
        int nextPt = arr[1][i].to;
        int cost = arr[1][i].cost;
        if (nextPt == parentPt)
            continue;

        int nextAns = findMin(nextPt, cntPt);
        if (nextAns < secMinVal)
            secMinVal = nextAns; 
        if (cost < secMinVal)
            secMinVal = cost;
        if (minVal > secMinVal)
            swap(secMinVal, minVal);
    }
    if (ans > secMinVal)
        ans = secMinVal;
    return minVal;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> vertexNum >> edgeNum)
    {
        memset(head, -1, sizeof(head));
        memset(dfn, -1, sizeof(dfn));
        memset(edccId, -1, sizeof(edccId));
        memset(isBridge, false, sizeof(isBridge));
        memset(arrPt, 0, sizeof(arrPt));
        cntTime = 0;
        edccNum = 0;
        bridgeNum = 0;

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, cost;
            cin >> from >> to >> cost;
            from--;
            to--;
            addEdge(0, from, to, cost);
            addEdge(0, to, from, cost);
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

        int minCost = INT_MAX, minFrom = -1, minTo = -1;
        for (int i = 0; i < arrPt[0]; i += 2)
        {
            int from = arr[0][i ^ 1].to;
            int to = arr[0][i].to;
            int cost = arr[0][i].cost;

            if (edccId[from] == edccId[to])
                continue;

            addEdge(1, edccId[from], edccId[to], cost);
            addEdge(1, edccId[to], edccId[from], cost);

            if (cost < minCost)
            {
                minCost = cost;
                minFrom = edccId[from];
                minTo = edccId[to];
            }
        }

        ans = INT_MAX;
        findMin(minFrom, minTo);
        findMin(minTo, minFrom);

        if (ans == INT_MAX)
            cout << -1 << endl;
        else
            cout << ans << endl;
    } 
    return 0;
}
