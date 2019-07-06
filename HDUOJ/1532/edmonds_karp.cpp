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
#define VERTEX_SIZE 201
#define EDGE_SIZE 401
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int pre[VERTEX_SIZE], cntFlow[VERTEX_SIZE];
bool hasVisited[VERTEX_SIZE];

void addEdge(int from, int to, int capacity)
{
    arr[arrPt] = {to, capacity, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, head[to]};
    head[to] = arrPt++;
}

void updateCapacity(int startPt, int endPt, int flowInc)
{
    int cntPt = endPt;
    while (cntPt != startPt)
    {
        int edgePt = pre[cntPt];
        arr[edgePt].capacity -= flowInc;
        arr[edgePt ^ 1].capacity += flowInc;
        cntPt = arr[edgePt ^ 1].to;
    }
}

int findAugPath(int startPt, int endPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<int> q;
    q.push(startPt);
    cntFlow[startPt] = INT_MAX;
    hasVisited[startPt] = true;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            if (!hasVisited[arr[edgePt].to] && arr[edgePt].capacity > 0)
            {
                cntFlow[arr[edgePt].to] = min(cntFlow[cntPt], arr[edgePt].capacity);
                hasVisited[arr[edgePt].to] = true;
                pre[arr[edgePt].to] = edgePt;

                if (arr[edgePt].to == endPt)
                {
                    updateCapacity(startPt, endPt, cntFlow[endPt]);
                    return cntFlow[endPt];
                }

                q.push(arr[edgePt].to);
            }
            edgePt = arr[edgePt].next;
        }
    }
    return 0;
}

int edmondsKarp(int startPt, int endPt)
{
    int ans = 0;
    while (true)
    {
        int flowInc = findAugPath(startPt, endPt);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int edgeNum, vertexNum;
    while (cin >> edgeNum >> vertexNum)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, capacity;
            cin >> from >> to >> capacity;
            from--;
            to--;
            addEdge(from, to, capacity);
        }
        int ans = edmondsKarp(0, vertexNum - 1);
        cout << ans << endl;
    }
    return 0;
}
