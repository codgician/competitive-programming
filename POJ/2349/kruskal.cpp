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

#define VERTEX_SIZE 510
#define EDGE_SIZE 260100

typedef struct _Vertex
{
    int x, y;
} Vertex;

Vertex vArr[VERTEX_SIZE];

typedef struct _Edge
{
    int from;
    int to;
    double len;
} Edge;

Edge arr[EDGE_SIZE];

int parent[VERTEX_SIZE];
double mstArr[VERTEX_SIZE];

int vertexNum, edgeNum;

double getDis(Vertex & fst, Vertex & snd)
{
    return sqrt((fst.x - snd.x) * (fst.x - snd.x) + (fst.y - snd.y) * (fst.y - snd.y));
}

bool cmp(Edge fst, Edge snd)
{
    return fst.len < snd.len;
}

int getParent(int n)
{
    if (parent[n] == n)
        return n;
    else
    {
        parent[n] = getParent(parent[n]);
        return parent[n];
    }
}

bool mergeNode(int fst, int snd)
{
    int fstParent = getParent(fst);
    int sndParent = getParent(snd);

    if (fstParent != sndParent)
    {
        parent[sndParent] = fstParent;
        return true;
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        edgeNum = 0;
        int satNum;
        cin >> satNum >> vertexNum;
        for (int i = 0; i < vertexNum; i++)
        {
            cin >> vArr[i].x >> vArr[i].y;
            for (int j = 0; j < i; j++)
            {
                arr[edgeNum].from = j;
                arr[edgeNum].to = i;
                arr[edgeNum].len = getDis(vArr[i], vArr[j]);
                edgeNum++;
            }
        }

        sort(arr + 0, arr + edgeNum, cmp);
        for (int i = 0; i < vertexNum; i++)
            parent[i] = i;

        int num = 0;
        for (int i = 0; i < edgeNum && num < vertexNum; i++)
        {
            if (mergeNode(arr[i].from, arr[i].to))
            {
                mstArr[num++] = arr[i].len;
            }
        }
        sort(mstArr + 0, mstArr + num);
        cout << fixed << setprecision(2) << mstArr[vertexNum - satNum - 1] << endl;
    }
    return 0;
}