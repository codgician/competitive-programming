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
#define PATH_SIZE 999999
#define INF 10000001
using namespace std;

typedef struct _EdgeNode
{
    int to;
    int length;
    int next;
} EdgeNode;

EdgeNode arr[PATH_SIZE];
int head[NODE_SIZE], dis[NODE_SIZE];
bool isShortest[NODE_SIZE];
int nodeNum;
int arrPt = 0;
priority_queue<pair<int, int> > pq;
// dis[i], i

void addEdge(int from, int to, int length)
{
    for (int i = head[from]; i >= 0; i = arr[i].next)
    {
        if (arr[i].to == to)
        {
            arr[i].length = min(arr[i].length, length);
            return;
        }
    }
    arr[arrPt].to = to;
    arr[arrPt].length = length;
    arr[arrPt].next = head[from];
    head[from] = arrPt;
    arrPt++;
}

void dijkstra(int startPt)
{
    memset(isShortest, false, sizeof(isShortest));
    for (int i = 0; i < nodeNum; i++)
        dis[i] = INF;
    dis[startPt] = 0;
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
                pq.push(make_pair(-dis[arr[i].to], arr[i].to));
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int edgeNum, nearHomeNum, destNum;
    while (cin >> edgeNum >> nearHomeNum >> destNum)
    {
        arrPt = 0;
        nodeNum = 0;
        memset(head, -1, sizeof(head));

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, length;
            cin >> from >> to >> length;
            nodeNum = max(nodeNum, max(from, to));
            addEdge(from, to, length);
            addEdge(to, from, length);
        }
        for (int i = 0; i < nearHomeNum; i++)
        {
            int to;
            cin >> to;
            nodeNum = max(nodeNum, to);
            addEdge(0, to, 0);
        }
        nodeNum++;

        dijkstra(0);

        int ans = INF;
        for (int i = 0; i < destNum; i++)
        {
            int dest;
            cin >> dest;
            ans = min(ans, dis[dest]);
        }
        cout << ans << endl;
    }
    return 0;
}
