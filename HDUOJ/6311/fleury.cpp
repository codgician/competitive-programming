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

#define VERTEX_SIZE 100100
#define EDGE_SIZE 400400

typedef struct _Edge
{
    int to;
    int id;
    bool hasVisited;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int degArr[VERTEX_SIZE];
int vertexNum, edgeNum;

bool hasVisited[VERTEX_SIZE];
vector<int> ansArr[EDGE_SIZE];
int pathNum;

void addEdge(int from, int to, int id)
{
    arr[arrPt] = {to, id, false, head[from]};
    head[from] = arrPt++;
}

void fleury(int cntPt)
{
    hasVisited[cntPt] = true;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        if (!arr[i].hasVisited)
        {
            arr[i].hasVisited = true;
            arr[i ^ 1].hasVisited = true;
            fleury(arr[i].to);
            if (arr[i].id == 0)
            {
                if (!ansArr[pathNum].empty())
                    ansArr[++pathNum].clear();
            }
            else
            {
                ansArr[pathNum].push_back(arr[i].id);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> vertexNum >> edgeNum)
    {
        memset(head, -1, sizeof(head));
        memset(degArr, 0, sizeof(degArr));
        memset(hasVisited, false, sizeof(hasVisited));
        arrPt = 0;
        pathNum = -1;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to, i + 1);
            addEdge(to, from, -(i + 1));
            degArr[from]++;
            degArr[to]++;
        }

        // Add virtual edges for vertices with odd degree
        int lastOddVertex = -1;
        for (int i = 0; i < vertexNum; i++)
        {
            if (degArr[i] & 1)
            {
                if (lastOddVertex != -1)
                {
                    addEdge(lastOddVertex, i, 0);
                    addEdge(i, lastOddVertex, 0);
                    lastOddVertex = -1;
                }
                else
                {
                    lastOddVertex = i;
                }
            }
        }

        for (int i = 0; i < vertexNum; i++)
        {
            if (!hasVisited[i] && (degArr[i] & 1))
            {
                ansArr[++pathNum].clear();
                fleury(i);
                // Since we've added virtual edges, it might end up with a blank path
                if (ansArr[pathNum].empty())
                    pathNum--;
            }
        }

        for (int i = 0; i < vertexNum; i++)
        {
            if (!hasVisited[i] && degArr[i] > 0)
            {
                ansArr[++pathNum].clear();
                fleury(i);
            }
        }
        pathNum++;

        cout << pathNum << endl;

        for (int i = 0; i < pathNum; i++)
        {
            cout << ansArr[i].size();
            for (auto rit = ansArr[i].rbegin(); rit != ansArr[i].rend(); ++rit)
            {
                cout << " " << *rit;
            }
            cout << endl;
        }
    }
    return 0;
}