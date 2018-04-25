#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <climits>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <functional>
#include <iterator>
#define VERTEX_SIZE 2050
#define EDGE_SIZE 4202500
using namespace std;

typedef struct _Node
{
    int x, y;
} Node;

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;

int st[VERTEX_SIZE], topPt;
bool hasSelected[VERTEX_SIZE];

Node keyArr[VERTEX_SIZE], doorArr[VERTEX_SIZE];

int vertexNum;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

bool dfs(int cntPt)
{
    if (hasSelected[cntPt ^ 1])
        return false;
    if (hasSelected[cntPt])
        return true;

    hasSelected[cntPt] = true;
    st[topPt++] = cntPt;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (!dfs(nextPt))
        {
            return false;
        }
    }
    return true;
}

bool twoSat()
{
    memset(hasSelected, false, sizeof(hasSelected));
    for (int i = 0; i < vertexNum; i += 2)
    {
        if (!hasSelected[i] && !hasSelected[i ^ 1])
        {
            topPt = 0;
            if (!dfs(i))
            {
                while (topPt)
                {
                    int cntTop = st[--topPt];
                    hasSelected[cntTop] = false;
                }

                if (!dfs(i ^ 1))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check(int cntNum)
{
    memset(head, -1, sizeof(head));
    memset(hasSelected, false, sizeof(hasSelected));
    arrPt = 0;
    topPt = 0;

    for (int i = 0; i < (vertexNum >> 1); i++)
    {
        addEdge(keyArr[i].x << 1, keyArr[i].y << 1 | 1);
        addEdge(keyArr[i].y << 1, keyArr[i].x << 1 | 1);
    }

    for (int i = 0; i < cntNum; i++)
    {
        addEdge(doorArr[i].x << 1 | 1, doorArr[i].y << 1);
        addEdge(doorArr[i].y << 1 | 1, doorArr[i].x << 1);
    }

    return twoSat();
}

int main()
{
    ios::sync_with_stdio(false);
    int doorNum;
    while (cin >> vertexNum >> doorNum)
    {
        if (vertexNum == 0 && doorNum == 0)
            break;

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> keyArr[i].x >> keyArr[i].y;
        }
        for (int i = 0; i < doorNum; i++)
        {
            cin >> doorArr[i].x >> doorArr[i].y;
        }
        vertexNum <<= 1;
        int leftPt = 0, rightPt = doorNum;
        int ans = 0;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;
            if (check(midPt))
            {
                ans = midPt;
                leftPt = midPt + 1;
            }
            else
            {
                rightPt = midPt - 1;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
