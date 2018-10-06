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
#define FIX_SIZE 1010
#define NODE_SIZE 110
#define EDGE_SIZE 20010
#define INF 1000000001
using namespace std;

typedef struct _Edge
{
    int to;
    int length;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[NODE_SIZE], dis[NODE_SIZE], fix[FIX_SIZE];
bool isShortest[NODE_SIZE];

int nodeNum, edgeNum;
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
    int destNum, caseId = 1;
    while (cin >> nodeNum >> destNum >> edgeNum)
    {
        if (nodeNum == 0 && destNum == 0 && edgeNum == 0)
            break;

        arrPt = 0;
        memset(head, -1, sizeof(head));
        mp.clear();

        int cntId = 0;
        for (int i = 0; i <= destNum; i++)
        {
            string str;
            cin >> str;
            if (!mp.count(str))
            {
                mp[str] = cntId;
                cntId++;
            }
            if (i > 0)
                fix[i - 1] = mp[str];
        }

        for (int i = 0; i < edgeNum; i++)
        {
            string from, to;
            int length;
            bool canLeft = false, canRight = false;
            char dir[2];

            cin >> from;
            cin >> dir[0] >> dir[1];
            if (dir[0] == '<')
                canLeft = true;
            cin >> length;
            cin >> dir[0] >> dir[1];
            if (dir[1] == '>')
                canRight = true;
            cin >> to;

            if (!mp.count(from))
                mp[from] = cntId++;
            if (!mp.count(to))
                mp[to] = cntId++;

            if (canLeft)
                addEdge(mp[to], mp[from], length);
            if (canRight)
                addEdge(mp[from], mp[to], length);
        }

        dijkstra(0);

        int ans = 0;
        for (int i = 0; i < destNum; i++)
        {
            ans += dis[fix[i]];
        }

        sort(fix + 0, fix + destNum);
        for (int i = 0; i < destNum; i++)
        {
            if (i == 0 || fix[i - 1] != fix[i])
                dijkstra(fix[i]);
            ans += dis[0];
        }

        cout << caseId++ << ". " << ans << endl;
    }
    return 0;
}
