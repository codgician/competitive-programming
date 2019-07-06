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
#include <cassert>
using namespace std;

#define VERTEX_SIZE 1010
#define EDGE_SIZE 1100000

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int vertexNum, edgeNum;

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

int findAugPath(int cntPt, int endPt, int minCap)
{
    if (cntPt == endPt)
        return minCap;

    int cntFlow = 0;
    for (int &i = lastVisitedEdge[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (depth[nextPt] == depth[cntPt] + 1 && arr[i].capacity > 0)
        {
            int flowInc = findAugPath(nextPt, endPt, min(minCap - cntFlow, arr[i].capacity));
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

int dinic(int startPt, int endPt)
{
    int ans = 0;
    while (updateDepth(startPt, endPt))
    {
        for (int i = 0; i < vertexNum; i++)
            lastVisitedEdge[i] = head[i];

        int flowInc =  findAugPath(startPt, endPt, INT_MAX);
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

    int heroNum, monsNum, potNum;
    while (cin >> heroNum >> monsNum >> potNum)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;

        int startPt = heroNum + monsNum;
        int potPt = startPt + 1, endPt = startPt + 2;
        vertexNum = endPt + 1;

        addEdge(startPt, potPt, potNum);
        for (int i = 0; i < heroNum; i++)
        {
            addEdge(startPt, i, 1);
            addEdge(potPt, i, 1);
            int siz;
            cin >> siz;
            while (siz--)
            {
                int cntMons;
                cin >> cntMons;
                addEdge(i, heroNum + cntMons - 1, 1);
            }
        }

        for (int i = 0; i < monsNum; i++)
            addEdge(heroNum + i, endPt, 1);

        int ans = dinic(startPt, endPt);
        cout << ans << endl;
    }

    return 0;
}