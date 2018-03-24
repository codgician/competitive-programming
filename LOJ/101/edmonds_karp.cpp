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
    int capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int pre[VERTEX_SIZE], minCapacity[VERTEX_SIZE];
bool hasVisited[VERTEX_SIZE];
int vertexNum;

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

int findAguPath(int startPt, int endPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<int> q;
    q.push(startPt);
    minCapacity[startPt] = INT_MAX;
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
                minCapacity[arr[edgePt].to] = min(minCapacity[cntPt], arr[edgePt].capacity);
                hasVisited[arr[edgePt].to] = true;
                pre[arr[edgePt].to] = edgePt;

                if (arr[edgePt].to == endPt)
                {
                    updateCapacity(startPt, endPt, minCapacity[endPt]);
                    return minCapacity[endPt];
                }

                q.push(arr[edgePt].to);
            }
            edgePt = arr[edgePt].next;
        }
    }
    return 0;
}

long long int edmondsKarp(int startPt, int endPt)
{
    long long int ans = 0;
    while (true)
    {
        int flowInc = findAguPath(startPt, endPt);
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
    int edgeNum, startPt, endPt;
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

    long long int ans = edmondsKarp(startPt, endPt);
    cout << ans << endl;
    return 0;
}
