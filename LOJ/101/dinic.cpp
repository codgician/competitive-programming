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
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <iterator>
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

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            if (depth[nextPt] == -1 && arr[i].capacity > 0)
            {
                depth[nextPt] = depth[cntPt] + 1;
                if (nextPt == endPt)
                    return true;
                q.push(nextPt);
            }
        }
    }

    return false;
}

long long int findAguPath(int cntPt, int endPt, long long int minCap)
{
    if (cntPt == endPt)
        return minCap;

    long long int cntFlow = 0;
    for (int &i = lastVisitedEdge[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (depth[nextPt] == depth[cntPt] + 1 && arr[i].capacity > 0)
        {
            long long int flowInc = findAguPath(nextPt, endPt, min(minCap - cntFlow, arr[i].capacity));
            if (flowInc == 0)
            {
                depth[nextPt] = -1;
            }
            else
            {
                arr[i].capacity -= flowInc;
                arr[i ^ 1].capacity += flowInc;
                cntFlow += flowInc;
                if (cntFlow == minCap)
                    break;
            }
        }
    }

    return cntFlow;
}

long long int dinic(int startPt, int endPt)
{
    long long int ans = 0;
    while (updateDepth(startPt, endPt))
    {
        for (int i = 0; i < vertexNum; i++)
            lastVisitedEdge[i] = head[i];

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
    cin.tie(0);
    cout.tie(0);
    memset(head, -1, sizeof(head));
    arrPt = 0;
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
