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

#define VERTEX_SIZE 3010
#define EDGE_SIZE 6020

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

long long int dis[VERTEX_SIZE];
bool isShortest[VERTEX_SIZE];
int vertexNum, edgeNum;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void dijkstra(int startPt, int delta)
{
    for (int i = 0; i < vertexNum; i++)
    {
        isShortest[i] = false;
        dis[i] = LLONG_MAX;
    }

    priority_queue<pair<long long int, int> > pq;
    pq.push(make_pair(0, startPt));
    dis[startPt] = 0;

    while (!pq.empty())
    {
        int cntPt = pq.top().second;
        pq.pop();
        if (isShortest[cntPt])
            continue;
        isShortest[cntPt] = true;

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            int len = max(0, arr[i].len - delta);

            if (dis[cntPt] != LLONG_MAX && dis[nextPt] > dis[cntPt] + len)
            {
                dis[nextPt] = dis[cntPt] + len;
                pq.push(make_pair(-dis[nextPt], nextPt));
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int k;
    while (cin >> vertexNum >> edgeNum >> k)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--;
            to--;
            addEdge(from, to, len);
            addEdge(to, from, len);
        }

        dijkstra(0, 0);
        long long int ans = dis[vertexNum - 1];

        for (int i = 0; i < (edgeNum << 1); i += 2)
        {
            dijkstra(0, arr[i].len);
            ans = min(ans, dis[vertexNum - 1] + 1ll * k * arr[i].len);
        }

        cout << ans << endl;
    }

    return 0;
}