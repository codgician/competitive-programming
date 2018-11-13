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

#define VERTEX_SIZE 300010
#define EDGE_SIZE 600020

typedef struct _Edge
{
    int to;
    long long int len;
    int id;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

long long int dis[VERTEX_SIZE];
bool isShortest[VERTEX_SIZE];

int ansArr[VERTEX_SIZE], ansPt; 

int vertexNum, edgeNum, k;

void addEdge(int from, int to, long long int len, int id)
{
    arr[arrPt] = {to, len, id, head[from]};
    head[from] = arrPt++;
}

void dijkstra(int startPt)
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
            if (dis[cntPt] != LLONG_MAX && dis[nextPt] > dis[cntPt] + arr[i].len)
            {
                dis[nextPt] = dis[cntPt] + arr[i].len;
                pq.push(make_pair(-dis[nextPt], nextPt));
            }
        }
    }
}

void bfs(int startPt)
{
    memset(isShortest, false, sizeof(isShortest));
    queue<int> q;
    q.push(startPt);
    isShortest[startPt] = true;

    ansPt = 0;
    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            if (isShortest[nextPt])
                continue;
            if (dis[cntPt] + arr[i].len != dis[nextPt])
                continue;

            ansArr[ansPt++] = arr[i].id;
            q.push(nextPt);
            isShortest[nextPt] = true;

            if (ansPt == k)
                return;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(head, -1, sizeof(head));
    arrPt = 0;

    cin >> vertexNum >> edgeNum >> k;
    for (int i = 0; i < edgeNum; i++)
    {
        int from, to;
        long long int len;
        cin >> from >> to >> len;
        from--, to--;

        addEdge(from, to, len, i + 1);
        addEdge(to, from, len, i + 1);
    }

    if (k == 0)
    {
        cout << 0 << endl;
        return 0;
    }

    dijkstra(0);
    bfs(0);

    cout << ansPt << endl;
    for (int i = 0; i < ansPt; i++)
    {
        cout << ansArr[i];
        if (i < ansPt - 1)
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}