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
#define MAX_CORD 1000000
#define VERTEX_SIZE 1010
#define EDGE_SIZE 1020100
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

bool hasSelected[VERTEX_SIZE];
int st[VERTEX_SIZE], topPt;

Node cordArr[VERTEX_SIZE], s1, s2;
int s1Dis[VERTEX_SIZE], s2Dis[VERTEX_SIZE];
Node hateArr[VERTEX_SIZE], likeArr[VERTEX_SIZE];

int vertexNum;
int hateNum, likeNum, sDis;

int getDis(Node &a, Node &b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

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
                while (topPt > 0)
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

bool check(int maxLen)
{
    memset(head, -1, sizeof(head));
    arrPt = 0;

    for (int i = 0; i < (vertexNum >> 1); i++)
    {
        bool s1ExceedLimit = false;
        if (s1Dis[i] > maxLen)
        {
            addEdge(i << 1, i << 1 | 1);
            s1ExceedLimit = true;
        }

        if (s2Dis[i] > maxLen)
        {
            if (s1ExceedLimit)
                return false;
            addEdge(i << 1 | 1, i << 1);
        }
    }

    for (int i = 0; i < (vertexNum >> 1); i++)
    {
        for (int j = i + 1; j < (vertexNum >> 1); j++)
        {
            if (s1Dis[i] + s1Dis[j] > maxLen)
            {
                addEdge(i << 1, j << 1 | 1);
                addEdge(j << 1, i << 1 | 1);
            }

            if (s2Dis[i] + s2Dis[j] > maxLen)
            {
                addEdge(i << 1 | 1, j << 1);
                addEdge(j << 1 | 1, i << 1);
            }

            if (s1Dis[i] + s2Dis[j] + sDis > maxLen)
            {
                addEdge(i << 1, j << 1);
                addEdge(j << 1 | 1, i << 1 | 1);
            }

            if (s1Dis[j] + s2Dis[i] + sDis > maxLen)
            {
                addEdge(j << 1, i << 1);
                addEdge(i << 1 | 1, j << 1 | 1);
            }
        }
    }

    for (int i = 0; i < hateNum; i++)
    {
        int fst = hateArr[i].x;
        int snd = hateArr[i].y;

        addEdge(fst << 1, snd << 1 | 1);
        addEdge(snd << 1, fst << 1 | 1);
        addEdge(fst << 1 | 1, snd << 1);
        addEdge(snd << 1 | 1, fst << 1);
    }

    for (int i = 0; i < likeNum; i++)
    {
        int fst = likeArr[i].x;
        int snd = likeArr[i].y;

        addEdge(fst << 1, snd << 1);
        addEdge(snd << 1, fst << 1);
        addEdge(fst << 1 | 1, snd << 1 | 1);
        addEdge(snd << 1 | 1, fst << 1 | 1);
    }

    return twoSat();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> vertexNum >> hateNum >> likeNum)
    {
        
        vertexNum <<= 1;
        cin >> s1.x >> s1.y >> s2.x >> s2.y;
        for (int i = 0; i < (vertexNum >> 1); i++)
        {
            cin >> cordArr[i].x >> cordArr[i].y;
            s1Dis[i] = getDis(s1, cordArr[i]);
            s2Dis[i] = getDis(s2, cordArr[i]);
        }

        for (int i = 0; i < hateNum; i++)
        {
            cin >> hateArr[i].x >> hateArr[i].y;
            hateArr[i].x--;
            hateArr[i].y--;
        }
        for (int i = 0; i < likeNum; i++)
        {
            cin >> likeArr[i].x >> likeArr[i].y;
            likeArr[i].x--;
            likeArr[i].y--;
        }

        sDis = getDis(s1, s2);

        int ans = -1;
        int leftPt = 0, rightPt = MAX_CORD << 3;
        while (leftPt <= rightPt)
        {
            int midPt = (leftPt + rightPt) >> 1;

            if (check(midPt))
            {
                ans = midPt;
                rightPt = midPt - 1;
            }
            else
            {
                leftPt = midPt + 1;
            }
        }

        cout << ans << endl;
    }
    return 0;
}
