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

#define SIZE 200020

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[SIZE];
int head[SIZE], arrPt;

typedef struct _Path
{
    int pt;
    long long int power;
} Path;

int parentArr[SIZE], numArr[SIZE], powerArr[SIZE];
Path pathArr[SIZE];
int pathPt;

int vertexNum;
long long int ans;

bool cmp(Path & fst, Path & snd)
{
    return fst.power > snd.power;
}

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, long long int cntPower)
{
    if (head[cntPt] == -1)
    {
        pathArr[pathPt++] = {cntPt, cntPower};
        return;
    }

    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        dfs(nextPt, cntPower + powerArr[nextPt]);
    }
}

void upgrade(int cntPt, int cntPower, int cntNum, int sourcePt)
{
    if (cntPt == 0)
    {
        ans += (long long int)cntPower * cntNum;
        while (sourcePt != 0)
        {
            numArr[sourcePt] -= cntNum;
            sourcePt = parentArr[sourcePt];
        }
        return;
    }

    if (numArr[cntPt] == 0)
        return;

    upgrade(parentArr[cntPt], cntPower, min(cntNum, numArr[cntPt]), sourcePt);
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> vertexNum)
    {
        cin >> vertexNum;
        memset(head, -1, sizeof(head));
        arrPt = 0;
        vertexNum++;
        for (int i = 1; i < vertexNum; i++)
        {
            cin >> parentArr[i] >> numArr[i] >> powerArr[i];
            addEdge(parentArr[i], i);
        }

        pathPt = 0;
        dfs(0, 0);
        sort(pathArr + 0, pathArr + pathPt, cmp);

        ans = 0;
        for (int i = 0; i < pathPt; i++)
            upgrade(pathArr[i].pt, pathArr[i].power, numArr[pathArr[i].pt], pathArr[i].pt);

        cout << ans << endl;
    }   
    return 0;
}