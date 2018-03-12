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
#define VERTEX_SIZE 16
#define EDGE_SIZE 2010
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int rev;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
bool hasVisited[VERTEX_SIZE];

void addEdge(int from, int to, int capacity)
{
    arr[arrPt] = {to, capacity, arrPt + 1, head[from]};
    arr[arrPt + 1] = {from, 0, arrPt, head[to]};
    head[from] = arrPt;
    head[to] = arrPt + 1;
    arrPt += 2;
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
                arr[arr[edgePt].rev].capacity += flowInc;
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
    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        int vertexNum, edgeNum;
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, capacity;
            cin >> from >> to >> capacity;
            from--;
            to--;
            addEdge(from, to, capacity);
        }
        int ans = fordFulkerson(0, vertexNum - 1);
        cout << "Case " << t << ": " << ans << endl;
    }
    return 0;
}
