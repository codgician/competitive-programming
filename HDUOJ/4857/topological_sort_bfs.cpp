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
#define VERTEX_SIZE 30010
#define EDGE_SIZE 100010
using namespace std;

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], inDegree[VERTEX_SIZE], arrPt;
int ans[VERTEX_SIZE], ansPt;
int vertexNum;
map<pair<int, int>, bool> mp;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void bfs()
{
    priority_queue<int> pq;
    for (int i = 0; i < vertexNum; i++)
    {
        if (inDegree[i] == 0)
        {
            pq.push(i);
        }
    }

    ansPt = 0;
    while (!pq.empty())
    {
        int cntPt = pq.top();
        pq.pop();

        ans[ansPt++] = cntPt;

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            inDegree[arr[edgePt].to]--;
            if (inDegree[arr[edgePt].to] == 0)
                pq.push(arr[edgePt].to);
            edgePt = arr[edgePt].next;
        }
        head[cntPt] = -1;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        mp.clear();
        arrPt = 0;
        memset(head, -1, sizeof(head));
        memset(inDegree, 0, sizeof(inDegree));

        int edgeNum;
        cin >> vertexNum >> edgeNum;

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            if (mp.find(make_pair(from, to)) == mp.end())
            {
                mp[make_pair(from, to)] = true;
                addEdge(to, from);
                inDegree[from]++;
            }
        }
        bfs();
        for (int i = vertexNum - 1; i >= 0; i--)
        {
            cout << ans[i] + 1;
            if (i > 0)
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}
