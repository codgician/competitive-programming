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
#include <list>
#include <functional>
#include <iterator>
using namespace std;

#define VERTEX_SIZE 200100
#define EDGE_SIZE 400200

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

bool flag[VERTEX_SIZE];
list<int> lst;

bool hasVisited[VERTEX_SIZE];

int ccSize[VERTEX_SIZE], ccNum;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void bfs()
{
    ccNum = 0;
    queue<int> q;
    memset(hasVisited, false, sizeof(hasVisited));
    memset(flag, false, sizeof(flag));

    while (!lst.empty())
    {
        int cntSize = 1;

        int addPt = lst.front();
        q.push(addPt);
        lst.pop_front();
        hasVisited[addPt] = true;

        while (!q.empty())
        {
            int cntPt = q.front();
            q.pop();

            for (int i = head[cntPt]; i != -1; i = arr[i].next)
            {
                int nextPt = arr[i].to;
                flag[nextPt] = true;
            }

            for (auto it = lst.begin(); it != lst.end(); ++it)
            {
                if (!hasVisited[*it] && !flag[*it])
                {
                    hasVisited[*it] = true;
                    cntSize++;
                    q.push(*it);
                    lst.erase(it--);
                }
            }

            for (int i = head[cntPt]; i != -1; i = arr[i].next)
            {
                int nextPt = arr[i].to;
                flag[nextPt] = false;
            }
        }

        ccSize[ccNum++] = cntSize;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    arrPt = 0;

    int vertexNum, edgeNum;
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

    for (int i = 0; i < vertexNum; i++)
    {
        lst.push_back(i);
    }

    bfs();
    sort(ccSize + 0, ccSize + ccNum);
    cout << ccNum << endl;
    for (int i = 0; i < ccNum; i++)
    {
        cout << ccSize[i];
        if (i < ccNum - 1)
            cout << " ";
        else
            cout << endl;
    }

    return 0;
}