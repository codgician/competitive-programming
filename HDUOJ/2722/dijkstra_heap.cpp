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
#define MAX_EDGE 21
#define ROAD_LENGTH 2520
#define NODE_SIZE 999
#define EDGE_SIZE 999999
#define INF 10000001
using namespace std;

typedef struct _Edge
{
    int to;
    int length;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[NODE_SIZE], dis[NODE_SIZE];
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
    int row, column;
    while (cin >> row >> column)
    {
        if (row == 0 && column == 0)
            break;

        arrPt = 0;
        memset(head, -1, sizeof(head));
        nodeNum = MAX_EDGE * row + column + 1;

        for (int i = 0; i <= row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                int speed;
                char dir;
                cin >> speed >> dir;
                if (speed != 0)
                {
                    if (dir == '*')
                    {
                        addEdge(MAX_EDGE * i + j, MAX_EDGE * i + j + 1, ROAD_LENGTH / speed);
                        addEdge(MAX_EDGE * i + j + 1, MAX_EDGE * i + j, ROAD_LENGTH / speed);
                    }
                    else if (dir == '>')
                    {
                        addEdge(MAX_EDGE * i + j, MAX_EDGE * i + j + 1, ROAD_LENGTH / speed);
                    }
                    else if (dir == '<')
                    {
                        addEdge(MAX_EDGE * i + j + 1, MAX_EDGE * i + j, ROAD_LENGTH / speed);
                    }
                }
            }

            if (i < row)
            {
                for (int j = 0; j <= column; j++)
                {
                    int speed;
                    char dir;
                    cin >> speed >> dir;
                    if (speed != 0)
                    {
                        if (dir == '*')
                        {
                            addEdge(MAX_EDGE * i + j, MAX_EDGE * (i + 1) + j, ROAD_LENGTH / speed);
                            addEdge(MAX_EDGE * (i + 1) + j, MAX_EDGE * i + j, ROAD_LENGTH / speed);
                        }
                        else if (dir == 'v')
                        {
                            addEdge(MAX_EDGE * i + j, MAX_EDGE * (i + 1) + j, ROAD_LENGTH / speed);
                        }
                        else if (dir == '^')
                        {
                            addEdge(MAX_EDGE * (i + 1) + j, MAX_EDGE * i + j, ROAD_LENGTH / speed);
                        }
                    }
                }
            }
        }

        dijkstra(0);
        int endPt = MAX_EDGE * row + column;

        if (dis[endPt] == INF)
        {
            cout << "Holiday" << endl;
        }
        else
        {
            cout << dis[endPt] << " blips" << endl;
        }
    }
    return 0;
}
