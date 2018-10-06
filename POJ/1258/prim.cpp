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

#define VERTEX_SIZE 110
#define EDGE_SIZE 20200

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int dis[VERTEX_SIZE];
bool hasVisited[VERTEX_SIZE];

int vertexNum;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

int prim(int startPt)
{
    int ans = 0;
    memset(hasVisited, false, sizeof(hasVisited));
    for (int i = 0; i < vertexNum; i++)
        dis[i] = INT_MAX;
    dis[startPt] = 0;
    priority_queue<pair<int, int> > pq;
    pq.push(make_pair(0, startPt));

    while (!pq.empty())
    {
        pair<int, int> cntTop = pq.top();
        int cntDis = -cntTop.first;
        int cntPt = cntTop.second;
        pq.pop();

        if (hasVisited[cntPt])
            continue;
        hasVisited[cntPt] = true;

        ans += cntDis;

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            int nextLen = arr[i].len;

            if (nextLen >= dis[nextPt])
                continue;
            if (hasVisited[nextPt])
                continue;

            dis[nextPt] = nextLen;
            pq.push(make_pair(-nextLen, nextPt));
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int num;
    while (cin >> num)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {
                int len;
                cin >> len;
                if (i != j)
                    addEdge(i, j, len);
            }
        }

        vertexNum = num;
        int ans = prim(0);
        cout << ans << endl;
    }
    return 0;
}