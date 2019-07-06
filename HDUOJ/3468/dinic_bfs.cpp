#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <iomanip>
#include <climits>
#include <vector>
#include <queue>
#include <map>
#include <set>
#define ROW_COLUMN_SIZE 101
#define CHAR_SIZE 52
#define VERTEX_SIZE 10010
#define EDGE_SIZE 2100000
using namespace std;

typedef struct _Node
{
    int x, y;
} Node;

typedef struct _Edge
{
    int to;
    int capacity;
    int next;
} Edge;

Edge arr[EDGE_SIZE];
int head[VERTEX_SIZE], arrPt;
int depth[VERTEX_SIZE], lastVisitedEdge[VERTEX_SIZE];
int vertexNum;

char mapArr[ROW_COLUMN_SIZE][ROW_COLUMN_SIZE];
bool hasVisited[ROW_COLUMN_SIZE][ROW_COLUMN_SIZE];
Node rallayArr[CHAR_SIZE], goldArr[VERTEX_SIZE];
int lastRallayPt, goldPt;
int dis[CHAR_SIZE][ROW_COLUMN_SIZE][ROW_COLUMN_SIZE];
int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column;

void addEdge(int from, int to, int capacity)
{
    arr[arrPt] = {to, capacity, head[from]};
    head[from] = arrPt++;
    arr[arrPt] = {from, 0, head[to]};
    head[to] = arrPt++;
}

bool updateDepth(int startPt, int endPt)
{
    memset(depth, -1, sizeof(depth));
    queue<int> q;

    q.push(startPt);
    depth[startPt] = 0;

    while (!q.empty())
    {
        int cntPt = q.front();
        q.pop();

        int edgePt = head[cntPt];
        while (edgePt != -1)
        {
            if (depth[arr[edgePt].to] == -1 && arr[edgePt].capacity > 0)
            {
                depth[arr[edgePt].to] = depth[cntPt] + 1;
                if (arr[edgePt].to == endPt)
                    return true;
                q.push(arr[edgePt].to);
            }
            edgePt = arr[edgePt].next;
        }
    }

    return false;
}

int findAugPath(int cntPt, int endPt, int minCapacity)
{
    if (cntPt == endPt)
        return minCapacity;

    int cntFlow = 0;
    int &edgePt = lastVisitedEdge[cntPt];
    while (edgePt != -1)
    {
        if (depth[arr[edgePt].to] == depth[cntPt] + 1 && arr[edgePt].capacity > 0)
        {
            int flowInc = findAugPath(arr[edgePt].to, endPt, min(minCapacity - cntFlow, arr[edgePt].capacity));
            if (flowInc == 0)
            {
                depth[arr[edgePt].to] = -1;
            }
            else
            {
                arr[edgePt].capacity -= flowInc;
                arr[edgePt ^ 1].capacity += flowInc;
                cntFlow += flowInc;

                if (cntFlow == minCapacity)
                    break;
            }
        }
        edgePt = arr[edgePt].next;
    }

    return cntFlow;
}

int dinic(int startPt, int endPt)
{
    int ans = 0;
    while (updateDepth(startPt, endPt))
    {
        for (int i = 0; i < vertexNum; i++)
            lastVisitedEdge[i] = head[i];
        int flowInc = findAugPath(startPt, endPt, INT_MAX);
        if (flowInc == 0)
            break;
        ans += flowInc;
    }
    return ans;
}

bool canVisit(Node &cntPt)
{
    return cntPt.x >= 0 && cntPt.x < row && cntPt.y >= 0 && cntPt.y < column && !hasVisited[cntPt.x][cntPt.y] && mapArr[cntPt.x][cntPt.y] != '#';
}

void bfs(int startPt)
{
    memset(hasVisited, false, sizeof(hasVisited));
    queue<Node> q;

    q.push(rallayArr[startPt]);
    hasVisited[rallayArr[startPt].x][rallayArr[startPt].y] = true;
    dis[startPt][rallayArr[startPt].x][rallayArr[startPt].y] = 0;

    while (!q.empty())
    {
        Node cntPt = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            Node nextPt = {cntPt.x + dir[0][i], cntPt.y + dir[1][i]};
            if (canVisit(nextPt))
            {
                hasVisited[nextPt.x][nextPt.y] = true;
                q.push(nextPt);
                dis[startPt][nextPt.x][nextPt.y] = dis[startPt][cntPt.x][cntPt.y] + 1;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> row >> column)
    {
        memset(head, -1, sizeof(head));
        memset(rallayArr, -1, sizeof(rallayArr));
        memset(dis, -1, sizeof(dis));
        arrPt = 0;
        lastRallayPt = 0;
        goldPt = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cin >> mapArr[i][j];
                if (mapArr[i][j] >= 'A' && mapArr[i][j] <= 'Z')
                {
                    rallayArr[mapArr[i][j] - 'A'] = {i, j};
                    lastRallayPt = max(lastRallayPt, mapArr[i][j] - 'A');
                }
                else if (mapArr[i][j] >= 'a' && mapArr[i][j] <= 'z')
                {
                    rallayArr[mapArr[i][j] - 'a' + 26] = {i, j};
                    lastRallayPt = max(lastRallayPt, mapArr[i][j] - 'a' + 26);
                }
                else if (mapArr[i][j] == '*')
                {
                    goldArr[goldPt++] = {i, j};
                }
            }
        }

        int startPt = 0;
        for (int i = 0; i <= lastRallayPt; i++)
        {
            bfs(i);
            if (i < lastRallayPt)
                addEdge(startPt, i + 1, 1);
        }

        bool hasAns = true;
        // Last rallyPt could be ignored
        for (int i = 0; i < lastRallayPt; i++)
        {
            for (int j = 0; j < goldPt; j++)
            {
                if (dis[i][rallayArr[i + 1].x][rallayArr[i + 1].y] == -1)
                {
                    hasAns = false;
                    break;
                }

                if (dis[i][goldArr[j].x][goldArr[j].y] + dis[i + 1][goldArr[j].x][goldArr[j].y] == dis[i][rallayArr[i + 1].x][rallayArr[i + 1].y])
                {
                    addEdge(i + 1, lastRallayPt + j + 1, 1);
                }
            }

            if (!hasAns)
                break;
        }

        if (!hasAns)
        {
            cout << -1 << endl;
            continue;
        }

        int endPt = lastRallayPt + goldPt + 1;
        vertexNum = endPt + 1;
        for (int i = 0; i < goldPt; i++)
        {
            addEdge(lastRallayPt + i + 1, endPt, 1);
        }

        int ans = dinic(startPt, endPt);
        cout << ans << endl;
    }
    return 0;
}
