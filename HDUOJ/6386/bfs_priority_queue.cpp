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

#define VERTEX_NUM 100010
#define EDGE_NUM 400040

typedef struct _State
{
    int pt;
    int prev, cost;

    bool operator < (const struct _State & snd) const
    {
        return cost > snd.cost;
    }
} State;

typedef struct _Edge
{
    int to;
    int type;
    int next;
} Edge;

Edge arr[EDGE_NUM];
int head[VERTEX_NUM], arrPt;

int dp[VERTEX_NUM];
int vertexNum, edgeNum;

void addEdge(int from, int to, int type)
{
    arr[arrPt] = {to, type, head[from]};
    head[from] = arrPt++;
}

int bfs(int startPt, int endPt)
{
    for (int i = 0; i < vertexNum; i++)
        dp[i] = INT_MAX;
    priority_queue<State> pq;
    State startState = {startPt, -1, 0};
    pq.push(startState);
    dp[startPt] = 0;

    while (!pq.empty())
    {
        State cntState = pq.top();
        pq.pop();

        int cntPt = cntState.pt;

        if (cntPt == endPt)
        {
            return cntState.cost;
        }

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            State nextState = {arr[i].to, arr[i].type, cntState.cost};
            if (arr[i].type != cntState.prev)
                nextState.cost++;

            if (nextState.cost >= dp[arr[i].to])
                continue;
            dp[arr[i].to] = nextState.cost;

            pq.push(nextState);
        }
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> vertexNum >> edgeNum)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, type;
            cin >> from >> to >> type;
            from--;
            to--;
            type--;
            addEdge(from, to, type);
            addEdge(to, from, type);
        }

        int ans = bfs(0, vertexNum - 1);
        cout << ans << endl;
    }
    return 0;
}