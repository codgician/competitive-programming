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
#include <set>
#include <map>
#define VERTEX_SIZE 500
#define EDGE_SIZE 501000
using namespace std;

const double eps = 1e-10;

typedef struct _Pad
{
    int x, y;
    int radius;
    double freq;
} Pad;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

Pad padArr[VERTEX_SIZE];
Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int vertexNum;

bool hasIntersect(int fstPt, int sndPt)
{
    int dis = abs(padArr[fstPt].x - padArr[sndPt].x) * abs(padArr[fstPt].x - padArr[sndPt].x) + abs(padArr[fstPt].y - padArr[sndPt].y) * abs(padArr[fstPt].y - padArr[sndPt].y);
    int radiusSum = (padArr[fstPt].radius + padArr[sndPt].radius) * (padArr[fstPt].radius + padArr[sndPt].radius);

    if (dis < radiusSum)
        return true;
    else
        return false;
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

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        arrPt = 0;
        memset(head, -1, sizeof(head));
        int padNum, redPt, violetPt;
        cin >> padNum;
        vertexNum = padNum + 1;
        for (int i = 0; i < padNum; i++)
        {
            int x, y, radius;
            double freq;
            cin >> freq >> x >> y >> radius;
            if (fabs(freq - 400.0) < eps)
                redPt = i + 1;
            else if (fabs(freq - 789.0) < eps)
                violetPt = i + 1;
            padArr[i] = {x, y, radius, freq};

            for (int j = 0; j < i; j++)
            {
                if (hasIntersect(i, j))
                {
                    if (fabs(padArr[i].freq - padArr[j].freq) < eps)
                        continue;

                    if (padArr[i].freq < padArr[j].freq)
                        addEdge(i + 1, j + 1, 1);
                    else if (padArr[i].freq > padArr[j].freq)
                        addEdge(j + 1, i + 1, 1);
                }
            }
        }

        int startPt = 0;
        addEdge(startPt, redPt, 2);
        int ans = dinic(startPt, violetPt);
        if (ans == 2)
            cout << "Game is VALID" << endl;
        else
            cout << "Game is NOT VALID" << endl;
    }
    return 0;
}
