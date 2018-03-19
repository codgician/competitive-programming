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
#define VERTEX_NUM 1040
#define EDGE_NUM 23000
using namespace std;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

Edge arr[EDGE_NUM];
int head[VERTEX_NUM], arrPt;
int depth[VERTEX_NUM], lastVisitedEdge[VERTEX_NUM];
int typeNum[VERTEX_NUM];
int vertexNum;

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

int main()
{
    ios::sync_with_stdio(false);
    int personNum, planetNum;
    while (cin >> personNum >> planetNum)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        memset(typeNum, 0, sizeof(typeNum));
        for (int i = 0; i < personNum; i++)
        {
            int cntType = 0;
            for (int j = 0; j < planetNum; j++)
            {
                bool canLive;
                cin >> canLive;
                if (canLive)
                    cntType += (1 << j);
            }
            typeNum[cntType]++;
        }

        int startPt = 0, endPt = (1 << planetNum) + planetNum;
        vertexNum = endPt + 1;
        for (int i = 1; i < (1 << planetNum); i++)
        {
            if (typeNum[i])
            {
                addEdge(startPt, i, typeNum[i]);
                for (int j = 0; j < planetNum; j++)
                {
                    if (i & (1 << j))
                        addEdge(i, (1 << planetNum) + j, INT_MAX);
                }
            }
        }
        for (int i = 0; i < planetNum; i++)
        {
            int capacity;
            cin >> capacity;
            addEdge((1 << planetNum) + i, endPt, capacity);
        }

        int ans = dinic(startPt, endPt);
        if (ans == personNum)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
