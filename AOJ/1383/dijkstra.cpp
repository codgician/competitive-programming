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

const long long int mod = 1e9 + 7;

#define EDGE_SIZE 100010
#define VERTEX_SIZE 100010

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[2][EDGE_SIZE];
int head[2][VERTEX_SIZE], arrPt[2];

long long int dis[2][VERTEX_SIZE], num[2][VERTEX_SIZE];
bool isShortest[VERTEX_SIZE];

int vertexNum, edgeNum;

void addEdge(int id, int from, int to, int len)
{
    arr[id][arrPt[id]] = {to, len, head[id][from]};
    head[id][from] = arrPt[id]++;
}

void dijkstra(int id, int startPt)
{
    for (int i = 0; i < vertexNum; i++)
    {
        dis[id][i] = LLONG_MAX;
        num[id][i] = 0;
        isShortest[i] = false;
    }

    priority_queue<pair<long long int, int> > pq;
    pq.push(make_pair(0, startPt));
    dis[id][startPt] = 0;
    num[id][startPt] = 1;

    while (!pq.empty())
    {
        int cntPt = pq.top().second;
        pq.pop();

        if (isShortest[cntPt])
            continue;
        isShortest[cntPt] = true;

        for (int i = head[id][cntPt]; i != -1; i = arr[id][i].next)
        {
            int nextPt = arr[id][i].to;
            if (dis[id][cntPt] != LLONG_MAX)
            {
                if (dis[id][nextPt] > dis[id][cntPt] + arr[id][i].len)
                {
                    dis[id][nextPt] = dis[id][cntPt] + arr[id][i].len;
                    num[id][nextPt] = num[id][cntPt];
                    pq.push(make_pair(-dis[id][nextPt], nextPt));
                }
                else if (dis[id][nextPt] == dis[id][cntPt] + arr[id][i].len)
                {
                    num[id][nextPt] = (num[id][nextPt] + num[id][cntPt]) % mod;
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> vertexNum >> edgeNum)
    {
        memset(head, -1, sizeof(head));
        memset(arrPt, 0, sizeof(arrPt));
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--;
            to--;
            addEdge(0, from, to, len);
            addEdge(1, to, from, len);
        }

        dijkstra(0, 0);
        dijkstra(1, 1);

        for (int i = 0; i < edgeNum; i++)
        {
            int from = arr[1][i].to;
            int to = arr[0][i].to;
            int len = arr[0][i].len;

            if (dis[0][to] != LLONG_MAX && dis[1][from] != LLONG_MAX && dis[0][to] + dis[1][from] + len < dis[0][1])
            {
                cout << "HAPPY" << endl;
            }
            else if (dis[0][from] != LLONG_MAX && dis[1][to] != LLONG_MAX && dis[0][from] + dis[1][to] + len == dis[0][1] && num[0][from] * num[1][to] % mod == num[0][1])
            {
                // is Bridge
                cout << "SAD" << endl;
            }
            else
            {
                cout << "SOSO" << endl;
            }
        }
    }

    return 0;
}