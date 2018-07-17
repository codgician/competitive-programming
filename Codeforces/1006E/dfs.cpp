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

#define VERTEX_SIZE 200010
#define EDGE_SIZE 200010

typedef struct _Edge
{
    int to;
    int next;   
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int dfsArr[VERTEX_SIZE << 1];
int inTime[VERTEX_SIZE], outTime[VERTEX_SIZE];

int parent[VERTEX_SIZE];

int vertexNum, cntTime;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt)
{
    dfsArr[cntTime] = cntPt;
    inTime[cntPt] = cntTime++;
    int edgePt = head[cntPt];
    while (edgePt != -1)
    {
        int nextPt = arr[edgePt].to;
        dfs(nextPt);
        edgePt = arr[edgePt].next;
    }
    outTime[cntPt] = cntTime;
}

int main()
{
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cntTime = 0;
    arrPt = 0;
    int qNum;
    cin >> vertexNum >> qNum;
    for (int i = 1; i < vertexNum; i++)
    {
        cin >> parent[i];
        parent[i]--;
    }
    for (int i = vertexNum - 1; i > 0; i--)
    {
        addEdge(parent[i], i);
    }

    dfs(0);

    while (qNum--)
    {
        int startPt, pos;
        cin >> startPt >> pos;
        startPt--;
        pos = inTime[startPt] + pos - 1;
        if (pos >= outTime[startPt])
            cout << -1 << endl;
        else
            cout << dfsArr[pos] + 1 << endl;
    }
    return 0;
}