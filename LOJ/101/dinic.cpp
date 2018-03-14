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
#define VERTEX_SIZE 101
#define EDGE_SIZE 10010
using namespace std;

typedef struct _Edge
{
    int to;
    long long int capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int vertexNum, edgeNum;

void addEdge(int from, int to, long long int capacity)
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

    depth[startPt] = 0;
    q.push(startPt);

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

long long int findAguPath(int cntPt, int endPt, long long int minCapacity)
{
    if (cntPt == endPt)
        return minCapacity;

    long long int cntFlow = 0;
    int &edgePt = lastVisitedEdge[cntPt];
    while (edgePt != -1)
    {
        if (depth[arr[edgePt].to] == depth[cntPt] + 1 && arr[edgePt].capacity > 0)
        {
            long long int flowInc = findAguPath(arr[edgePt].to, endPt, min(minCapacity - cntFlow, arr[edgePt].capacity));
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

long long int dinic(int startPt, int endPt)
{
    long long int ans = 0;
    while (updateDepth(startPt, endPt))
    {
        for (int i = 0; i < vertexNum; i++)
        {
            lastVisitedEdge[i] = head[i];
        }
        long long int flowInc = findAguPath(startPt, endPt, LLONG_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    arrPt = 0;
    memset(head, -1, sizeof(head));
    int startPt, endPt;
    cin >> vertexNum >> edgeNum >> startPt >> endPt;
    startPt--;
    endPt--;
    for (int i = 0; i < edgeNum; i++)
    {
        int from, to;
        long long int capacity;
        cin >> from >> to >> capacity;
        from--;
        to--;
        addEdge(from, to, capacity);
    }

    long long int ans = dinic(startPt, endPt);
    cout << ans << endl;
    return 0;
}
