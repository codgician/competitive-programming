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
#define VERTEX_SIZE 110
#define EDGE_SIZE 2010
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int bridgeArr[VERTEX_SIZE], bridgeCost[VERTEX_SIZE], bridgePt;
int vertexNum;

void addEdge(int from, int to, int capacity)
{
    arr[arrPt] = {to, capacity, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, head[to]};
    head[to] = arrPt++;
}

bool updateDepth(int startPt, int endPt)
{
    memset(depth, -1, sizeof(depth));
    queue<int> q;

    q.push(startPt);
    depth[startPt] = 0;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            if (depth[arr[edgePt].to] == -1 && arr[edgePt].capacity > 0)
            {
                depth[arr[edgePt].to] = depth[cntPt] + 1;
                if (arr[edgePt].to == endPt)
                    return true;
                q.push(arr[edgePt].to);
            }
            edgePt = arr[edgePt].next;
        }
    }

    return false;
}

int findAguPath(int cntPt, int endPt, int minCapacity)
{
    if (cntPt == endPt)
        return minCapacity;

    int cntFlow = 0;
    int &edgePt = lastVisitedEdge[cntPt];
    while (edgePt != -1)
    {
        if (depth[arr[edgePt].to] == depth[cntPt] + 1 && arr[edgePt].capacity > 0)
        {
            int flowInc = findAguPath(arr[edgePt].to, endPt, min(minCapacity - cntFlow, arr[edgePt].capacity));
            if (flowInc == 0)
            {
                depth[arr[edgePt].to] = -1;
            }
            else
            {
                arr[edgePt].capacity -= flowInc;
                arr[edgePt ^ 1].capacity += flowInc;
                cntFlow += flowInc;
                if (cntFlow == minCapacity)
                    break;
            }
        }
        edgePt = arr[edgePt].next;
    }

    return cntFlow;
}

int dinic(int startPt, int endPt)
{
    int ans = 0;
    while (updateDepth(startPt, endPt))
    {
        for (int i = 0; i < vertexNum; i++)
            lastVisitedEdge[i] = head[i];
        int flowInc = findAguPath(startPt, endPt, INT_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

void restoreGraph()
{
    for (int i = 0; i < arrPt; i += 2)
    {
        arr[i].capacity += arr[i ^ 1].capacity;
        arr[i ^ 1].capacity = 0;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int cityNum, roadNum;
    while (cin >> cityNum >> roadNum)
    {
        arrPt = 0;
        bridgePt = 0;
        memset(head, -1, sizeof(head));

        int startPt = 0, endPt = cityNum + 1;
        vertexNum = endPt + 1;
        for (int i = 1; i <= cityNum; i++)
        {
            int personNum;
            cin >> personNum;
            if (personNum > 0)
                addEdge(startPt, i, personNum);
        }

        int cost = 0;
        for (int i = 0; i < roadNum; i++)
        {
            int from, to, capacity, type;
            cin >> from >> to >> capacity >> type;
            if (type < 0)
            {
                addEdge(from, to, INT_MAX);
                addEdge(from, endPt, capacity);
            }
            else if (type == 0)
            {
                addEdge(from, to, INT_MAX);
            }
            else
            {
                bridgeArr[bridgePt] = arrPt;
                bridgeCost[bridgePt] = capacity;
                cost += capacity;
                bridgePt++;
                addEdge(from, to, INT_MAX);
            }
        }

        int ans = dinic(startPt, endPt);

        if (ans == 0)
        {
            cout << "Poor Heaven Empire" << endl;
        }
        else
        {
            cout << ans << " ";

            for (int i = 0; i < (1 << bridgePt) - 1; i++)
            {
                restoreGraph();
                int cntCost = 0;
                for (int j = 0; j < bridgePt; j++)
                {
                    if (i & (1 << j))
                    {
                        arr[bridgeArr[j]].capacity = INT_MAX;
                        arr[bridgeArr[j] ^ 1].capacity = 0;
                        cntCost += bridgeCost[j];
                    }
                    else
                    {
                        arr[bridgeArr[j]].capacity = 1;
                        arr[bridgeArr[j] ^ 1].capacity = 0;
                    }
                }

                int cntAns = dinic(startPt, endPt);
                if (cntAns == ans)
                {
                    cost = min(cost, cntCost);
                }
            }

            cout << cost << endl;
        }
    }
    return 0;
}
