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
#include <functional>
#include <iterator>
#define SIZE 301000
using namespace std;

typedef struct _Node
{
    int x, y;
    int step;

    bool operator < (const struct _Node b) const
    {
        return step > b.step;
    }
    bool operator == (const struct _Node b) const
    {
        return x == b.x && y == b.y;
    }
} Node;

bool arr[SIZE], hasVisited[SIZE];
int dir[2][4] = {1, -1, 0, 0, 0, 0, 1, -1};
int row, column;

Node startPt, endPt;

int getId(int x, int y)
{
    return x * column + y;
}

bool canMove(Node nextPt)
{
    int cntId = getId(nextPt.x, nextPt.y);
    if (nextPt.x < 0 || nextPt.y < 0 || nextPt.x >= row || nextPt.y >= column || hasVisited[cntId])
        return false;
    return true;
}

int bfs(Node startPt, Node endPt)
{
    priority_queue<Node> pq;
    startPt.step = 0;
    pq.push(startPt);

    int startId = getId(startPt.x, startPt.y);
    hasVisited[startId] = true;

    while (!pq.empty())
    {
        Node cntPt = pq.top();
        pq.pop();

        int cntId = getId(cntPt.x, cntPt.y);

        int starti, endi;
        if ((arr[cntId] == 1 && (cntPt.step & 1)) || (arr[cntId] == 0 && !(cntPt.step & 1)))
        {
            starti = 0;
            endi = 1;
        }
        else if ((arr[cntId] == 0 && (cntPt.step & 1)) || (arr[cntId] == 1 && !(cntPt.step & 1)))
        {
            starti = 2;
            endi = 3;
        }

        for (int i = starti; i <= endi; i++)
        {
            Node nextPt;
            nextPt.x = cntPt.x + dir[0][i];
            nextPt.y = cntPt.y + dir[1][i];
            nextPt.step = cntPt.step + 1;

            if (!canMove(nextPt))
                continue;

            if (nextPt == endPt)
                return nextPt.step;

            pq.push(nextPt);

            int nextId = getId(nextPt.x, nextPt.y);
            hasVisited[nextId] = true;
        }
    }

    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    int caseNum;
    cin >> caseNum;
    while (caseNum--)
    {
        cin >> row >> column;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                int cntId = getId(i, j);
                cin >> arr[cntId];
                hasVisited[cntId] = false;
            }
        }

        cin >> startPt.x >> startPt.y >> endPt.x >> endPt.y;
        startPt.x--;
        startPt.y--;
        endPt.x--;
        endPt.y--;

        if (startPt == endPt)
            cout << 0 << endl;
        else
        {
            int ans = bfs(startPt, endPt);
            cout << ans << endl;
        }
    }
    return 0;
}
