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
using namespace std;

#define VERTEX_SIZE 1010
#define EDGE_SIZE 10010

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int inDeg[VERTEX_SIZE];
int ansArr[VERTEX_SIZE], ansPt;

int dis[VERTEX_SIZE];

int vertexNum, edgeNum;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len,  head[from]};
    head[from] = arrPt++;
    inDeg[to]++;
}

void topo()
{
    queue<int> q;
    for (int i = 0; i < vertexNum; i++)
    {
        if (inDeg[i] == 0)
        {
            dis[i] = 0;
            q.push(i);
        }
    }

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();
        
        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            int len = arr[i].len;

            dis[nextPt] = max(dis[nextPt], dis[cntPt] + len);

            inDeg[nextPt]--;
            if (inDeg[nextPt] == 0)
                q.push(nextPt);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> vertexNum >> edgeNum)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;

        memset(inDeg, 0, sizeof(inDeg));
        memset(dis, 0, sizeof(dis));
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, len;
            from--;
            to--;
            cin >> from >> to >> len;
            addEdge(from, to, len);
        }

        topo();

        int ans = 0;
        for (int i = 0; i < vertexNum; i++)
        {
            ans = max(ans, dis[i]);
        }
        cout << ans + 1 << endl;
    }
    return 0;
}