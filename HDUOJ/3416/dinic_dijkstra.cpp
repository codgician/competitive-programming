#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define VERTEX_SIZE 1010
#define EDGE_SIZE 210000
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int length;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int dis[VERTEX_SIZE];
bool isShortest[VERTEX_SIZE];
int vertexNum;

void addEdge(int from, int to, int capacity, int length)
{
    arr[arrPt] = {to, capacity, length, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, 0, head[to]};
    head[to] = arrPt++;
}

void dijkstra(int startPt)
{
    memset(isShortest, false, sizeof(isShortest));
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    priority_queue<pair<int, int> > pq;

    dis[startPt] = 0;
    pq.push(make_pair(0, startPt));

    while (!pq.empty())
    {
        int cntPt = pq.top().second;
        pq.pop();
        if (isShortest[cntPt])
            continue;
        isShortest[cntPt] = true;

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            if (!(edgePt & 1) && dis[cntPt] != INT_MAX && dis[arr[edgePt].to] > dis[cntPt] + arr[edgePt].length)
            {
                dis[arr[edgePt].to] = dis[cntPt] + arr[edgePt].length;
                pq.push(make_pair(-dis[arr[edgePt].to], arr[edgePt].to));
            }

            edgePt = arr[edgePt].next;
        }
    }
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

int findAugPath(int cntPt, int endPt, int minCapacity)
{
    if (cntPt == endPt)
        return minCapacity;

    int cntFlow = 0;
    int &edgePt = lastVisitedEdge[cntPt];
    while (edgePt != -1)
    {
        if (depth[arr[edgePt].to] == depth[cntPt] + 1 && arr[edgePt].capacity > 0)
        {
            int flowInc = findAugPath(arr[edgePt].to, endPt, min(minCapacity - cntFlow, arr[edgePt].capacity));
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
        int flowInc = findAugPath(startPt, endPt, INT_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

void removeBadEdge()
{
    for (int i = 0; i < vertexNum; i++)
    {
        int edgePt = head[i];
        while (edgePt != -1)
        {
            if (!(edgePt & 1) && dis[i] + arr[edgePt].length > dis[arr[edgePt].to])
            {
                arr[edgePt].capacity = 0;
                arr[edgePt ^ 1].capacity = 0;
            }
            edgePt = arr[edgePt].next;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        int cityNum, roadNum;
        cin >> cityNum >> roadNum;
        int startPt = 0, endPt = cityNum + 1;
        vertexNum = endPt + 1;

        for (int i = 0; i < roadNum; i++)
        {
            int from, to, length;
            cin >> from >> to >> length;
            addEdge(from, to, 1, length);
        }

        int aPt, bPt;
        cin >> aPt >> bPt;
        addEdge(startPt, aPt, INT_MAX, 0);
        addEdge(bPt, endPt, INT_MAX, 0);

        dijkstra(startPt);
        removeBadEdge();
        int ans = dinic(startPt, endPt);
        cout << ans << endl;
    }
    return 0;
}
