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
bool hasVisited[VERTEX_SIZE];

void addEdge(int from, int to, int capacity)
{
    arr[arrPt] = {to, capacity, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, head[to]};
    head[to] = arrPt++;
}

int findAguPath(int cntPt, int endPt, int cntFlow)
{
    if (cntPt == endPt)
    {
        return cntFlow;
    }

    hasVisited[cntPt] = true;

    int edgePt = head[cntPt];
    while (edgePt != -1)
    {
        if (!hasVisited[arr[edgePt].to] && arr[edgePt].capacity > 0)
        {
            int flowInc = findAguPath(arr[edgePt].to, endPt, min(cntFlow, arr[edgePt].capacity));
            if (flowInc > 0)
            {
                arr[edgePt].capacity -= flowInc;
                arr[edgePt ^ 1].capacity += flowInc;
                return flowInc;
            }
        }
        edgePt = arr[edgePt].next;
    }

    return 0;
}

int fordFulkerson(int startPt, int endPt)
{
    int ans = 0;
    while (true)
    {
        memset(hasVisited, false, sizeof(hasVisited));
        int flowInc = findAguPath(startPt, endPt, INT_MAX);
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
        int ans = fordFulkerson(0, vertexNum - 1);
        cout << ans << endl;
    }
    return 0;
}
