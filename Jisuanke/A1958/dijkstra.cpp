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

#define VERTEX_SIZE 100010
#define EDGE_SIZE 200020
#define K_SIZE 11

typedef struct _Node
{
    int pt;
    long long int dis;
    int free;

    bool operator < (const struct _Node & snd) const
    {
        if (dis != snd.dis)
            return dis > snd.dis;
        return free > snd.free;
    }
} Node;

typedef struct _Edge
{
    int to;
    long long int len;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum, edgeNum, freeNum;

long long int dis[VERTEX_SIZE][K_SIZE];
bool isShortest[VERTEX_SIZE][K_SIZE];

void addEdge(int from, int to, long long int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void dijkstra(int startPt)
{
    priority_queue<Node> pq;
    memset(isShortest, false, sizeof(isShortest));
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j <= freeNum; j++)
        {
            dis[i][j] = LLONG_MAX;
        }
    }
    dis[startPt][0] = 0;
    pq.push(Node{startPt, 0, 0});

    while (!pq.empty())
    {
        Node cntNode = pq.top();
        pq.pop();

        if (isShortest[cntNode.pt][cntNode.free])
            continue;
        isShortest[cntNode.pt][cntNode.free] = true;

        for (int i = head[cntNode.pt]; i >= 0; i = arr[i].next)
        {
            int nextPt = arr[i].to;

            if (cntNode.free < freeNum && !isShortest[nextPt][cntNode.free + 1] && dis[nextPt][cntNode.free + 1] > cntNode.dis)
            {
                dis[nextPt][cntNode.free + 1] = cntNode.dis;
                pq.push(Node{nextPt, dis[nextPt][cntNode.free + 1], cntNode.free + 1});
            }

            if (dis[cntNode.pt][cntNode.free] != LLONG_MAX && !isShortest[nextPt][cntNode.free] && dis[nextPt][cntNode.free] > dis[cntNode.pt][cntNode.free] + arr[i].len)
            {
                dis[nextPt][cntNode.free] = dis[cntNode.pt][cntNode.free] + arr[i].len;
                pq.push(Node{nextPt, dis[nextPt][cntNode.free], cntNode.free});
            }
        }
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

        cin >> vertexNum >> edgeNum >> freeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--;
            to--;
            addEdge(from, to, len);
        }

        dijkstra(0);

        cout << dis[vertexNum - 1][freeNum] << endl;
    }
    
    return 0;
}