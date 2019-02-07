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

#define SIZE 40010

typedef struct _Edge
{
    int to, len, next;
} Edge;

Edge arr[SIZE << 1];
int head[SIZE], arrPt;
int depth[SIZE], dist[SIZE], ancestor[SIZE][20];
int vertexNum, maxDepth;

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void bfs(int startPt)
{
    memset(depth, -1, sizeof(depth));
    memset(dist, 0, sizeof(dist));
    memset(ancestor, -1, sizeof(ancestor));
    queue<int> q;
    q.push(startPt);
    depth[startPt] = 0;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            if (depth[nextPt] != -1)
                continue;
            depth[nextPt] = depth[cntPt] + 1;
            dist[nextPt] = dist[cntPt] + arr[i].len;
            ancestor[nextPt][0] = cntPt;
            for (int j = 1; j <= maxDepth; j++)
                ancestor[nextPt][j] = ancestor[ancestor[nextPt][j - 1]][j - 1];
            q.push(nextPt);
        }
    }
}

int lca(int fstPt, int sndPt)
{
    if (depth[fstPt] > depth[sndPt])
        swap(fstPt, sndPt);
    for (int i = maxDepth; i >= 0; i--)
        if (ancestor[sndPt][i] != -1 && depth[ancestor[sndPt][i]] >= depth[fstPt])
            sndPt = ancestor[sndPt][i];
    if (fstPt == sndPt)
        return fstPt;
    for (int i = maxDepth; i >= 0; i--)
        if (ancestor[fstPt][i] != -1 && ancestor[sndPt][i] != -1 && ancestor[fstPt][i] != ancestor[sndPt][i])
            fstPt = ancestor[fstPt][i], sndPt = ancestor[sndPt][i];
    return ancestor[fstPt][0];
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
        int qNum;
        cin >> vertexNum >> qNum;
        maxDepth = log2(vertexNum) + 1;

        for (int i = 1; i < vertexNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            from--, to--;
            addEdge(from, to, len);
            addEdge(to, from, len);
        }

        bfs(0);

        for (int i = 0; i < qNum; i++)
        {
            int fstPt, sndPt;
            cin >> fstPt >> sndPt;
            fstPt--, sndPt--;
            int ans = dist[fstPt] + dist[sndPt];
            int lcaPt = lca(fstPt, sndPt);
            if (lcaPt != -1)
                ans -= dist[lcaPt] << 1;
            cout << ans << endl;
        }
    }

    return 0;
}