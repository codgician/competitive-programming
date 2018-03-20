#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define VERTEX_SIZE 210
#define EDGE_SIZE 21000
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int vertexNum, startPt, endPt, n;

int parent[VERTEX_SIZE >> 1];
bool origMatch[VERTEX_SIZE >> 1][VERTEX_SIZE >> 1];

int getParent(int n)
{
    if (parent[n] == n)
    {
        return n;
    }
    else
    {
        parent[n] = getParent(parent[n]);
        return parent[n];
    }
}

void mergeNode(int a, int b)
{
    int aParent = getParent(a);
    int bParent = getParent(b);

    if (aParent != bParent)
    {
        parent[bParent] = aParent;
    }
}

void addEdge(int from, int to, int capacity)
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

int findAguPath(int cntPt, int endPt, int minCapacity)
{
    if (cntPt == endPt)
        return minCapacity;

    int cntFlow = 0;
    int &edgePt = lastVisitedEdge[cntPt];
    while (edgePt != -1)
    {
        if (depth[arr[edgePt].to] == depth[cntPt] + 1 && arr[edgePt].capacity > 0)
        {
            int flowInc = findAguPath(arr[edgePt].to, endPt, min(minCapacity - cntFlow, arr[edgePt].capacity));
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
        int flowInc = findAguPath(startPt, endPt, INT_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

void restoreGraph()
{
    for (int i = 0; i < arrPt; i += 2)
    {
        if (arr[i ^ 1].capacity > 0)
        {
            arr[i].capacity += arr[i ^ 1].capacity;
            arr[i ^ 1].capacity = 0;
        }
    }
}

void updateGraph(int turnNum)
{
    int edgePt = head[startPt];
    while (edgePt != -1)
    {
        arr[edgePt].capacity = turnNum;
        edgePt = arr[edgePt].next;
    }

    for (int i = 0; i < n; i++)
    {
        edgePt = head[i + n + 1];
        while (edgePt != -1)
        {
            if (arr[edgePt].to == endPt)
            {
                arr[edgePt].capacity = turnNum;
                break;
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
        memset(origMatch, false, sizeof(origMatch));
        int m, f;
        cin >> n >> m >> f;
        startPt = 0, endPt = (n << 1) + 1;
        vertexNum = endPt + 1;

        for (int i = 0; i < m; i++)
        {
            int girlId, boyId;
            cin >> girlId >> boyId;
            girlId--;
            boyId--;
            origMatch[girlId][boyId] = true;
        }

        for (int i = 0; i < n; i++)
            parent[i] = i;

        for (int i = 0; i < f; i++)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            mergeNode(a, b);
        }

        if (f > 0)
        {
            for (int i = 0; i < n; i++)
            {
                parent[i] = getParent(parent[i]);
                for (int j = 0; j < n; j++)
                {
                    if (origMatch[i][j])
                        origMatch[parent[i]][j] = true;
                }
            }
        }

        int leftPt = 0, rightPt = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            int cntDegree = 0;
            for (int j = 0; j < n; j++)
            {
                if (f > 0)
                {
                    origMatch[i][j] = origMatch[parent[i]][j];
                }
                if (origMatch[i][j])
                {
                    addEdge(i + 1, j + n + 1, 1);
                    cntDegree++;
                }
            }
            rightPt = min(rightPt, cntDegree);
        }

        bool isFirst = true;
        int ans;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;
            if (isFirst)
            {
                for (int i = 0; i < n; i++)
                {
                    addEdge(startPt, i + 1, midPt);
                    addEdge(i + n + 1, endPt, midPt);
                }
                isFirst = false;
            }
            else
            {
                restoreGraph();
                updateGraph(midPt);
            }

            int cntAns = dinic(startPt, endPt);
            if (cntAns == midPt * n)
            {
                leftPt = midPt + 1;
                ans = midPt;
            }
            else
            {
                rightPt = midPt - 1;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
