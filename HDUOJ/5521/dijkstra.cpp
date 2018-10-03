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

#define EDGE_SIZE 4000010
#define VERTEX_SIZE 2000010

typedef struct _Edge
{
    int to;
    long long int len;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int vertexNum;

long long int dis[VERTEX_SIZE], ansArr[VERTEX_SIZE];
bool isShortest[VERTEX_SIZE];

void addEdge(int from, int to, long long int len)
{
    arr[arrPt] = {to, len, head[from]};
    head[from] = arrPt++;
}

void dijkstra(int startPt)
{
    for (int i = 0; i < vertexNum; i++)
    {
        isShortest[i] = false;
        dis[i] = LLONG_MAX;
    }

    priority_queue<pair<long long int, int> > pq;
    pq.push(make_pair(0, startPt));
    dis[startPt] = 0;

    while (!pq.empty())
    {
        int cntPt = pq.top().second;
        pq.pop();
        if (isShortest[cntPt])
            continue;
        isShortest[cntPt] = true;

        for (int i = head[cntPt]; i != -1; i = arr[i].next)
        {
            int nextPt = arr[i].to;
            if (dis[cntPt] != LLONG_MAX && dis[nextPt] > dis[cntPt] + arr[i].len)
            {
                dis[nextPt] = dis[cntPt] + arr[i].len;
                pq.push(make_pair(-dis[nextPt], nextPt));
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int caseNum;
    cin >> caseNum;
    for (int t = 1; t <= caseNum; t++)
    {
        memset(head, -1, sizeof(head));
        arrPt = 0;

        int blockNum, areaNum;
        cin >> blockNum >> areaNum;
        vertexNum = blockNum + areaNum;
        for (int i = 0; i < areaNum; i++)
        {
            long long int cntLen;
            int num;
            cin >> cntLen >> num;
            for (int j = 0; j < num; j++)
            {
                int cntPt;
                cin >> cntPt;
                cntPt--;
                addEdge(blockNum + i, cntPt, cntLen);
                addEdge(cntPt, blockNum + i, 0);
            }
        }

        cout << "Case #" << t << ": ";

        dijkstra(0);
        if (dis[blockNum - 1] == LLONG_MAX)
        {
            cout << "Evil John" << endl;
            continue;
        }
        for (int i = 0; i < blockNum; i++)
        {
            ansArr[i] = dis[i];
        }

        dijkstra(blockNum - 1);
        if (dis[0] == LLONG_MAX)
        {
            cout << "Evil John" << endl;
            continue;
        }

        long long int minDis = LLONG_MAX;
        for (int i = 0; i < blockNum; i++)
        {
            ansArr[i] = max(ansArr[i], dis[i]);
            minDis = min(minDis, ansArr[i]);
        }

        cout << minDis << endl;
        bool isFirst = true;
        for (int i = 0; i < blockNum; i++)
        {
            if (ansArr[i] == minDis)
            {
                if (isFirst)
                    isFirst = false;
                else
                    cout << " ";
                cout << i + 1;
            }
        }
        cout << endl;
    }

    return 0;
}