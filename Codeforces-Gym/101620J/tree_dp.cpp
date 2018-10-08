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

#define EDGE_SIZE 2000020
#define VERTEX_SIZE 1000010

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum;

int sizeArr[VERTEX_SIZE], sizeNum[VERTEX_SIZE];
int ansArr[VERTEX_SIZE], ansPt;

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int fatherPt)
{
    sizeArr[cntPt] = 1;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == fatherPt)
            continue;
        dfs(nextPt, cntPt);
        sizeArr[cntPt] += sizeArr[nextPt];
    }
    sizeNum[sizeArr[cntPt]]++;
}

bool check(int subNum)
{
    int subSize = vertexNum / subNum, cntNum = 0;
    for (int i = subSize; i <= vertexNum; i += subSize)
        cntNum += sizeNum[i];
    return cntNum == subNum;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> vertexNum)
    {
        memset(head, -1, sizeof(head));
        memset(sizeArr, 0, sizeof(sizeArr));
        memset(sizeNum, 0, sizeof(sizeNum));
        arrPt = 0;

        for (int i = 0; i < vertexNum - 1; i++)
        {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            addEdge(from, to);
            addEdge(to, from);
        }
    
        dfs(0, -1);

        ansPt = 0;
        for (int i = 2; i * i <= vertexNum; i++)
        {
            if (vertexNum % i != 0)
                continue;

            if (check(i))
                ansArr[ansPt++] = i - 1;
            if (i * i != vertexNum && check(vertexNum / i))
                ansArr[ansPt++] = vertexNum / i - 1;
        }

        sort(ansArr + 0, ansArr + ansPt);

        for (int i = 0; i < ansPt; i++)
            cout << ansArr[i] << " ";
        cout << vertexNum - 1 << endl;
    }

    return 0;
}