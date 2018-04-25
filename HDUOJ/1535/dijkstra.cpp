#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define VERTEX_NUM 1000010
#define EDGE_NUM 2000020
using namespace std;

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[2][EDGE_NUM];
int head[2][VERTEX_NUM], arrPt[2];

long long int dis[VERTEX_NUM];
bool isShortest[VERTEX_NUM];

int vertexNum;

void addEdge(bool graphId, int from, int to, int len)
{
    arr[graphId][arrPt[graphId]] = {to, len, head[graphId][from]};
    head[graphId][from] = arrPt[graphId]++;
}

void dijkstra(bool graphId, int startPt)
{
    memset(isShortest, false, sizeof(isShortest));
    for (int i = 0; i < vertexNum; i++)
        dis[i] = LLONG_MAX;

    dis[startPt] = 0;
    priority_queue<pair<int, int> > pq;
    pq.push(make_pair(0, startPt));

    while (!pq.empty())
    {
        int cntPt = pq.top().second;
        pq.pop();

        if (isShortest[cntPt])
            continue;
        isShortest[cntPt] = true;

        for (int i = head[graphId][cntPt]; i != -1; i = arr[graphId][i].next)
        {
            int nextPt = arr[graphId][i].to;
            if (dis[cntPt] != LLONG_MAX && dis[nextPt] > dis[cntPt] + arr[graphId][i].len)
            {
                dis[nextPt] = dis[cntPt] + arr[graphId][i].len;
                pq.push(make_pair(-dis[nextPt], nextPt));
            }
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
        memset(head, -1, sizeof(head));
        memset(arrPt, 0, sizeof(arrPt));

        int edgeNum;
        cin >> vertexNum >> edgeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, cost;
            cin >> from >> to >> cost;
            from--;
            to--;
            addEdge(0, from, to, cost);
            addEdge(1, to, from, cost);
        }

        dijkstra(0, 0);
        long long int ans = 0;
        for (int i = 1; i < vertexNum; i++)
        {
            ans += dis[i];
        }
        dijkstra(1, 0);
        for (int i = 1; i < vertexNum; i++)
        {
            ans += dis[i];
        }
        cout << ans << endl;
    }
    return 0;
}