#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <iterator>
#include <functional>
#define VERTEX_SIZE 1001
#define EDGE_SIZE 20010
#define FUEL_SIZE 101
using namespace std;

typedef struct _Edge
{
    int to;
    int len;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum, edgeNum;

int priceArr[VERTEX_SIZE];

typedef struct _Node
{
    int cost;
    int fuel;
    int pt;

    bool operator < (const struct _Node &b) const
    {
        return cost > b.cost;
    }
} Node;

int dp[VERTEX_SIZE][FUEL_SIZE];

void addEdge(int from, int to, int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

int bfs(int capacity, int startPt, int endPt)
{
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            dp[i][j] = INT_MAX;
        }
    }

    priority_queue<Node> pq;

    Node startState;
    startState.pt = startPt;
    startState.fuel = 0;
    startState.cost = 0;

    pq.push(startState);

    while (!pq.empty())
    {
        Node cntState = pq.top();
        pq.pop();

        if (cntState.pt == endPt)
        {
            return cntState.cost;
        }

        if (cntState.fuel < capacity)
        {
            Node nextState;
            nextState.pt = cntState.pt;
            nextState.fuel = cntState.fuel + 1;
            nextState.cost = cntState.cost + priceArr[cntState.pt];

            if (nextState.cost < dp[nextState.pt][nextState.fuel])
            {
                dp[nextState.pt][nextState.fuel] = nextState.cost;
                pq.push(nextState);
            }
        }

        for (int i = head[cntState.pt]; i != -1; i = arr[i].next)
        {
            if (cntState.fuel >= arr[i].len)
            {
                Node nextState;
                nextState.pt = arr[i].to;
                nextState.fuel = cntState.fuel - arr[i].len;
                nextState.cost = cntState.cost;

                if (nextState.cost < dp[nextState.pt][nextState.fuel])
                {
                    dp[nextState.pt][nextState.fuel] = nextState.cost;
                    pq.push(nextState);
                }
            }
        }
    }
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> vertexNum >> edgeNum)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;

        for (int i = 0; i < vertexNum; i++)
        {
            cin >> priceArr[i];
        }
        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, len;
            cin >> from >> to >> len;
            addEdge(from, to, len);
            addEdge(to, from, len);
        }

        int qNum;
        cin >> qNum;
        while (qNum--)
        {
            int capacity, startPt, endPt;
            cin >> capacity >> startPt >> endPt;

            int ans = bfs(capacity, startPt, endPt);
            if (ans == -1)
                cout << "impossible" << endl;
            else
                cout << ans << endl;
        }
    }
    return 0;
}