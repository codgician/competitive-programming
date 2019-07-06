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

#define PROD_SIZE 210
#define VERTEX_SIZE 510
#define EDGE_SIZE 260100

typedef struct _Node
{
    int startPt, endPt;
    int val;
} Node;

Node nodeArr[PROD_SIZE];

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

int dscArr[VERTEX_SIZE], dscPt;

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
    queue<int> q;
    q.push(startPt);
    inQueue[startPt] = true;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();
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
                    q.push(nextPt);
                }
            }
        }
    }
    return dis[endPt] != INT_MAX;
}

int findAugPath(int cntPt, int endPt, int minCap, int & cost)
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
            int flowInc = findAugPath(nextPt, endPt, min(minCap - cntFlow, arr[i].capacity), cost);
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
            flow += findAugPath(startPt, endPt, INT_MAX, cost);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        dscPt = 0;
        int len, lim, prodNum;
        cin >> len >> lim >> prodNum;

        for (int i = 0; i < prodNum; i++)
        {
            cin >> nodeArr[i].startPt >> nodeArr[i].endPt >> nodeArr[i].val;
            nodeArr[i].endPt++;
            dscArr[dscPt++] = nodeArr[i].startPt;
            dscArr[dscPt++] = nodeArr[i].endPt;
        }

        sort(dscArr + 0, dscArr + dscPt);
        dscPt = unique(dscArr + 0, dscArr + dscPt) - dscArr;

        int startPt = dscPt, endPt = dscPt + 1;
        vertexNum = endPt + 1;
        addEdge(startPt, 0, lim, 0);
        addEdge(dscPt - 1, endPt, lim, 0);
        for (int i = 0; i < dscPt - 1; i++)
        {
            addEdge(i, i + 1, INT_MAX, 0);
        }

        for (int i = 0; i < prodNum; i++)
        {
            int from = lower_bound(dscArr + 0, dscArr + dscPt, nodeArr[i].startPt) - dscArr;
            int to = lower_bound(dscArr + 0, dscArr + dscPt, nodeArr[i].endPt) - dscArr;
            addEdge(from, to, 1, -nodeArr[i].val);
        }

        int flow = 0, cost = 0;
        zkw(startPt, endPt, flow, cost);
        cout << -cost << endl;
    }

    return 0;
}