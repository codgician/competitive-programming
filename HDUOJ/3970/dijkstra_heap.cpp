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
#define NODE_SIZE 1001
#define PATH_SIZE 200002
#define INF 100000001
using namespace std;

typedef struct _EdgeNode
{
    int to;
    int length;
    int cost;
    int next;
} EdgeNode;

EdgeNode arr[PATH_SIZE];
int head[NODE_SIZE], dis[NODE_SIZE], cost[NODE_SIZE];
bool isShortest[NODE_SIZE];
int nodeNum, edgeNum;
int arrPt = 0;
priority_queue<pair<int, int> > pq;
// dis[i], i

void addEdge(int from, int to, int length, int cost)
{
    for (int i = head[from]; i >= 0; i = arr[i].next)
    {
        if (arr[i].to == to)
        {
            if (arr[i].length > length)
            {
                arr[i].length = length;
                arr[i].cost = cost;
            }
            else if (arr[i].length == length)
            {
                arr[i].cost = min(arr[i].cost, cost);
            }
            return;
        }
    }
    arr[arrPt].to = to;
    arr[arrPt].length = length;
    arr[arrPt].cost = cost;
    arr[arrPt].next = head[from];
    head[from] = arrPt;
    arrPt++;
}

void dijkstra(int startPt)
{
    memset(isShortest, false, sizeof(isShortest));
    for (int i = 0; i < nodeNum; i++)
    {
        dis[i] = INF;
        cost[i] = INF;
    }
    dis[startPt] = 0;
    cost[startPt] = 0;
    pq.push(make_pair(0, startPt));

    while (!pq.empty())
    {
        int cntNode = pq.top().second;
        pq.pop();
        if (isShortest[cntNode])
            continue;
        isShortest[cntNode] = true;

        for (int i = head[cntNode]; i >= 0; i = arr[i].next)
        {
            if (dis[arr[i].to] > dis[cntNode] + arr[i].length)
            {
                dis[arr[i].to] = dis[cntNode] + arr[i].length;
                cost[arr[i].to] = cost[cntNode] + arr[i].cost;
                pq.push(make_pair(-dis[arr[i].to], arr[i].to));
            }
            else if (dis[arr[i].to] == dis[cntNode] + arr[i].length)
            {
                if (cost[arr[i].to] > cost[cntNode] + arr[i].cost)
                    cost[arr[i].to] = cost[cntNode] + arr[i].cost;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> nodeNum >> edgeNum)
    {
        if (nodeNum == 0 && edgeNum == 0)
            break;

        memset(head, -1, sizeof(head));
        arrPt = 0;

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, length, cost;
            cin >> from >> to >> length >> cost;
            from--;
            to--;
            addEdge(from, to, length, cost);
            addEdge(to, from, length, cost);
        }

        int startPt, endPt;
        cin >> startPt >> endPt;
        startPt--;
        endPt--;

        dijkstra(startPt);

        cout << dis[endPt] << " " << cost[endPt] << endl;
    }
    return 0;
}
