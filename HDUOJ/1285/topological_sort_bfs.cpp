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
#define VERTEX_SIZE 510
#define EDGE_SIZE 251000
using namespace std;

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], inDegree[VERTEX_SIZE], arrPt;
int vertexNum;
map<pair<int, int>, bool> mp;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void bfs()
{
    priority_queue<int, vector<int>, greater<int> > pq;
    for (int i = 0; i < vertexNum; i++)
    {
        if (inDegree[i] == 0)
        {
            pq.push(i);
        }
    }

    bool isFirst = true;
    while (!pq.empty())
    {
        int cntPt = pq.top();
        pq.pop();

        if (isFirst)
            isFirst = false;
        else
            cout << " ";
        cout << cntPt + 1;

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
    int edgeNum;
    while (cin >> vertexNum >> edgeNum)
    {
        mp.clear();
        arrPt = 0;
        memset(head, -1, sizeof(head));
        memset(inDegree, 0, sizeof(inDegree));

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            if (mp.find(make_pair(from, to)) == mp.end())
            {
                mp[make_pair(from, to)] = true;
                addEdge(from, to);
                inDegree[to]++;
            }
        }
        bfs();
        cout << endl;
    }
    return 0;
}
