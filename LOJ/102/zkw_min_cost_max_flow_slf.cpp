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
#include <deque>
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
int dis[VERTEX_SIZE];
bool inQueue[VERTEX_SIZE], hasVisited[VERTEX_SIZE];
int vertexNum;

void addEdge(int from, int to, int capacity, int cost)
{
    arr[arrPt] = {to, capacity, cost, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, -cost, head[to]};
    head[to] = arrPt++;
}

bool isFullFlow(int startPt, int endPt)
{
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    memset(inQueue, false, sizeof(inQueue));
    dis[startPt] = 0;
    deque<int> dq;
    dq.push_back(startPt);
    inQueue[startPt] = true;

    while (!dq.empty())
    {
        int cntPt = dq.front();
        dq.pop_front();
        inQueue[cntPt] = false;

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            if (arr[i ^ 1].capacity != 0 && dis[nextPt] > dis[cntPt] - arr[i].cost)
            {
                dis[nextPt] = dis[cntPt] - arr[i].cost;
                if (!inQueue[nextPt])
                {
                    inQueue[nextPt] = true; 
                    if (!dq.empty() && dis[nextPt] < dis[dq.front()])
                        dq.push_front(nextPt);
                    else
                        dq.push_back(nextPt);
                }
            }
        }
    }
    return dis[endPt] != INT_MAX;
}

int findAguPath(int cntPt, int endPt, int minCap, int & cost)
{
    if (cntPt == endPt)
    {
        hasVisited[endPt] = true;
        return minCap;
    }

    int cntFlow = 0;
    hasVisited[cntPt] = true;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (hasVisited[nextPt])
            continue;

        if (dis[cntPt] - arr[i].cost == dis[nextPt] && arr[i].capacity > 0)
        {
            // Can be augmented
            int flowInc = findAguPath(nextPt, endPt, min(minCap - cntFlow, arr[i].capacity), cost);
            if (flowInc != 0)
            {
                cost += flowInc * arr[i].cost;
                arr[i].capacity -= flowInc;
                arr[i ^ 1].capacity += flowInc;
                cntFlow += flowInc;
            }

            if (cntFlow == minCap)
                break;
        }
    }

    return cntFlow;
}

void zkw(int startPt, int endPt, int & flow, int & cost)
{
    flow = 0;
    cost = 0;
    while (isFullFlow(endPt, startPt))
    {
        hasVisited[endPt] = true;
        while (hasVisited[endPt])
        {
            memset(hasVisited, false, sizeof(hasVisited));
            flow += findAguPath(startPt, endPt, INT_MAX, cost);
        }
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
    zkw(0, vertexNum - 1, flow, cost);
    cout << flow << " " << cost << endl;
    return 0;
}