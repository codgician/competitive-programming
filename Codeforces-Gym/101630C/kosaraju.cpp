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

#define EDGE_SIZE 200020
#define VERTEX_SIZE 200020

typedef struct _Edge
{
    int to;
    bool selected;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum, edgeNum;

bool hasVisited[VERTEX_SIZE];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, false, head[from]};
    head[from] = arrPt++;
}

void dfs(int dir, int cntPt)
{
    hasVisited[cntPt] = true;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;

        if ((i & 1) != dir)
            continue;
        if (hasVisited[nextPt])
            continue;

        dfs(dir, nextPt);
        arr[i].selected = true;
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
        cin >> vertexNum >> edgeNum;

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to);
            addEdge(to, from);
        }

        memset(hasVisited, false, sizeof(hasVisited));
        dfs(0, 0);
        memset(hasVisited, false, sizeof(hasVisited));
        dfs(1, 0);

        int delNum = 0;
        for (int i = 0; i < arrPt && delNum < edgeNum - (vertexNum << 1); i += 2)
        {
            if (!arr[i].selected && !arr[i ^ 1].selected)
            {
                cout << arr[i ^ 1].to + 1 << " " << arr[i].to + 1 << endl;
                delNum++;
            }
        }
    }

    return 0;
}