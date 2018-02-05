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
#define NODE_SIZE 110
#define PATH_SIZE 20002
#define BAG_SIZE 2000202
#define INF 100000001
using namespace std;

typedef struct _Edge
{
    int to;
    int length;
    int next;
} Edge;

Edge arr[PATH_SIZE];
int head[NODE_SIZE], dis[NODE_SIZE], power[NODE_SIZE];
int dp[BAG_SIZE];
bool isShortest[NODE_SIZE];

int nodeNum, edgeNum;
int arrPt = 0;

priority_queue<pair<int, int> > pq;
// dis[i], i

void addEdge(int from, int to, int length)
{
    for (int i = head[from]; i >= 0; i = arr[i].next)
    {
        if (arr[i].to == to)
        {
            arr[i].length = min(arr[i].length, length);
            return;
        }
    }
    arr[arrPt].to = to;
    arr[arrPt].length = length;
    arr[arrPt].next = head[from];
    head[from] = arrPt;
    arrPt++;
}

void dijkstra(int startPt)
{
    memset(isShortest, false, sizeof(isShortest));
    for (int i = 0; i < nodeNum; i++)
        dis[i] = INF;
    dis[startPt] = 0;
    pq.push(make_pair(0, startPt));

    while (!pq.empty())
    {
        int cntNode = pq.top().second;
        pq.pop();
        if (isShortest[cntNode])
            continue;
        isShortest[cntNode] = true;

        for (int i = head[cntNode]; i >= 0; i = arr[i].next)
        {
            if (dis[cntNode] != INF && dis[arr[i].to] > dis[cntNode] + arr[i].length)
            {
                dis[arr[i].to] = dis[cntNode] + arr[i].length;
                pq.push(make_pair(-dis[arr[i].to], arr[i].to));
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;
        cin >> nodeNum >> edgeNum;
        nodeNum++;

        for (int i = 0; i < edgeNum; i++)
        {
            int from, to, length;
            cin >> from >> to >> length;
            addEdge(from, to, length);
            addEdge(to, from, length);
        }

        dijkstra(0);

        int powerSum = 0, oilSum = 0;
        for (int i = 1; i < nodeNum; i++)
        {
            cin >> power[i];
            powerSum += power[i];
            if (dis[i] != INF)
                oilSum += dis[i];
        }

        memset(dp, 0, sizeof(dp));
        for (int i = 1; i < nodeNum; i++)
        {
            if (dis[i] == INF)
                continue;

            for (int j = oilSum; j >= dis[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - dis[i]] + power[i]);
            }
        }

        bool isPossible = false;
        int ans;
        for (int i = 0; i <= oilSum; i++)
        {
            if (dp[i] >= powerSum / 2 + 1)
            {
                isPossible = true;
                ans = i;
                break;
            }
        }

        if (isPossible)
            cout << ans << endl;
        else
            cout << "impossible" << endl;
    }
    return 0;
}
