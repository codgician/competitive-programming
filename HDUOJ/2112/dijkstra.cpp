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
#define NODE_SIZE 151
#define PATH_SIZE 20010
#define INF 10000001
using namespace std;

typedef struct _EdgeNode
{
    int to;
    int length;
    int next;
} EdgeNode;

EdgeNode arr[PATH_SIZE];
int head[NODE_SIZE], dis[NODE_SIZE];
bool isShortest[NODE_SIZE];
int nodeNum, pathNum;
int arrPt = 0;
map<string, int> mp;
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
            if (dis[arr[i].to] > dis[cntNode] + arr[i].length)
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
    while (cin >> pathNum)
    {
        if (pathNum < 0)
            break;

        arrPt = 0;
        mp.clear();
        memset(head, -1, sizeof(head));

        string startStr, endStr;
        cin >> startStr >> endStr;
        mp[startStr] = 1;
        mp[endStr] = 2;

        int startPt = 0, endPt = 1;
        if (startStr == endStr)
        {
            endPt = 0;
        }

        nodeNum = 2;
        for (int i = 0; i < pathNum; i++)
        {
            int length;
            cin >> startStr >> endStr >> length;
            if (mp[startStr] == 0)
                mp[startStr] = ++nodeNum;
            if (mp[endStr] == 0)
                mp[endStr] = ++nodeNum;
            addEdge(mp[startStr] - 1, mp[endStr] - 1, length);
            addEdge(mp[endStr] - 1, mp[startStr] - 1, length);
        }

        dijkstra(startPt);

        if (dis[endPt] == INF)
            cout << -1 << endl;
        else
            cout << dis[endPt] << endl;
    }
    return 0;
}
