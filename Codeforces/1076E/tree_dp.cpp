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
#include <cassert>
using namespace std;

#define SIZE 300010

typedef struct _Edge
{
    int to;
    int next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int vertexNum;
long long int ansArr[SIZE], depArr[SIZE];

vector<pair<int, int> > qArr[SIZE];

void addEdge(int from, int to)
{
    arr[arrPt] = {to, head[from]};
    head[from] = arrPt++;
}

void dfs(int cntPt, int parentPt, int depth, long long int cntSum)
{
    for (auto cnt : qArr[cntPt])
    {
        depArr[depth] += cnt.second;
        if (depth + cnt.first + 1 <= vertexNum)
            depArr[depth + cnt.first + 1] -= cnt.second;
    }

    cntSum += depArr[depth];
    ansArr[cntPt] = cntSum;
    for (int i = head[cntPt]; i != -1; i = arr[i].next)
    {
        int nextPt = arr[i].to;
        if (nextPt == parentPt)
            continue;
        dfs(nextPt, cntPt, depth + 1, cntSum);
    }

    for (auto cnt : qArr[cntPt])
    {
        depArr[depth] -= cnt.second;
        if (depth + cnt.first + 1 <= vertexNum)
            depArr[depth + cnt.first + 1] += cnt.second;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    memset(head, -1, sizeof(head));
    memset(depArr, 0, sizeof(depArr));
    arrPt = 0;
    cin >> vertexNum;
    for (int i = 1; i < vertexNum; i++)
    {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        addEdge(from, to);
        addEdge(to, from);
    }

    int qNum;
    cin >> qNum;
    while (qNum--)
    {
        int cntPt, sub, val;
        cin >> cntPt >> sub >> val;
        cntPt--;
        qArr[cntPt].push_back(make_pair(sub, val));
    }

    dfs(0, -1, 0, 0);

    for (int i = 0; i < vertexNum - 1; i++)
        cout << ansArr[i] << " ";
    cout << ansArr[vertexNum - 1] << endl;

    return 0;
}