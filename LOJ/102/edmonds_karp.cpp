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
#define VERTEX_SIZE 401
#define EDGE_SIZE 31000
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int cost;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int dis[VERTEX_SIZE], minCapacity[VERTEX_SIZE], pre[VERTEX_SIZE];
bool inQueue[VERTEX_SIZE];
int vertexNum;

void addEdge(int from, int to, int capacity, int cost)
{
    arr[arrPt] = {to, capacity, cost, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, -cost, head[to]};
    head[to] = arrPt++;
}

void updateCapacity(int startPt, int endPt)
{
    int cntPt = endPt;
    while (cntPt != startPt)
    {
        int edgePt = pre[cntPt];
        arr[edgePt].capacity -= minCapacity[endPt];
        arr[edgePt ^ 1].capacity += minCapacity[endPt];
        cntPt = arr[edgePt ^ 1].to;
    }
}

bool findAguPath(int startPt, int endPt)
{
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    memset(inQueue, false, sizeof(inQueue));
    queue<int> q;

    q.push(startPt);
    dis[startPt] = 0;
    minCapacity[startPt] = INT_MAX;
    inQueue[startPt] = true;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();
        inQueue[cntPt] = false;

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            if (arr[edgePt].capacity > 0 && dis[cntPt] != INT_MAX && dis[arr[edgePt].to] > dis[cntPt] + arr[edgePt].cost)
            {
                dis[arr[edgePt].to] = dis[cntPt] + arr[edgePt].cost;
                minCapacity[arr[edgePt].to] = min(minCapacity[cntPt], arr[edgePt].capacity);
                pre[arr[edgePt].to] = edgePt;

                if (!inQueue[arr[edgePt].to])
                {
                    q.push(arr[edgePt].to);
                    inQueue[arr[edgePt].to] = true;
                }
            }
            edgePt = arr[edgePt].next;
        }
    }

    if (dis[endPt] == INT_MAX)
        return false;
    return true;
}

void edmondsKarp(int startPt, int endPt, int &flow, int &cost)
{
    while (findAguPath(startPt, endPt))
    {
        updateCapacity(startPt, endPt);
        flow += minCapacity[endPt];
        cost += dis[endPt] * minCapacity[endPt];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    arrPt = 0;
    memset(head, -1, sizeof(head));
    int edgeNum;
    cin >> vertexNum >> edgeNum;
    for (int i = 0; i < edgeNum; i++)
    {
        int from, to, length, cost;
        cin >> from >> to >> length >> cost;
        from--;
        to--;
        addEdge(from, to, length, cost);
    }

    int flow = 0, cost = 0;
    edmondsKarp(0, vertexNum - 1, flow, cost);
    cout << flow << " " << cost << endl;
    return 0;
}
