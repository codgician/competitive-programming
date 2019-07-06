#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <iterator>
using namespace std;

#define EDGE_SIZE 98200
#define VERTEX_SIZE 410

typedef struct _Movie
{
    int startPt, endPt;
    int happVal;
    bool type;
} Movie;

Movie movieArr[VERTEX_SIZE];

typedef struct _Edge
{
    int to;
    int capacity;
    int cost;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int dis[VERTEX_SIZE], minCapacity[VERTEX_SIZE], pre[VERTEX_SIZE];
bool inQueue[VERTEX_SIZE];
int vertexNum;

void addEdge(int from, int to, int capacity, int cost)
{
    arr[arrPt] = {to, capacity, cost, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, -cost, head[to]};
    head[to] = arrPt++;
}

void updateCapacity(int startPt, int endPt)
{
    int cntPt = endPt;
    while (cntPt != startPt)
    {
        int edgePt = pre[cntPt];
        arr[edgePt].capacity -= minCapacity[endPt];
        arr[edgePt ^ 1].capacity += minCapacity[endPt];
        cntPt = arr[edgePt ^ 1].to;
    }
}

bool findAugPath(int startPt, int endPt)
{
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    memset(inQueue, false, sizeof(inQueue));
    queue<int> q;

    q.push(startPt);
    dis[startPt] = 0;
    minCapacity[startPt] = INT_MAX;
    inQueue[startPt] = true;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();
        inQueue[cntPt] = false;

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            if (arr[edgePt].capacity > 0 && dis[cntPt] != INT_MAX && dis[arr[edgePt].to] > dis[cntPt] + arr[edgePt].cost)
            {
                dis[arr[edgePt].to] = dis[cntPt] + arr[edgePt].cost;
                minCapacity[arr[edgePt].to] = min(minCapacity[cntPt], arr[edgePt].capacity);
                pre[arr[edgePt].to] = edgePt;

                if (!inQueue[arr[edgePt].to])
                {
                    q.push(arr[edgePt].to);
                    inQueue[arr[edgePt].to] = true;
                }
            }
            edgePt = arr[edgePt].next;
        }
    }

    if (dis[endPt] == INT_MAX)
        return false;
    return true;
}

void edmondsKarp(int startPt, int endPt, int &flow, int &cost)
{
    while (findAugPath(startPt, endPt))
    {
        updateCapacity(startPt, endPt);
        flow += minCapacity[endPt];
        cost += dis[endPt] * minCapacity[endPt];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        int dayLen, movNum, audNum, loseVal;
        cin >> dayLen >> movNum >> audNum >> loseVal;

        int gStartPt = movNum << 1;
        int startPt = gStartPt + 1, endPt = gStartPt + 2;
        vertexNum = gStartPt + 3;

        addEdge(gStartPt, startPt, audNum, 0);

        for (int i = 0; i < movNum; i++)
        {
            cin >> movieArr[i].startPt >> movieArr[i].endPt >> movieArr[i].happVal >> movieArr[i].type;
            addEdge(startPt, i << 1, 1, -movieArr[i].happVal);
            addEdge(i << 1, i << 1 | 1, 1, 0);
            addEdge(i << 1 | 1, endPt, 1, 0);
        }

        for (int i = 0; i < movNum; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (movieArr[j].endPt <= movieArr[i].startPt)
                {
                    int cntHappVal = movieArr[i].happVal;
                    if (movieArr[i].type == movieArr[j].type)
                        cntHappVal -= loseVal;
                    addEdge(j << 1 | 1, i << 1, 1, -cntHappVal);
                }
                else if (movieArr[i].endPt <= movieArr[j].startPt)
                {
                    int cntHappVal = movieArr[j].happVal;
                    if (movieArr[i].type == movieArr[j].type)
                        cntHappVal -= loseVal;
                    addEdge(i << 1 | 1, j << 1, 1, -cntHappVal);
                }
            }
        }

        int flow = 0, cost = 0;
        edmondsKarp(gStartPt, endPt, flow, cost);
        cout << -cost << endl;
    }
    return 0;
}